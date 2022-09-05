// Copyright © 2017 Clownacy
// Copyright © 2019 Cucky

#include <windows.h>
#include <string>

#include "mod_loader.h"

// #include "cs.h"
#include "cave_story.h"
#include "playermain.h"
#include "Map.h"
#include "Networking.h"

const char* gameIp;
const char* gamePort;
const char* gamePlyrName;
bool japanese;
int mim_compatibility;
int show_player_names;
bool hide_players_on_map;
bool hide_me_on_map;
bool im_being_held = false;

int networkStarted = 0;

const char* EngDisconnectedText = "Disconnected from Server.";
const char* EngPressPeriodText = "Press period to reconnect! (.)";

const char* JpnDisconnectedText = "\x83\x54\x81\x5B\x83\x6F\x81\x5B\x82\xA9\x82\xE7\x90\xD8\x92\x66\x82\xB3\x82\xEA\x82\xBD\x81\x42";
const char* JpnPressPeriodText = "\x83\x73\x83\x8A\x83\x49\x83\x68\x83\x4C\x81\x5B\x82\xF0\x89\x9F\x82\xB7\x82\xC6\x8D\xC4\x90\xDA\x91\xB1\x82\xB3\x82\xEA\x82\xDC\x82\xB7\x81\x42";

const char* DisconnectedText;
const char* PressPeriodText;

void ServerHandler()
{
	if (InServer())
		HandleClient();
	else
		KillClient();
}

void CampLoop_GetTrg()
{
	ServerHandler();

	CS_GetTrg();
}

void CampLoop_PutFramePerSecound()
{
	PutServer();

	CS_PutFramePerSecound();
}

void ModeAction_GetTrg()
{
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
		if (gKey & KEY_ALT_DOWN)
			networkStarted = 0;
	}

	// Holding a player code
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].stage == gStageNo && gVirtualPlayers[i].is_being_held == false)
		{
			if (gVirtualPlayers[i].y - gVirtualPlayers[i].hit.top < (Player3->y + Player3->hit.bottom) &&
				gVirtualPlayers[i].y + gVirtualPlayers[i].hit.bottom >(Player3->y - Player3->hit.top) &&
				gVirtualPlayers[i].x - gVirtualPlayers[i].hit.left < (Player3->x + Player3->hit.right) &&
				gVirtualPlayers[i].x + gVirtualPlayers[i].hit.right >(Player3->x - Player3->hit.left) &&
				(gKeyTrg & gKeyDown))
			{
				gVirtualPlayers[i].x = Player3->x;
				gVirtualPlayers[i].y = Player3->y - (16 * 0x200);
				gVirtualPlayers[i].is_being_held = true;
			}
		}
		else if (gVirtualPlayers[i].stage == gStageNo && gVirtualPlayers[i].is_being_held == true)
		{
			if (gKeyTrg & gKeyDown)
			{
				gVirtualPlayers[i].x = Player3->x;
				gVirtualPlayers[i].y = Player3->y;
				gVirtualPlayers[i].is_being_held = false;
			}
		}

		if (im_being_held == true)
		{
			// i don't know how to do networking code, but if "im being held", then i should go ABOVE the player whos holding me's head??
			// idk how this works lol just please work please work pl

			Player3->x = gVirtualPlayers[i].x;
			Player3->y = gVirtualPlayers[i].y - (16 * 0x200);
		}
	}

	if (networkStarted != 1)
	{
		InitNetworking();
		JoinServer(gameIp, gamePort, gamePlyrName);
		networkStarted = 1;
	}

	ServerHandler();

	CS_GetTrg();
}

// 0x41483A
void MiniMapLoop_CortBox2(RECT *r, unsigned long c, CS_SurfaceID s)
{
	CS_CortBox2(r, c, s);
}

void MiniMapLoop_GetTrg()
{
	ServerHandler();

	CS_GetTrg();
}

void MiniMapLoop_PutFramePerSecound()
{
	PutServer();

	CS_PutFramePerSecound();
}

// 0x41498E
void MiniMapLoop_PutBitmapPlayer(RECT *v, int x, int y, RECT *r, CS_SurfaceID s)
{
	// Bitmap
	CS_PutBitmap3(v, x, y, r, s);

	RECT th_rect = { 0, 65, 1, 66 };

	RECT rcView;
	for (int f = 0; f <= 8; f++) {
		rcView.left =	((CS_window_surface_width / CS_window_upscale) / 2) -  (((gMap->width * f) / 8) / 2);
		rcView.right =  ((CS_window_surface_width / CS_window_upscale) / 2) +  (((gMap->width * f) / 8) / 2);
		rcView.top =	((CS_window_surface_height / CS_window_upscale) / 2) - (((gMap->length * f) / 8) / 2);
		rcView.bottom = ((CS_window_surface_height / CS_window_upscale) / 2) + (((gMap->length * f) / 8) / 2);
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
				CS_PutBitmap3(&grcGame, th_x + rcView.left + 1, th_y + rcView.top + 1, &th_rect, CS_SURFACE_ID_TEXT_BOX);
		}
	}
}

void SelectStage_Loop_GetTrg()
{
	ServerHandler();

	CS_GetTrg();
}

void SelectStage_Loop_PutFramePerSecound()
{
	PutServer();

	CS_PutFramePerSecound();
}


void ModeAction_PutFramePerSecound()
{
	PutServer();

	if (!InServer())
	{
		CS_PutText(0, 1, DisconnectedText, 0x000010);
		CS_PutText(0, 1 - 1, DisconnectedText, 0xFFFFFF);

		CS_PutText(0, 9, PressPeriodText, 0x000010);
		CS_PutText(0, 9 - 1, PressPeriodText, 0xFFFFFF);
	}

	CS_PutFramePerSecound();
}

void MakeCustomSurfaces(int x, int y, int s, BOOL r)
{
	CS_MakeSurface_Generic(x, y, s, r);
	CS_MakeSurface_Generic(CS_WINDOW_WIDTH * 2, MAX_CLIENTS * 16, CS_SURFACE_ID_USERNAME, FALSE);
}

// ok but actually this is nice
void InactiveWindow()
{
	// nothing lol
}

void InitMod(void)
{
	gameIp = ModLoader_GetSettingString("IP", "127.0.0.1");
	gamePort = ModLoader_GetSettingString("PORT", "28000");
	gamePlyrName = ModLoader_GetSettingString("PLAYER_NAME", "Player");
	japanese = ModLoader_GetSettingBool("JAPANESE", false);
	mim_compatibility = ModLoader_GetSettingInt("MIM_COMPATIBLITY", 0);
	show_player_names = ModLoader_GetSettingInt("NAME_DISPLAY", 0);
	hide_players_on_map = ModLoader_GetSettingBool("HIDE_PLAYERS_ON_MAP", false);
	hide_me_on_map = ModLoader_GetSettingBool("HIDE_ME_ON_MAP", false);

	ModLoader_WriteJump((void*)0x412BC0, (void*)InactiveWindow);
	ModLoader_WriteCall((void*)0x4115F0, (void*)MakeCustomSurfaces);
	// CampLoop replacement CALLs (run networking in inventory)
	ModLoader_WriteCall((void*)0x401DD8, (void*)CampLoop_GetTrg);
	ModLoader_WriteCall((void*)0x401E84, (void*)CampLoop_PutFramePerSecound);
	// ModeAction replacement CALLs (run networking in mode action instead of PutFlash)
	ModLoader_WriteCall((void*)0x4104D0, (void*)ModeAction_GetTrg);
	ModLoader_WriteCall((void*)0x410874, (void*)ModeAction_PutFramePerSecound);
	// MiniMapLoop replacement CALLs (run networking in minimap)
	ModLoader_WriteCall((void*)0x41483A, (void*)MiniMapLoop_CortBox2);
	ModLoader_WriteCall((void*)0x4146BE, (void*)MiniMapLoop_GetTrg);
	ModLoader_WriteCall((void*)0x4147B8, (void*)MiniMapLoop_PutFramePerSecound);
	ModLoader_WriteCall((void*)0x41485A, (void*)MiniMapLoop_GetTrg);
	ModLoader_WriteCall((void*)0x41498E, (void*)MiniMapLoop_PutBitmapPlayer);
	ModLoader_WriteCall((void*)0x414996, (void*)MiniMapLoop_PutFramePerSecound);
	ModLoader_WriteCall((void*)0x4149D6, (void*)MiniMapLoop_GetTrg);
	ModLoader_WriteCall((void*)0x414AD0, (void*)MiniMapLoop_PutFramePerSecound);
	// SelectStage_Loop replacement CALLs (run networking in teleporter menu)
	ModLoader_WriteCall((void*)0x41DA88, (void*)SelectStage_Loop_GetTrg);
	ModLoader_WriteCall((void*)0x41DB6F, (void*)SelectStage_Loop_PutFramePerSecound);

	//Hooking into the end of PutBullet
	ModLoader_WriteByte((void*)0x403F65, 0xC9); //write LEAVE
	ModLoader_WriteWordBE((void*)0x403F66, 0xEB11); //write short JMP to get past the switch table
	ModLoader_WriteJump((void*)0x403F79, (void*)PutVirtualPlayers); //JMP to PutVirtualPlayers instead of returning
}
