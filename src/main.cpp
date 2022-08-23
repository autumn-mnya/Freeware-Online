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

// Puts the players because idk how to shove this above PutMyChar
void PutFlash(void)
{
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
		networkStarted = 1;
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
