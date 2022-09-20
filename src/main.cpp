#include <windows.h>
#include <string>

#include "mod_loader.h"

#include "cave_story.h"
#include "Inputs.h"
#include "Networking.h"
#include "VirtualShoot.h"

const char* gameIp;
const char* gamePort;
const char* gamePlyrName;
bool japanese;
int mim_compatibility;
int show_player_names;
bool enable_map_calls;
bool hide_players_on_map;
bool hide_me_on_map;
bool im_being_held = false;
bool pause_window_on_lost_focus = false;
// I'm shooting a gun
bool my_shooting = false;
int my_soft_rensha = 0;

int networkStarted = 0;

const char* EngDisconnectedText = "Disconnected from Server.";
const char* EngPressPeriodText = "Press period to reconnect! (.)";

const char* JpnDisconnectedText = "\x83\x54\x81\x5B\x83\x6F\x81\x5B\x82\xA9\x82\xE7\x90\xD8\x92\x66\x82\xB3\x82\xEA\x82\xBD\x81\x42";
const char* JpnPressPeriodText = "\x83\x73\x83\x8A\x83\x49\x83\x68\x83\x4C\x81\x5B\x82\xF0\x89\x9F\x82\xB7\x82\xC6\x8D\xC4\x90\xDA\x91\xB1\x82\xB3\x82\xEA\x82\xDC\x82\xB7\x81\x42";

const char* DisconnectedText;
const char* PressPeriodText;

bool gTypingChat = false;

void HandleChat()
{
	static char chatMessage[PACKET_DATA];
	static RECT rcChatTypeArea = { 0, WINDOW_HEIGHT - CHAT_OFF_Y + CHAT_LINE_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT };

	if (gTypingChat == true)
	{
		gLastChatMessage = GetTickCount();

		if (strlen(gTypedText) > 0)
		{
			if (gTypedText[0] == '\x08')
			{
				if (strlen(chatMessage))
					chatMessage[strlen(chatMessage) - 1] = '\0';
			}
			else if (strlen(chatMessage) + strlen(gTypedText) < PACKET_DATA)
				strcat(chatMessage, gTypedText);
			PlaySoundObject(2, SOUND_MODE_PLAY);

			//Redraw text
			CortBox2(&rcChatTypeArea, 0x000000, SURFACE_ID_CHAT);

			char text[PACKET_DATA + 5];
			sprintf(text, "Say: %s_", chatMessage);
			PutText2(8, WINDOW_HEIGHT - CHAT_OFF_Y + CHAT_LINE_HEIGHT + 1, text, 0x110022, SURFACE_ID_CHAT);
			PutText2(8, WINDOW_HEIGHT - CHAT_OFF_Y + CHAT_LINE_HEIGHT, text, 0xFFFFFE, SURFACE_ID_CHAT);
		}

		if (gKeyTrg & KEY_ENTER)
		{
			if (strlen(chatMessage) > 0)
				SendChatMessage(NULL, chatMessage);
			memset(chatMessage, 0, PACKET_DATA);
			CortBox2(&rcChatTypeArea, 0x000000, SURFACE_ID_CHAT);
			gTypingChat = false;
		}
	}

	//Open chat when T is pressed
	if (gKeyTrg & KEY_T)
	{
		if (gTypingChat == false)
		{
			memset(chatMessage, 0, PACKET_DATA);
			gTypingChat = true;

			//Redraw text
			CortBox2(&rcChatTypeArea, 0x000000, SURFACE_ID_CHAT);
			PutText2(8, WINDOW_HEIGHT - CHAT_OFF_Y + CHAT_LINE_HEIGHT + 1, "Say: _", 0x110022, SURFACE_ID_CHAT);
			PutText2(8, WINDOW_HEIGHT - CHAT_OFF_Y + CHAT_LINE_HEIGHT, "Say: _", 0xFFFFFE, SURFACE_ID_CHAT);
		}
	}
}

void ServerHandler()
{
	if (InServer())
	{
		HandleClient();
		SetMyShooting();
		VirtualShootBullet();
	}
	else
		KillClient();
}

void CampLoop_GetTrg()
{
	ServerHandler();

	GetTrg();
}

void CampLoop_PutFramePerSecound()
{
	PutServer();

	PutFramePerSecound();
}

void ModeAction_GetTrg()
{
	CustomInputHandler();
	ChatInput();

	if (japanese != true)
	{
		DisconnectedText = EngDisconnectedText;
		PressPeriodText = EngPressPeriodText;
	}
	else
	{
		DisconnectedText = JpnDisconnectedText;
		PressPeriodText = JpnPressPeriodText;
	}

	if (networkStarted == 1 && !InServer())
	{
		// Period key pressed, reset network state.
		if (gKey & gKeyReconnect)
			networkStarted = 0;
	}

	if (networkStarted != 1)
	{
		InitNetworking();
		JoinServer(gameIp, gamePort, gamePlyrName);
		networkStarted = 1;
	}

	ServerHandler();

	GetTrg();
}

// 0x41483A
void MiniMapLoop_CortBox2(RECT *r, unsigned long c, SurfaceID s)
{
	CortBox2(r, c, s);
}

void MiniMapLoop_GetTrg()
{
	ServerHandler();

	GetTrg();
}

void MiniMapLoop_PutFramePerSecound()
{
	PutServer();

	PutFramePerSecound();
}

// 0x41498E
void MiniMapLoop_PutBitmapPlayer(RECT *v, int x, int y, RECT *r, SurfaceID s)
{
	// Bitmap
	PutBitmap3(v, x, y, r, s);

	RECT th_rect = { 0, 65, 1, 66 };

	RECT rcView;
	for (int f = 0; f <= 8; f++) {
		rcView.left =	((window_surface_width / mag) / 2) -  (((gMap->width * f) / 8) / 2);
		rcView.right =  ((window_surface_width / mag) / 2) +  (((gMap->width * f) / 8) / 2);
		rcView.top =	((window_surface_height / mag) / 2) - (((gMap->length * f) / 8) / 2);
		rcView.bottom = ((window_surface_height / mag) / 2) + (((gMap->length * f) / 8) / 2);
	}
	rcView.left -= 1;
	rcView.right = rcView.left + gMap->width + 2;
	rcView.top -= 1;
	rcView.bottom = rcView.top + gMap->length + 2;

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (!hide_players_on_map && (gVirtualPlayers[i].stage == gStageNo && gVirtualPlayers[i].hide_vp_on_map == false))
		{
			int th_x = (gVirtualPlayers[i].x / 0x200 + 8) / 16;
			int th_y = (gVirtualPlayers[i].y / 0x200 + 8) / 16;
			if ((gVirtualPlayers[i].cond & 0x80) && !(gVirtualPlayers[i].cond & 2))
				PutBitmap3(&grcGame, th_x + rcView.left + 1, th_y + rcView.top + 1, &th_rect, SURFACE_ID_TEXT_BOX);
		}
	}
}

void SelectStage_Loop_GetTrg()
{
	ServerHandler();

	GetTrg();
}

void SelectStage_Loop_PutFramePerSecound()
{
	PutServer();

	PutFramePerSecound();
}


void ModeAction_PutFramePerSecound()
{
	PutServer();

	if (gKey & gKeyChat)
		PutText(0, 64, "banger game", 0xFFFFFF);

	PutText(0, 80, gTypedText, 0xFFFFFF);

	if (!InServer())
	{
		PutText(0, 1, DisconnectedText, 0x000010);
		PutText(0, 1 - 1, DisconnectedText, 0xFFFFFF);

		PutText(0, 9, PressPeriodText, 0x000010);
		PutText(0, 9 - 1, PressPeriodText, 0xFFFFFF);
	}

	PutFramePerSecound();
}

void MakeCustomSurfaces(int x, int y, int s, BOOL r)
{
	MakeSurface_Generic(x, y, s, r);
	MakeSurface_Generic(WINDOW_WIDTH * 2, MAX_CLIENTS * 16, SURFACE_ID_USERNAME, FALSE);
	MakeSurface_Generic(WINDOW_WIDTH, WINDOW_HEIGHT, SURFACE_ID_CHAT, FALSE);
}

void InitMod(void)
{
	gameIp = ModLoader_GetSettingString("IP", "127.0.0.1");
	gamePort = ModLoader_GetSettingString("PORT", "28000");
	gamePlyrName = ModLoader_GetSettingString("PLAYER_NAME", "Player");
	japanese = ModLoader_GetSettingBool("JAPANESE", false);
	mim_compatibility = ModLoader_GetSettingInt("MIM_COMPATIBLITY", 0);
	show_player_names = ModLoader_GetSettingInt("NAME_DISPLAY", 0);
	enable_map_calls = ModLoader_GetSettingBool("ENABLE_MAP_SYSTEM_CODE", true);
	hide_players_on_map = ModLoader_GetSettingBool("HIDE_PLAYERS_ON_MAP", false);
	hide_me_on_map = ModLoader_GetSettingBool("HIDE_ME_ON_MAP", false);
	pause_window_on_lost_focus = ModLoader_GetSettingBool("PAUSE_WINDOW_ON_LOST_FOCUS", false);

	if (pause_window_on_lost_focus == false)
		ModLoader_WriteCall((void*)0x413316, (void*)ActiveWindow);

	ModLoader_WriteCall((void*)0x4115F0, (void*)MakeCustomSurfaces);
	// CampLoop replacement CALLs (run networking in inventory)
	ModLoader_WriteCall((void*)0x401DD8, (void*)CampLoop_GetTrg);
	ModLoader_WriteCall((void*)0x401E84, (void*)CampLoop_PutFramePerSecound);
	// ModeAction replacement CALLs (run networking in mode action instead of PutFlash)
	ModLoader_WriteCall((void*)0x4104D0, (void*)ModeAction_GetTrg);
	ModLoader_WriteCall((void*)0x410874, (void*)ModeAction_PutFramePerSecound);
	// MiniMapLoop replacement CALLs (run networking in minimap)
	if (enable_map_calls)
	{
		ModLoader_WriteCall((void*)0x41483A, (void*)MiniMapLoop_CortBox2);
		ModLoader_WriteCall((void*)0x4146BE, (void*)MiniMapLoop_GetTrg);
		ModLoader_WriteCall((void*)0x4147B8, (void*)MiniMapLoop_PutFramePerSecound);
		ModLoader_WriteCall((void*)0x41485A, (void*)MiniMapLoop_GetTrg);
		ModLoader_WriteCall((void*)0x41498E, (void*)MiniMapLoop_PutBitmapPlayer);
		ModLoader_WriteCall((void*)0x414996, (void*)MiniMapLoop_PutFramePerSecound);
		ModLoader_WriteCall((void*)0x4149D6, (void*)MiniMapLoop_GetTrg);
		ModLoader_WriteCall((void*)0x414AD0, (void*)MiniMapLoop_PutFramePerSecound);
	}
	// SelectStage_Loop replacement CALLs (run networking in teleporter menu)
	ModLoader_WriteCall((void*)0x41DA88, (void*)SelectStage_Loop_GetTrg);
	ModLoader_WriteCall((void*)0x41DB6F, (void*)SelectStage_Loop_PutFramePerSecound);

	//Hooking into the end of PutBullet
	ModLoader_WriteByte((void*)0x403F65, 0xC9); //write LEAVE
	ModLoader_WriteWordBE((void*)0x403F66, 0xEB11); //write short JMP to get past the switch table
	ModLoader_WriteJump((void*)0x403F79, (void*)PutVirtualPlayers); //JMP to PutVirtualPlayers instead of returning
}
