// Copyright © 2017 Clownacy
// Copyright © 2019 Cucky

#include <windows.h>

#include "mod_loader.h"

// #include "cs.h"
#include "cave_story.h"
#include "playermain.h"
#include "Networking.h"
#include "Server.h"

const char* gameIp;
const char* gamePort;
const char* gamePlyrName;
bool japanese;

int* gKKey = (int*)0x49E210;

void ServerDisconnect()
{
	if (IsHosting())
		KillServer();
	if (InServer())
		KillClient();
}

//0x40AE30
void DefaultConfigData(CS_ConfigData *conf)
{
	//Claer old config data
	memset(conf, 0, sizeof(CS_ConfigData));

	conf->window_size = 2;

	//Reset joystick settings (as these can't simply be set to 0)
	conf->gamepad_enabled = 1;
	conf->gamepad_buttons[0] = 2;
	conf->gamepad_buttons[1] = 1;
	conf->gamepad_buttons[2] = 5;
	conf->gamepad_buttons[3] = 6;
	conf->gamepad_buttons[4] = 3;
	conf->gamepad_buttons[5] = 4;
	conf->gamepad_buttons[6] = 6;
	conf->gamepad_buttons[7] = 3;
}

int frame_x = 0;
int frame_y = 0;

// ok but actually this is nice
void InactiveWindow()
{
	// nothing lol
}

// Idk why I do this here tbh

/*
static void SetWindowName(HWND hWnd)
{
	CS_MakeSurface_Generic(CS_window_surface_width * 2, MAX_CLIENTS * 16, CS_SURFACE_ID_UNKNOWN_12);
	// CS_MakeSurface_Generic(CS_window_surface_width * 2, MAX_CLIENTS * 16, CS_SURFACE_ID_UNKNOWN_4);
	char* window_name;
	window_name = "CS Freeware Online";
	SetWindowTextA(hWnd, window_name);
}
*/


// Handles the connection instead of whimsical star lol
/*
void ActStar()
{

}
*/

int networkStarted = 0;
RECT rcDrownedChar = { 32, 80, 48, 96 };

const char* EngDisconnectedText = "Disconnected from Server.";
const char* EngPressPeriodText = "Press period to reconnect! (.)";

const char* JpnDisconnectedText = "\x83\x54\x81\x5B\x83\x6F\x81\x5B\x82\xA9\x82\xE7\x90\xD8\x92\x66\x82\xB3\x82\xEA\x82\xBD\x81\x42";
const char* JpnPressPeriodText = "\x83\x73\x83\x8A\x83\x49\x83\x68\x83\x4C\x81\x5B\x82\xF0\x89\x9F\x82\xB7\x82\xC6\x8D\xC4\x90\xDA\x91\xB1\x82\xB3\x82\xEA\x82\xDC\x82\xB7\x81\x42";

const char* DisconnectedText;
const char* PressPeriodText;

// Puts the players because idk how to shove this above PutMyChar
void PutFlash(void)
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
		if (*gKKey & 0x20000)
			networkStarted = 0;
	}

	if (networkStarted != 1)
	{
		InitNetworking();
		JoinServer(gameIp, gamePort, gamePlyrName);
		if (InServer())
			networkStarted = 1;
	}

	if (!InServer())
	{
		CS_PutText(0, 1, DisconnectedText, 0x000010);
		CS_PutText(0, 1 - 1, DisconnectedText, 0xFFFFFF);

		CS_PutText(0, 9, PressPeriodText, 0x000010);
		CS_PutText(0, 9 - 1, PressPeriodText, 0xFFFFFF);
	}

	CS_GetFramePosition(&frame_x, &frame_y);

	if (InServer())
	{
		HandleClient();
	}
	else
	{
		KillClient();
	}

	PutServer();
}


void InitMod(void)
{
	gameIp = ModLoader_GetSettingString("IP", "127.0.0.1");
	gamePort = ModLoader_GetSettingString("PORT", "25565");
	gamePlyrName = ModLoader_GetSettingString("PLAYER_NAME", "Player");
	japanese = ModLoader_GetSettingBool("JAPANESE", false);

	ModLoader_WriteJump((void*)0x40AE30, (void*)DefaultConfigData);
	// ModLoader_WriteJump((void*)0x412320, (void*)SetWindowName);
	ModLoader_WriteJump((void*)0x412BC0, (void*)InactiveWindow);
	
	//Hooking into the end of PutBullet
	ModLoader_WriteByte((void*)0x403F65, 0xC9); //write LEAVE
	ModLoader_WriteWordBE((void*)0x403F66, 0xEB11); //write short JMP to get past the switch table
	ModLoader_WriteJump((void*)0x403F79, (void*)PutVirtualPlayers); //JMP to PutVirtualPlayers instead of returning
	
	// ModLoader_WriteJump((void*)0x421040, (void*)ActStar);
	ModLoader_WriteJump((void*)0x40EE20, (void*)PutFlash);
}
