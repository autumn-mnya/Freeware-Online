#ifdef WINDOWS
#define RECT WINRECT
#include <enet/enet.h>
#undef RECT
#else
#include <enet/enet.h>
#endif

#include <chrono>
#include <string>

#include "File.h"
#include "Networking.h"
#include "main.h"
#include "cave_story.h"
#include "mod_loader.h"
#include "ByteStream.h"

ENetHost *client;
ENetAddress clientAddress;
ENetPeer *toServer;
bool clientConnected;
char username[MAX_NAME];

typedef std::chrono::high_resolution_clock Clock;

VIRTUAL_PLAYER gVirtualPlayers[MAX_CLIENTS];

unsigned int gLastChatMessage = 0;

const char *skinFilename = "Skin";
const char *playerName = "Player";

static int SubpixelToScreenCoord(int coord)
{
	return (coord / 0x200);
}

//Handle ENet
bool InitNetworking()
{
	return enet_initialize() >= 0;
}

void QuitNetworking()
{
	enet_deinitialize();
}

//Connect to a server
static int ConvertIpToAddress(ENetAddress *address, const char *name)
{
	enet_uint8 vals [4] = {0, 0, 0, 0};
	for (int i = 0; i < 4; i++)
	{
		const char * next = name + 1;
		if (*name != '0')
		{
			long val = strtol(name, (char**)&next, 10);
			if (val < 0 || val > 0xFF || next == name || next - name > 3)
				return -1;
			vals[i] = (enet_uint8)val;
		}

		if (*next != (i < 3 ? '.' : '\0'))
			return -1;
		name = next + 1;
	}
	
	memcpy(&address->host, vals, sizeof(enet_uint32));
	address->host = address->host; //originally this swapped endian where needed, but that macro was removed
	return 0;
}

static bool VerifyPort(const char *port)
{
	for (int i = 0; port[i]; i++)
	{
		if (port[i] < '0' || port[i] > '9')
			return false;
	}
	
	return true;
}

bool JoinServer(const char *ip, const char *port, const char *name)
{
	//Make sure we have a name
	if (strlen(name) < NAME_MIN)
		return false;
	strcpy(username, name);
	
	//Set IP address
	if (!(enet_address_set_host(&clientAddress, ip) >= 0 || ConvertIpToAddress(&clientAddress, ip) >= 0))
		return false;
	
	//Set port
	if (!VerifyPort(port))
		return false;
	clientAddress.port = std::stoi(gamePort), 0, 10;
	
	//Create client
	clientConnected = false;
	if ((client = enet_host_create(NULL, 1, 1, 0, 0)) == NULL)
		return false;
	
	//Connect to server
	if ((toServer = enet_host_connect(client, &clientAddress, 0, CONNECT_NORMAL)) == NULL)
	{
		enet_host_destroy(client);
		return false;
	}
	
	//Clear stuff
	// LoadMySkin();
	/*
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		ReleaseSurface(SURFACE_ID_MY_CHAR + i);
		MakeSurface_File("MyChar", SURFACE_ID_MY_CHAR + i);
	}
	*/
	
	ClearChat();
	
	return true;
}

//Kill toServer
void KillClient()
{
	//Disconnect from server
	if (toServer)
		enet_peer_disconnect_now(toServer, DISCONNECT_FORCE);
	toServer = NULL;
	
	//Destroy client
	if (client)
		enet_host_destroy(client);
	client = NULL;
}

//Handle client
void HandleClient()
{
	ENetEvent event;
	
	ByteStream *packetData;
	ENetPacket *definePacket;
	
	static Clock::time_point lastPlayerTick;
	
	char msg[PACKET_DATA];
	
	//Send player data
	if (Clock::now() > lastPlayerTick + TICKRATE)
	{
		//Setup packet
		uint8_t packet[0x100];
		memset(packet, 0, 0x100);
		packetData = new ByteStream(packet, 0x100);
		packetData->WriteLE32(NET_VERSION);
		packetData->WriteLE32(PACKETCODE_REPLICATE_PLAYER);
		
		//Set attributes
		packetData->WriteLE32(gMC.cond);
		packetData->WriteLE32(gMC.unit);
		packetData->WriteLE32(gMC.flag);
		packetData->WriteLE32(gMC.x);
		packetData->WriteLE32(gMC.y);
		packetData->WriteLE32(gMC.xm);
		packetData->WriteLE32(gMC.ym);
		packetData->WriteLE32(gMC.up);
		packetData->WriteLE32(gMC.down);
		packetData->WriteLE32(gArmsData[gSelectedArms].code);
		packetData->WriteLE32(gMC.equip);
		packetData->WriteLE32(gMC.ani_no);
		packetData->WriteLE32(gMC.hit.back);
		packetData->WriteLE32(gMC.hit.top);
		packetData->WriteLE32(gMC.hit.front);
		packetData->WriteLE32(gMC.hit.bottom);
		packetData->WriteLE32(gMC.direct);
		packetData->WriteLE32(gMC.shock);
		packetData->WriteLE32(gMC.life);
		packetData->WriteLE32(gMC.max_life);
		packetData->WriteLE32(gStageNo);

		// <MIM patch location
		switch(mim_compatibility)
		{
			default:
				packetData->WriteLE32(CSM_MIM_unobstructive);
				break;

			case 0:
				packetData->WriteLE32(CSM_MIM_unobstructive);
				break;

			case 1:
				packetData->WriteLE32(CSM_MIM_tsc_plus);
				break;
		}
		
		packetData->WriteLE32(hide_me_on_map);
		packetData->WriteLE32(im_being_held);

		//Send packet
		definePacket = enet_packet_create(packet, 0x100, 0);
		enet_peer_send(toServer, 0, definePacket);
		
		//Prepare for next tick
		lastPlayerTick = Clock::now();
	}
	
	//Handle events
	int i;
	uint8_t *packet;
	unsigned int packetSize;
	
	while (enet_host_service(client, &event, 5) > 0)
	{
		switch (event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
				//Tell us we're connected (yeah i just said that)
				clientConnected = true;
				
				//Welcome message
				// PrintChat("Welcome to the server!");
				// PrintChat("Use 'T' to chat!");
				
				//Write packet data
				packetSize = 8 + MAX_NAME;
				packet = (uint8_t*)malloc(packetSize);
				memset(packet, 0, packetSize);
				
				packetData = new ByteStream(packet, packetSize);
				
				packetData->WriteLE32(NET_VERSION);
				packetData->WriteLE32(PACKETCODE_DEFINE_PLAYER);
				packetData->Write(username, 1, MAX_NAME);
				
				//Send packet
				definePacket = enet_packet_create(packet, packetSize, ENET_PACKET_FLAG_RELIABLE);
				delete packetData;
				free(packet);

				if (enet_peer_send(toServer, 0, definePacket) < 0)
					KillClient();
				else
				{
					/*Write skin packet
					char path[MAX_PATH];

					sprintf(path, "%s/%s.bmp", "%s", skinFilename);
					
					SDL_RWops *temp = SDL_RWFromFile(path, "rb");
					
					if (!temp)
					{
						sprintf(path, "%s/%s.bmp", "%s", skinFilename);
						temp = SDL_RWFromFile(path, "rb");
						
						if (!temp)
							break;
					}
					
					if (temp)
					{
						printf("Sending skin\n");
						
						packetSize = (8 + SDL_RWsize(temp));
						packet = (uint8_t*)malloc(packetSize);
						memset(packet, 0, packetSize);
						
						packetData = SDL_RWFromMem(packet, packetSize);
						SDL_WriteLE32(packetData, NET_VERSION);
						SDL_WriteLE32(packetData, PACKETCODE_SKIN);
						SDL_RWclose(packetData);
						SDL_RWread(temp, packet + 8, 1, SDL_RWsize(temp));
						SDL_RWclose(temp);
						
						//Send packet
						definePacket = enet_packet_create(packet, packetSize, ENET_PACKET_FLAG_RELIABLE);
						free(packet);
						enet_peer_send(toServer, 0, definePacket);
					}
					*/
				}
				break;
				
			case ENET_EVENT_TYPE_DISCONNECT:
				//Tell us we've disconnected (...)
				clientConnected = false;
				KillClient();
				return;
				
			case ENET_EVENT_TYPE_RECEIVE:
				//Handle packet data
				packetData = new ByteStream(event.packet->data, event.packet->dataLength);
				
				if (packetData->ReadLE32() == NET_VERSION)
				{
					switch (packetData->ReadLE32())
					{
						case PACKETCODE_CHAT_MESSAGE:
							packetData->Read(msg, 1, event.packet->dataLength - 8);
							PrintChat(msg);
							break;
							
						case PACKETCODE_REPLICATE_PLAYER:
							i = packetData->ReadLE32();
							
							//cond & unit
							gVirtualPlayers[i].cond = packetData->ReadLE32();
							gVirtualPlayers[i].unit = packetData->ReadLE32();
							gVirtualPlayers[i].flag = packetData->ReadLE32();
							
							//Update username
							char prevName[MAX_NAME];
							strcpy(prevName, gVirtualPlayers[i].name);
							packetData->Read(gVirtualPlayers[i].name, 1, MAX_NAME);
							gVirtualPlayers[i].player_num = packetData->ReadLE32();

							if (strcmp(prevName, gVirtualPlayers[i].name))
							{
								RECT rcUsername = { 0, i * 16, WINDOW_WIDTH, i * 16 + 16 };
								CortBox2(&rcUsername, 0x000000, SURFACE_ID_USERNAME);
								std::string acss = (std::string(playerName) + " " + std::to_string(gVirtualPlayers[i].player_num));
								const char* anonName = acss.c_str();
								switch (show_player_names)
								{
									default:
										PutText2((WINDOW_WIDTH - strlen(gVirtualPlayers[i].name) * 5) / 2, i * 16 + 2 + 1, gVirtualPlayers[i].name, 0x000010, SURFACE_ID_USERNAME);
										PutText2((WINDOW_WIDTH - strlen(gVirtualPlayers[i].name) * 5) / 2, i * 16 + 2, gVirtualPlayers[i].name, 0xFFFFFE, SURFACE_ID_USERNAME);
										break;

									case 2:
										PutText2((WINDOW_WIDTH - strlen(anonName) * 5) / 2, i * 16 + 2 + 1, anonName, 0x000010, SURFACE_ID_USERNAME);
										PutText2((WINDOW_WIDTH - strlen(anonName) * 5) / 2, i * 16 + 2, anonName, 0xFFFFFE, SURFACE_ID_USERNAME);
										break;
								}
							}
							
							//Update variables
							gVirtualPlayers[i].timeout = Clock::now() + VIRTUAL_PLAYER_TIMEOUT;
							
							//Set position
							gVirtualPlayers[i].lerpX = gVirtualPlayers[i].x;
							gVirtualPlayers[i].lerpY = gVirtualPlayers[i].y;
							gVirtualPlayers[i].x = packetData->ReadLE32();
							gVirtualPlayers[i].y = packetData->ReadLE32();
							gVirtualPlayers[i].xm = packetData->ReadLE32();
							gVirtualPlayers[i].ym = packetData->ReadLE32();

							if (gVirtualPlayers[i].x - gVirtualPlayers[i].lerpX > 0x1000 || gVirtualPlayers[i].y - gVirtualPlayers[i].lerpY > 0x1000
							 || gVirtualPlayers[i].x - gVirtualPlayers[i].lerpX < -0x1000 || gVirtualPlayers[i].y - gVirtualPlayers[i].lerpY < -0x1000)
							{
								gVirtualPlayers[i].lerpX = gVirtualPlayers[i].x;
								gVirtualPlayers[i].lerpY = gVirtualPlayers[i].y;
							}
							
							//Set other variables
							gVirtualPlayers[i].lerpTick = Clock::duration();
							gVirtualPlayers[i].up = packetData->ReadLE32();
							gVirtualPlayers[i].down = packetData->ReadLE32();
							gVirtualPlayers[i].arms = packetData->ReadLE32();
							gVirtualPlayers[i].equip = packetData->ReadLE32();
							gVirtualPlayers[i].ani_no = packetData->ReadLE32();
							gVirtualPlayers[i].hit.left = packetData->ReadLE32();
							gVirtualPlayers[i].hit.top = packetData->ReadLE32();
							gVirtualPlayers[i].hit.right = packetData->ReadLE32();
							gVirtualPlayers[i].hit.bottom = packetData->ReadLE32();
							gVirtualPlayers[i].direct = packetData->ReadLE32();
							gVirtualPlayers[i].shock = packetData->ReadLE32();
							gVirtualPlayers[i].life = packetData->ReadLE32();
							gVirtualPlayers[i].max_life = packetData->ReadLE32();


							static int lastStage;
							lastStage = gVirtualPlayers[i].stage;
							gVirtualPlayers[i].stage = packetData->ReadLE32();
							gVirtualPlayers[i].mim = packetData->ReadLE32();
							gVirtualPlayers[i].hide_vp_on_map = packetData->ReadLE32();
							gVirtualPlayers[i].is_being_held = packetData->ReadLE32();

							if (lastStage != gVirtualPlayers[i].stage)
							{
								RECT rcMapName = { WINDOW_WIDTH, i * 16,WINDOW_WIDTH * 2, i * 16 + 16 };
								CortBox2(&rcMapName, 0x000000, SURFACE_ID_USERNAME);
								PutText2(WINDOW_WIDTH + (WINDOW_WIDTH - strlen(gTMT[gVirtualPlayers[i].stage].name) * 5) / 2, i * 16 + 2, gTMT[gVirtualPlayers[i].stage].name, 0xFFFFFE, SURFACE_ID_USERNAME);
							}

							break;

							// undefined currently, might be for grabbing other players and throwing them similar to New Super Mario Bros.
						case PACKETCODE_RECEIVE_DEATH:
							if (enable_deathlink == true)
							{
								printf("Received death from Server\n");
								PlayerDeath();
							}
							break;
					}
				}
				
				delete packetData;
				break;
		}
		continue;
	}
}

//Draw virtual players
void PutVirtualPlayers(int fx, int fy)
{
	//Timeout other players
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].timeout > Clock::time_point())
		{
			//Timeout
			if (Clock::now() > gVirtualPlayers[i].timeout)
				memset(&gVirtualPlayers[i], 0, sizeof(VIRTUAL_PLAYER));
		}
	}
	
	//Draw other players
	static Clock::time_point lastLerpTick = Clock::now();
	
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].timeout > Clock::time_point() && gVirtualPlayers[i].stage == gStageNo)
		{
			//Get position
			int drawX = gVirtualPlayers[i].lerpX + (gVirtualPlayers[i].x - gVirtualPlayers[i].lerpX) * (gVirtualPlayers[i].lerpTick / TICKRATE);
			int drawY = gVirtualPlayers[i].lerpY + (gVirtualPlayers[i].y - gVirtualPlayers[i].lerpY) * (gVirtualPlayers[i].lerpTick / TICKRATE);
			gVirtualPlayers[i].lerpTick += (Clock::now() - lastLerpTick);
			
			if (gVirtualPlayers[i].lerpTick > TICKRATE)
				gVirtualPlayers[i].lerpTick = TICKRATE;
			
			//Draw
			RECT rcVirtualPlayer[12] = {
				{0,   0, 16,  16},
				{16,  0, 32,  16},
				{0,   0, 16,  16},
				{32,  0, 48,  16},
				{0,   0, 16,  16},
				{48,  0, 64,  16},
				{64,  0, 80,  16},
				{48,  0, 64,  16},
				{80,  0, 96,  16},
				{48,  0, 64,  16},
				{96,  0, 112, 16},
				{112, 0, 128, 16},
			};

			RECT rcVirtualPlayerHitbox;
			
			if ((gVirtualPlayers[i].cond & 0x80) && !(gVirtualPlayers[i].cond & 2))
			{
				//Draw weapon
				RECT rect_arms;
				rect_arms.left = 24 * (gVirtualPlayers[i].arms % 13);
				rect_arms.right = rect_arms.left + 24;
				rect_arms.top = 96 * (gVirtualPlayers[i].arms / 13);
				rect_arms.bottom = rect_arms.top + 16;
				
				if (gVirtualPlayers[i].direct == 2)
				{
					rect_arms.top += 16;
					rect_arms.bottom += 16;
				}
				
				int arms_offset_y;
				if (gVirtualPlayers[i].up)
				{
					arms_offset_y = -4;
					rect_arms.top += 32;
					rect_arms.bottom += 32;
				}
				else if (gVirtualPlayers[i].down)
				{
					arms_offset_y = 4;
					rect_arms.top += 64;
					rect_arms.bottom += 64;
				}
				else
				{
					arms_offset_y = 0;
				}
				
				if (gVirtualPlayers[i].ani_no == 1 || gVirtualPlayers[i].ani_no == 3 || gVirtualPlayers[i].ani_no == 6 || gVirtualPlayers[i].ani_no == 8)
					++rect_arms.top;
				
				if (gVirtualPlayers[i].direct)
					PutBitmap3(
						&grcGame,
						(drawX - 0x1000) / 0x200 - fx / 0x200,
						(drawY - 0x1000) / 0x200 - fy / 0x200 + arms_offset_y,
						&rect_arms,
						SURFACE_ID_ARMS);
				else
					PutBitmap3(
						&grcGame,
						(drawX - 0x1000) / 0x200 - fx / 0x200 - 8,
						(drawY - 0x1000) / 0x200 - fy / 0x200 + arms_offset_y,
						&rect_arms,
						SURFACE_ID_ARMS);
				
				gVirtualPlayers[i].shockT++;
				
				if (gVirtualPlayers[i].shock == 0 || !((gVirtualPlayers[i].shockT >> 1) & 1))
				{
					//Draw player
					RECT rect;		
					rect = rcVirtualPlayer[gVirtualPlayers[i].ani_no];
					if (gVirtualPlayers[i].direct)
					{
						rect.top += 16;
						rect.bottom += 16;
					}
				
					rect.top += 32 * gVirtualPlayers[i].mim;
					rect.bottom += 32 * gVirtualPlayers[i].mim;

					if (gVirtualPlayers[i].equip & 0x40)
					{
						rect.top += 32;
						rect.bottom += 32;
					}
					
					PutBitmap3(&grcGame, (drawX - 0x1000) / 0x200 - fx / 0x200, (drawY - 0x1000) / 0x200 - fy / 0x200, &rect, SURFACE_ID_MY_CHAR);
					
					//Draw airtank
					RECT rcBubble[2];
					rcBubble[0] = {56, 96, 80, 120};
					rcBubble[1] = {80, 96, 104, 120};
					
					++gVirtualPlayers[i].bubble;
					
					if (gVirtualPlayers[i].equip & 0x10 && gVirtualPlayers[i].flag & 0x100)
						PutBitmap3(&grcGame, drawX / 0x200 - 12 - fx / 0x200, gVirtualPlayers[i].y / 0x200 - 12 - fy / 0x200, &rcBubble[(gVirtualPlayers[i].bubble >> 1) & 1], SURFACE_ID_CARET);
					else if (gVirtualPlayers[i].unit == 1)
						PutBitmap3(&grcGame, drawY / 0x200 - 12 - fx / 0x200, gVirtualPlayers[i].y / 0x200 - 12 - fy / 0x200, &rcBubble[(gVirtualPlayers[i].bubble >> 1) & 1], SURFACE_ID_CARET);
				}

				// Draw player names
				RECT rcUsername = { 0, i * 16, WINDOW_WIDTH, i * 16 + 16 };
				if (show_player_names != 1)
					PutBitmap3(&grcGame, drawX / 0x200 - fx / 0x200 - WINDOW_WIDTH / 2, drawY / 0x200 - fy / 0x200 - 22, &rcUsername, SURFACE_ID_USERNAME);
			}

			// Draw Virtual Player hitboxes

			if (show_players_hitboxes == true)
			{
				rcVirtualPlayerHitbox.left = SubpixelToScreenCoord(gVirtualPlayers[i].x) - SubpixelToScreenCoord(gVirtualPlayers[i].hit.left) - SubpixelToScreenCoord(fx) + SubpixelToScreenCoord(3 * 0x200);
				rcVirtualPlayerHitbox.top = SubpixelToScreenCoord(gVirtualPlayers[i].y) - SubpixelToScreenCoord(gVirtualPlayers[i].hit.top) - SubpixelToScreenCoord(fy) + SubpixelToScreenCoord(6 * 0x200);
				rcVirtualPlayerHitbox.right = SubpixelToScreenCoord(gVirtualPlayers[i].x) + SubpixelToScreenCoord(gVirtualPlayers[i].hit.right) - SubpixelToScreenCoord(fx) - SubpixelToScreenCoord(3 * 0x200);
				rcVirtualPlayerHitbox.bottom = SubpixelToScreenCoord(gVirtualPlayers[i].y) + SubpixelToScreenCoord(gVirtualPlayers[i].hit.bottom) - SubpixelToScreenCoord(fy) - SubpixelToScreenCoord(6 * 0x200);
				CortBox(&rcVirtualPlayerHitbox, GetCortBoxColor(RGB(0xFF, 0x00, 0xFF)));
			}
		}
	}
	
	lastLerpTick = Clock::now();
}

//Connection verification
bool InServer()
{
	return (toServer != NULL && client != NULL);
}

bool ConnectedServer()
{
	return clientConnected == true;
}

//Chat system
void SendChatMessage(const char *name, const char *text)
{
	/*
	//Get actual text to render (and clip so it fits into 256 bytes)
	char msgName[MAX_NAME + 3];
	
	if (name)
		sprintf(msgName, "%s", name);
	else
		sprintf(msgName, "%s: ", username);
	
	// Brayconn additions
	auto TEMP = std::string(msgName) + std::string(text);
	auto msgText = TEMP.c_str();
	
	//Write packet data
	// This packet is different from how it was originally -Brayconn
	auto packetSize = 8 + (strlen(msgText) + 1);
	uint8_t* packet = new uint8_t[packetSize];
	SDL_RWops *packetData = SDL_RWFromMem(packet, packetSize);
	SDL_WriteLE32(packetData, NET_VERSION);
	SDL_WriteLE32(packetData, PACKETCODE_CHAT_MESSAGE);
	SDL_RWwrite(packetData, msgText, 1, sizeof(msgText));
	SDL_RWclose(packetData);

	//Send packet
	ENetPacket *definePacket = enet_packet_create(packet, packetSize, ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(toServer, 0, definePacket);

	// Brayconn addition (if we use new, we delete afterwards!!)
	delete[] packet;
	*/
}

void ClearChat()
{
	/*
	RECT rcChatFull = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	CortBox2(&rcChatFull, 0x000000, SURFACE_ID_CHAT);
	*/
}

void ShiftChat()
{
	/*
	//Shift chat upwards
	RECT rcChatShift = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT - CHAT_OFF_Y + CHAT_LINE_HEIGHT};
	RECT rcChatNewLine = {0, WINDOW_HEIGHT - CHAT_OFF_Y, WINDOW_WIDTH, WINDOW_HEIGHT - CHAT_OFF_Y + CHAT_LINE_HEIGHT};
	Surface2Surface(0, -CHAT_LINE_HEIGHT, &rcChatShift, SURFACE_ID_CHAT, SURFACE_ID_CHAT);
	CortBox2(&rcChatNewLine, 0x000000, SURFACE_ID_CHAT);
	*/
}

void PrintChat(const char *text)
{
	/*
	gLastChatMessage = SDL_GetTicks();
	
	//Draw new line
	ShiftChat();
	PutTextChat2(8, WINDOW_HEIGHT - CHAT_OFF_Y + 1, text, 0x110022, SURFACE_ID_CHAT);
	PutTextChat2(8, WINDOW_HEIGHT - CHAT_OFF_Y, text, 0xFFFFFE, SURFACE_ID_CHAT);
	*/
}

//Draw server things
void PutServer()
{
	//Draw chat
	/*
	RECT rcChat = {0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT};
	if (SDL_GetTicks() < gLastChatMessage + 8000)
		DrawSprite_WithTransparency(&grcGame, 0, WINDOW_HEIGHT / 2, &rcChat, SURFACE_ID_UNKNOWN_3);
	*/

	if (gKey & KEY_ALT_LEFT)
	{
		//Draw player-list
		const int nameWidth = ((MAX_NAME * 5) + 8 + 16);
		
		//Get amount of players
		int clientNo = 0;
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if (gVirtualPlayers[i].timeout > Clock::time_point())
				clientNo++;
		}
		
		//Draw actual playerlist
		int playerPerLine = 320 / nameWidth;
		int offX = (320 - (nameWidth * playerPerLine)) / 2;
		
		int player_i = 0;
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if (gVirtualPlayers[i].timeout > Clock::time_point())
			{
				int x = offX + (player_i % playerPerLine) * nameWidth;
				int y = 0 + (player_i / playerPerLine) * 20;
				player_i++;
				
				//Draw back
				RECT rcBack = {x, y, x + nameWidth, y + 20};
				CortBox(&rcBack, 0x000020);
				
				//Draw skin
				RECT rcSkin = {0, 0, 16, 16};

				// <MIM / Mimiga Mask (Equip 0x40)
				rcSkin.top += 32 * gVirtualPlayers[i].mim;
				rcSkin.bottom += 32 * gVirtualPlayers[i].mim;

				if (gVirtualPlayers[i].equip & 0x40)
				{
					rcSkin.top += 32;
					rcSkin.bottom += 32;
				}

				PutBitmap3(&rcBack, x, y + 2, &rcSkin, SURFACE_ID_MY_CHAR);

				// 'Comma menu' Text.

				//Draw username
				RECT rcUsername = { 0, i * 16, WINDOW_WIDTH, i * 16 + 16 };

				//Draw username
				switch (show_player_names)
				{
					default:
						PutBitmap3(&rcBack, x + nameWidth / 2 - WINDOW_WIDTH / 2, y - 1, &rcUsername, SURFACE_ID_USERNAME);
						break;

					case 1:
						break;
				}

				//Draw mapname
				RECT rcMapName = { WINDOW_WIDTH, i * 16, WINDOW_WIDTH * 2, i * 16 + 16 };
				PutBitmap3(&rcBack, x + nameWidth / 2 - WINDOW_WIDTH / 2, y + 9, &rcMapName, SURFACE_ID_USERNAME);
			}
		}
	}
}

//Get profile to write to / load from
char *GetProfileName()
{
	static char profileName[MAX_PATH];
	if (InServer() && clientAddress.host)
		sprintf(profileName, "Profile%d.dat", clientAddress.host);
	else
		sprintf(profileName, "ProfileUnk.dat");
	return profileName;
}

//Handle skins
void LoadMySkin()
{
	/*
	//Verify skin before we load it
	char path[MAX_PATH];
	sprintf(path, "%s/%s.bmp", gModulePath, skinFilename);
	
	//Attempt to load as .bmp
	SDL_Surface *temp = SDL_LoadBMP(path);
	
	if (!temp)
	{
		//Attempt to load as .bmp
		sprintf(path, "%s/%s.bmp", gModulePath, skinFilename);
		temp = SDL_LoadBMP(path);
		
		if (!temp)
			return;
	}
	
	//Verify size
	if (temp->w != 200 || temp->h != 64)
		return;
	
	//Load Skin over our character
	ReleaseSurface(SURFACE_ID_MY_CHAR);
	sprintf(path, "../%s", skinFilename);
	MakeSurface_File(path, SURFACE_ID_MY_CHAR);
	*/
}

void SendMyDeathPacket()
{
	uint8_t packet[8];
	ByteStream packetData(packet, 8);

	packetData.WriteLE32(NET_VERSION);
	packetData.WriteLE32(PACKETCODE_RECEIVE_DEATH);

	//Send packet
	auto definePacket = enet_packet_create(packet, 8, ENET_PACKET_FLAG_RELIABLE);

	if (enet_peer_send(toServer, 0, definePacket) < 0)
		KillClient();
}