#ifdef WINDOWS
#define RECT WINRECT
#include <enet/enet.h>
#undef RECT
#else
#include <enet/enet.h>
#endif

#include <string>
#include <SDL.h>

#include "File.h"
#include "Networking.h"
#include "Server.h"
#include "player.h"
#include "cave_story.h"
#include "cs.h"
#include "mod_loader.h"
#include "Stage.h"

ENetHost *client;
ENetAddress clientAddress;
ENetPeer *toServer;
bool clientConnected;
char username[MAX_NAME];

CS_ARMS gArmsData[ARMS_MAX];
CS_ITEM gItemData[ITEM_MAX];

VIRTUAL_PLAYER gVirtualPlayers[MAX_CLIENTS];

unsigned int gLastChatMessage = 0;

const char *skinFilename = "Skin";
const char *playerName = "Player";

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
	address->host = SDL_SwapLE32(address->host);
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
	clientAddress.port = 28000, 0, 10;
	
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
		CS_ReleaseSurface(CS_SURFACE_ID_MY_CHAR + i);
		CS_MakeSurface_File("MyChar", CS_SURFACE_ID_MY_CHAR + i);
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
	
	SDL_RWops *packetData;
	ENetPacket *definePacket;
	
	static unsigned int lastPlayerTick = 0;
	
	char msg[PACKET_DATA];
	
	//Send player data
	if (SDL_GetTicks() > lastPlayerTick + TICKRATE)
	{
		//Setup packet
		uint8_t packet[0x100];
		memset(packet, 0, 0x100);
		packetData = SDL_RWFromMem(packet, 0x100);
		SDL_WriteLE32(packetData, NET_VERSION);
		SDL_WriteLE32(packetData, PACKETCODE_REPLICATE_PLAYER);
		
		//Set attributes
		SDL_WriteLE32(packetData, Player2->cond);
		SDL_WriteLE32(packetData, Player2->cond);
		SDL_WriteLE32(packetData, Player2->unit);
		SDL_WriteLE32(packetData, Player2->flag);
		SDL_WriteLE32(packetData, Player2->x);
		SDL_WriteLE32(packetData, Player2->y);
		SDL_WriteLE32(packetData, Player2->up);
		SDL_WriteLE32(packetData, Player2->down);
		SDL_WriteLE32(packetData, CS_quote_weapon_selected);
		SDL_WriteLE32(packetData, Player2->equip);
		SDL_WriteLE32(packetData, Player2->ani_no);
		SDL_WriteLE32(packetData, Player2->direct);
		SDL_WriteLE32(packetData, Player2->shock);
		SDL_WriteLE32(packetData, Player2->life);
		SDL_WriteLE32(packetData, Player2->max_life);
		SDL_WriteLE32(packetData, CS_current_room);

		// <MIM patch location
		switch(mim_compatibility)
		{
			default:
				SDL_WriteLE32(packetData, CSM_MIM_unobstructive);
				break;

			case 0:
				SDL_WriteLE32(packetData, CSM_MIM_unobstructive);
				break;

			case 1:
				SDL_WriteLE32(packetData, CSM_MIM_tsc_plus);
				break;
		}
		
		//Send packet
		definePacket = enet_packet_create(packet, 0x100, 0);
		enet_peer_send(toServer, 0, definePacket);
		
		//Prepare for next tick
		lastPlayerTick = SDL_GetTicks();
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
				PrintChat("Welcome to the server!");
				PrintChat("Use 'T' to chat!");
				
				//Write packet data
				packetSize = 8 + MAX_NAME;
				packet = (uint8_t*)malloc(packetSize);
				memset(packet, 0, packetSize);
				
				packetData = SDL_RWFromMem(packet, packetSize);
				
				SDL_WriteLE32(packetData, NET_VERSION);
				SDL_WriteLE32(packetData, PACKETCODE_DEFINE_PLAYER);
				SDL_RWwrite(packetData, username, 1, MAX_NAME);
				
				//Send packet
				definePacket = enet_packet_create(packet, packetSize, ENET_PACKET_FLAG_RELIABLE);
				SDL_RWclose(packetData);
				free(packet);

				if (enet_peer_send(toServer, 0, definePacket) < 0)
					KillClient();
				else
				{
					//Write skin packet
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
				}
				break;
				
			case ENET_EVENT_TYPE_DISCONNECT:
				//Tell us we've disconnected (...)
				clientConnected = false;
				KillClient();
				return;
				
			case ENET_EVENT_TYPE_RECEIVE:
				//Handle packet data
				packetData = SDL_RWFromConstMem(event.packet->data, event.packet->dataLength);
				
				if (SDL_ReadLE32(packetData) == NET_VERSION)
				{
					switch (SDL_ReadLE32(packetData))
					{
						case PACKETCODE_CHAT_MESSAGE:
							SDL_RWread(packetData, msg, 1, event.packet->dataLength - 8);
							PrintChat(msg);
							break;
							
						case PACKETCODE_REPLICATE_PLAYER:
							i = SDL_ReadLE32(packetData);
							
							//cond & unit
							gVirtualPlayers[i].cond = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].unit = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].flag = SDL_ReadLE32(packetData);
							
							//Update username
							char prevName[MAX_NAME];
							strcpy(prevName, gVirtualPlayers[i].name);
							SDL_RWread(packetData, gVirtualPlayers[i].name, 1, MAX_NAME);
							
							if (strcmp(prevName, gVirtualPlayers[i].name))
							{
							}
							
							//Update variables
							gVirtualPlayers[i].timeout = SDL_GetTicks() + VIRTUAL_PLAYER_TIMEOUT;
							
							//Set position
							gVirtualPlayers[i].lerpX = gVirtualPlayers[i].x;
							gVirtualPlayers[i].lerpY = gVirtualPlayers[i].y;
							gVirtualPlayers[i].x = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].y = SDL_ReadLE32(packetData);
							
							if (gVirtualPlayers[i].x - gVirtualPlayers[i].lerpX > 0x1000 || gVirtualPlayers[i].y - gVirtualPlayers[i].lerpY > 0x1000
							 || gVirtualPlayers[i].x - gVirtualPlayers[i].lerpX < -0x1000 || gVirtualPlayers[i].y - gVirtualPlayers[i].lerpY < -0x1000)
							{
								gVirtualPlayers[i].lerpX = gVirtualPlayers[i].x;
								gVirtualPlayers[i].lerpY = gVirtualPlayers[i].y;
							}
							
							//Set other variables
							gVirtualPlayers[i].lerpTick = 0;
							gVirtualPlayers[i].up = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].down = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].arms = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].equip = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].ani_no = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].direct = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].shock = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].life = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].max_life = SDL_ReadLE32(packetData);


							static int lastStage;
							lastStage = gVirtualPlayers[i].stage;
							gVirtualPlayers[i].stage = SDL_ReadLE32(packetData);
							gVirtualPlayers[i].mim = SDL_ReadLE32(packetData);

							break;
							
							// was used for skins in CSE2 online, but i dont know if we can do that very easily in freeware
						case PACKETCODE_SKIN:
							/*
							i = SDL_ReadLE32(packetData);
							
							printf("Recieved %d's skin\n", i);
							
							//Get bitmap data (packet data but with first 12 bytes cut-off)
							SDL_RWops *bitmapData = SDL_RWFromConstMem(event.packet->data + 12, event.packet->dataLength - 12);
							
							//Load bitmap to skin slot (or use placeholder if failed)
							ReleaseSurface(SURFACE_ID_SKIN_0 + i);
							if (LoadBitmap(bitmapData, SURFACE_ID_SKIN_0 + i, true))
							{
								printf("Loaded %d's skin\n", i);
							}
							else
							{
								printf("Failed to open %d's skin\n", i);
								ReleaseSurface(SURFACE_ID_SKIN_0 + i);
								MakeSurface_File("MyChar", SURFACE_ID_SKIN_0 + i);
								SDL_RWclose(bitmapData);
							}
							*/
							break;
					}
				}
				
				SDL_RWclose(packetData);
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
		if (gVirtualPlayers[i].timeout)
		{
			//Timeout
			if (SDL_GetTicks() > gVirtualPlayers[i].timeout)
				memset(&gVirtualPlayers[i], 0, sizeof(VIRTUAL_PLAYER));
		}
	}
	
	//Draw other players
	static unsigned int lastLerpTick = SDL_GetTicks();
	
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].timeout && gVirtualPlayers[i].stage == CS_current_room)
		{
			//Get position
			int drawX = gVirtualPlayers[i].lerpX + (gVirtualPlayers[i].x - gVirtualPlayers[i].lerpX) * gVirtualPlayers[i].lerpTick / TICKRATE;
			int drawY = gVirtualPlayers[i].lerpY + (gVirtualPlayers[i].y - gVirtualPlayers[i].lerpY) * gVirtualPlayers[i].lerpTick / TICKRATE;
			gVirtualPlayers[i].lerpTick += (SDL_GetTicks() - lastLerpTick);
			
			if (gVirtualPlayers[i].lerpTick > TICKRATE)
				gVirtualPlayers[i].lerpTick = TICKRATE;
			
			//Draw
			RECT rcLeft[12];
			RECT rcRight[12];
			
			rcLeft[0] = {0, 0, 16, 16};
			rcLeft[1] = {16, 0, 32, 16};
			rcLeft[2] = {0, 0, 16, 16};
			rcLeft[3] = {32, 0, 48, 16};
			rcLeft[4] = {0, 0, 16, 16};
			rcLeft[5] = {48, 0, 64, 16};
			rcLeft[6] = {64, 0, 80, 16};
			rcLeft[7] = {48, 0, 64, 16};
			rcLeft[8] = {80, 0, 96, 16};
			rcLeft[9] = {48, 0, 64, 16};
			rcLeft[10] = {96, 0, 112, 16};
			rcLeft[11] = {112, 0, 128, 16};

			rcRight[0] = {0, 16, 16, 32};
			rcRight[1] = {16, 16, 32, 32};
			rcRight[2] = {0, 16, 16, 32};
			rcRight[3] = {32, 16, 48, 32};
			rcRight[4] = {0, 16, 16, 32};
			rcRight[5] = {48, 16, 64, 32};
			rcRight[6] = {64, 16, 80, 32};
			rcRight[7] = {48, 16, 64, 32};
			rcRight[8] = {80, 16, 96, 32};
			rcRight[9] = {48, 16, 64, 32};
			rcRight[10] = {96, 16, 112, 32};
			rcRight[11] = {112, 16, 128, 32};
			
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
					CS_PutBitmap3(
						&CS_clip_rect_common,
						(drawX - 0x1000) / 0x200 - fx / 0x200,
						(drawY - 0x1000) / 0x200 - fy / 0x200 + arms_offset_y,
						&rect_arms,
						CS_SURFACE_ID_ARMS);
				else
					CS_PutBitmap3(
						&CS_clip_rect_common,
						(drawX - 0x1000) / 0x200 - fx / 0x200 - 8,
						(drawY - 0x1000) / 0x200 - fy / 0x200 + arms_offset_y,
						&rect_arms,
						CS_SURFACE_ID_ARMS);
				
				gVirtualPlayers[i].shockT++;
				
				if (gVirtualPlayers[i].shock == 0 || !((gVirtualPlayers[i].shockT >> 1) & 1))
				{
					//Draw player
					RECT rect;
					if (gVirtualPlayers[i].direct)
						rect = rcRight[gVirtualPlayers[i].ani_no];
					else
						rect = rcLeft[gVirtualPlayers[i].ani_no];
					
					rect.top += 32 * gVirtualPlayers[i].mim;
					rect.bottom += 32 * gVirtualPlayers[i].mim;

					if (gVirtualPlayers[i].equip & 0x40)
					{
						rect.top += 32;
						rect.bottom += 32;
					}
					
					CS_PutBitmap3(&CS_clip_rect_common, (drawX - 0x1000) / 0x200 - fx / 0x200, (drawY - 0x1000) / 0x200 - fy / 0x200, &rect, CS_SURFACE_ID_MY_CHAR);
					
					//Draw airtank
					RECT rcBubble[2];
					rcBubble[0] = {56, 96, 80, 120};
					rcBubble[1] = {80, 96, 104, 120};
					
					++gVirtualPlayers[i].bubble;
					
					if (gVirtualPlayers[i].equip & 0x10 && gVirtualPlayers[i].flag & 0x100)
						CS_PutBitmap3(&CS_clip_rect_common, drawX / 0x200 - 12 - fx / 0x200, gVirtualPlayers[i].y / 0x200 - 12 - fy / 0x200, &rcBubble[(gVirtualPlayers[i].bubble >> 1) & 1], CS_SURFACE_ID_UNKNOWN_19);
					else if (gVirtualPlayers[i].unit == 1)
						CS_PutBitmap3(&CS_clip_rect_common, drawY / 0x200 - 12 - fx / 0x200, gVirtualPlayers[i].y / 0x200 - 12 - fy / 0x200, &rcBubble[(gVirtualPlayers[i].bubble >> 1) & 1], CS_SURFACE_ID_UNKNOWN_19);
				}

				// Draw player names
				switch (show_player_names)
				{
					default:
						CS_PutText((drawX / 0x200 - fx / 0x200) - (strlen(gVirtualPlayers[i].name) * 3), drawY / 0x200 - fy / 0x200 - 19, gVirtualPlayers[i].name, 0x000010);
						CS_PutText((drawX / 0x200 - fx / 0x200) - (strlen(gVirtualPlayers[i].name) * 3), drawY / 0x200 - fy / 0x200 - 20, gVirtualPlayers[i].name, 0xFFFFFF);
						break;

					// Don't show names
					case 1:
						break;

					// Show "Player #"
					case 2:
						CS_PutText((drawX / 0x200 - fx / 0x200) - (strlen(playerName) * 3), drawY / 0x200 - fy / 0x200 - 19, (std::string(playerName) + " " + std::to_string(i)).c_str(), 0x000010);
						CS_PutText((drawX / 0x200 - fx / 0x200) - (strlen(playerName) * 3), drawY / 0x200 - fy / 0x200 - 20, (std::string(playerName) + " " + std::to_string(i)).c_str(), 0xFFFFFF);
						break;
				}
			}
		}
	}
	
	lastLerpTick = SDL_GetTicks();
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
		CS_DrawSprite_WithTransparency(&CS_clip_rect_common, 0, WINDOW_HEIGHT / 2, &rcChat, CS_SURFACE_ID_UNKNOWN_3);
	*/

	if (*gKey & 0x10000)
	{
		//Draw player-list
		const int nameWidth = ((MAX_NAME * 5) + 8 + 16);
		
		//Get amount of players
		int clientNo = 0;
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if (gVirtualPlayers[i].timeout)
				clientNo++;
		}
		
		//Draw actual playerlist
		int playerPerLine = 320 / nameWidth;
		int offX = (320 - (nameWidth * playerPerLine)) / 2;
		
		int player_i = 0;
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if (gVirtualPlayers[i].timeout)
			{
				int x = offX + (player_i % playerPerLine) * nameWidth;
				int y = 0 + (player_i / playerPerLine) * 20;
				player_i++;
				
				//Draw back
				RECT rcBack = {x, y, x + nameWidth, y + 20};
				CS_CortBox(&rcBack, 0x000020);
				
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

				CS_PutBitmap3(&rcBack, x, y + 2, &rcSkin, CS_SURFACE_ID_MY_CHAR);

				// 'Comma menu' Text.

				//Draw username
				switch (show_player_names)
				{
					default:
						CS_PutText((x + nameWidth / 2) - 42, y, gVirtualPlayers[i].name, 0xFFFFFF);
						break;

					case 1:
						break;

					case 2:
						CS_PutText((x + nameWidth / 2) - 42, y, (std::string(playerName) + " " + std::to_string(i)).c_str(), 0xFFFFFF);
						break;
				}
				
				//Draw mapname
				if (show_player_names == 1)
					CS_PutText((x + nameWidth / 2) - 42, y + 4, StageTbl[gVirtualPlayers[i].stage].name, 0xFFFFFF);
				else
					CS_PutText((x + nameWidth / 2) - 42, y + 9, StageTbl[gVirtualPlayers[i].stage].name, 0xFFFFFF);
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
