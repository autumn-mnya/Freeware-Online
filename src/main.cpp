#include <windows.h>
#include <string>

#include "mod_loader.h"

#include "cave_story.h"
#include "main.h"
#include "Networking.h"

#include "AutPI.h"

const char* gameIp;
const char* gamePort;
const char* gamePlyrName;
bool networking = true;
bool japanese;
int mim_compatibility;
int show_player_names;
bool hide_players_on_map;
bool hide_me_on_map;
bool im_being_held = false;
bool pause_window_on_lost_focus = false;
bool show_players_hitboxes = false;
bool enable_deathlink = false;
bool enable_deathlink_on_death = false;

int networkStarted = 0;

const char* EngDisconnectedText = "Disconnected from Server.";
const char* EngPressPeriodText = "Press period to reconnect! (.)";

const char* JpnDisconnectedText = "\x83\x54\x81\x5B\x83\x6F\x81\x5B\x82\xA9\x82\xE7\x90\xD8\x92\x66\x82\xB3\x82\xEA\x82\xBD\x81\x42";
const char* JpnPressPeriodText = "\x83\x73\x83\x8A\x83\x49\x83\x68\x83\x4C\x81\x5B\x82\xF0\x89\x9F\x82\xB7\x82\xC6\x8D\xC4\x90\xDA\x91\xB1\x82\xB3\x82\xEA\x82\xDC\x82\xB7\x81\x42";

const char* DisconnectedText;
const char* PressPeriodText;

int gCurrentGameMode = 0;

void SetModeOpening()
{
	gCurrentGameMode = 1;
}

void SetModeTitle()
{
	gCurrentGameMode = 2;
}

void SetModeAction()
{
	gCurrentGameMode = 3;
}

void PlayerDeath()
{
	PlaySoundObject(17, SOUND_MODE_PLAY);
	gMC.cond = 0;
	SetDestroyNpChar(gMC.x, gMC.y, 10 * 0x200, 0x40);
	StartTextScript(40);
}

void ServerHandler()
{
	if (InServer())
		HandleClient();
	else
		KillClient();
}

// 0x41483A
void MiniMapLoop_CortBox2(RECT *r, unsigned long c, SurfaceID s)
{
	CortBox2(r, c, s);
}

// 0x41498E
void MiniMapLoop_PutBitmapPlayer(RECT *v, int x, int y, RECT *r, SurfaceID s)
{
	// Bitmap
	PutBitmap3(v, x, y, r, s);

	RECT th_rect = { 0, 65, 1, 66 };

	RECT rcView;
	for (int f = 0; f <= 8; f++) {
		rcView.left =	(WINDOW_WIDTH / 2) -  (((gMap.width * f) / 8) / 2);
		rcView.right =  (WINDOW_WIDTH / 2) +  (((gMap.width * f) / 8) / 2);
		rcView.top =	(WINDOW_HEIGHT / 2) - (((gMap.length * f) / 8) / 2);
		rcView.bottom = (WINDOW_HEIGHT / 2) + (((gMap.length * f) / 8) / 2);
	}
	rcView.left -= 1;
	rcView.right = rcView.left + gMap.width + 2;
	rcView.top -= 1;
	rcView.bottom = rcView.top + gMap.length + 2;

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

void Netplay_GetTrg()
{
	// only do this if we're in ModeAction
	if (gCurrentGameMode == 3)
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

		if (networkStarted != 1)
		{
			InitNetworking();
			JoinServer(gameIp, gamePort, gamePlyrName);
			networkStarted = 1;
		}
	}

	ServerHandler();
}

void Netplay_PutFPS()
{
	PutServer();

	// only do this if we're in mode action
	if (gCurrentGameMode == 3)
	{
		if (!InServer())
		{
			PutText(0, 1, DisconnectedText, 0x000010);
			PutText(0, 1 - 1, DisconnectedText, 0xFFFFFF);

			PutText(0, 9, PressPeriodText, 0x000010);
			PutText(0, 9 - 1, PressPeriodText, 0xFFFFFF);
		}
	}
}

void MakeCustomSurfaces(int x, int y, int s, BOOL r)
{
	MakeSurface_Generic(x, y, s, r);
	MakeSurface_Generic(WINDOW_WIDTH * 2, MAX_CLIENTS * 16, SURFACE_ID_USERNAME, FALSE);
}

// 0x419B40 -- StartTextScript(40);

void DamageMyChar_Death(int event)
{
	SendMyDeathPacket();
	StartTextScript(event);
}

// 0x416A0D -- StartTextScript(41)
void AirProcess_Drown(int event)
{
	SendMyDeathPacket();
	StartTextScript(event);
}

int frax = 0, fray = 0;

void Netplay_DrawVirtualPlayers()
{
	GetFramePosition(&frax, &fray);
	PutVirtualPlayers(frax, fray);
}

void InitMod(void)
{
	LoadAutPiDll();
	networking = ModLoader_GetSettingBool("Networking Enabled", true);
	gameIp = ModLoader_GetSettingString("IP", "127.0.0.1");
	gamePort = ModLoader_GetSettingString("Port", "28000");
	gamePlyrName = ModLoader_GetSettingString("Player Name", "Player");
	japanese = ModLoader_GetSettingBool("Japanese Text", false);
	mim_compatibility = ModLoader_GetSettingInt("<MIM Compatibility", 0);
	show_player_names = ModLoader_GetSettingInt("Name Display Setting", 0);
	hide_players_on_map = ModLoader_GetSettingBool("Hide Players on Map", false);
	hide_me_on_map = ModLoader_GetSettingBool("Hide Me on Map", false);
	pause_window_on_lost_focus = ModLoader_GetSettingBool("Pause Window on Lost Focus", false);
	show_players_hitboxes = ModLoader_GetSettingBool("Show Players Hitboxes", false);
	enable_deathlink = ModLoader_GetSettingBool("Enable Deathlink", false);
	enable_deathlink_on_death = ModLoader_GetSettingBool("Enable Deathlink on My Death", false);

	if (networking)
	{

		if (pause_window_on_lost_focus == false)
			ModLoader_WriteCall((void*)0x413316, (void*)ActiveWindow);

		ModLoader_WriteCall((void*)0x4115F0, (void*)MakeCustomSurfaces);
		// CampLoop replacement CALLs (run networking in inventory)
		// ModLoader_WriteCall((void*)0x401DD8, (void*)CampLoop_GetTrg);
		// ModLoader_WriteCall((void*)0x401E84, (void*)CampLoop_PutFramePerSecound);
		// ModeAction replacement CALLs (run networking in mode action instead of PutFlash)
		// ModLoader_WriteCall((void*)0x4104D0, (void*)ModeAction_GetTrg);
		// ModLoader_WriteCall((void*)0x410874, (void*)ModeAction_PutFramePerSecound);
		// MiniMapLoop replacement CALLs (run networking in minimap)
		ModLoader_WriteCall((void*)0x41483A, (void*)MiniMapLoop_CortBox2);
		// ModLoader_WriteCall((void*)0x4146BE, (void*)MiniMapLoop_GetTrg);
		// ModLoader_WriteCall((void*)0x4147B8, (void*)MiniMapLoop_PutFramePerSecound);
		// ModLoader_WriteCall((void*)0x41485A, (void*)MiniMapLoop_GetTrg);
		ModLoader_WriteCall((void*)0x41498E, (void*)MiniMapLoop_PutBitmapPlayer);
		// ModLoader_WriteCall((void*)0x414996, (void*)MiniMapLoop_PutFramePerSecound);
		// ModLoader_WriteCall((void*)0x4149D6, (void*)MiniMapLoop_GetTrg);
		// ModLoader_WriteCall((void*)0x414AD0, (void*)MiniMapLoop_PutFramePerSecound);
		// SelectStage_Loop replacement CALLs (run networking in teleporter menu)
		// ModLoader_WriteCall((void*)0x41DA88, (void*)SelectStage_Loop_GetTrg);
		// ModLoader_WriteCall((void*)0x41DB6F, (void*)SelectStage_Loop_PutFramePerSecound);

		RegisterGetTrgElement(Netplay_GetTrg);
		RegisterPutFPSElement(Netplay_PutFPS);

		//Hooking into the end of PutBullet
		// ModLoader_WriteByte((void*)0x403F65, 0xC9); //write LEAVE
		// ModLoader_WriteWordBE((void*)0x403F66, 0xEB11); //write short JMP to get past the switch table
		// ModLoader_WriteJump((void*)0x403F79, (void*)PutVirtualPlayers); //JMP to PutVirtualPlayers instead of returning
		RegisterBelowPlayerElement(Netplay_DrawVirtualPlayers);

		// Death-Link
		if (enable_deathlink_on_death)
		{
			ModLoader_WriteCall((void*)0x419B40, (void*)DamageMyChar_Death);
			ModLoader_WriteCall((void*)0x416A0D, (void*)AirProcess_Drown);
		}

		// do not do this
		// InitExperiment_NPCSync();
	}

	// jank way of getting mode
	RegisterOpeningInitElement(SetModeOpening);
	RegisterTitleInitElement(SetModeTitle);
	RegisterInitElement(SetModeAction);

	RegisterLuaFuncElement(SetNetplayLua);
}
