// Quote movement function base mod for Freeware Cave Story
// Copyright � 2017 Clownacy
// Copyright � 2019 Cucky

#include <windows.h>

#include "mod_loader.h"

#include "cs.h"
#include "cave_story.h"

#include "Networking.h"
#include "Server.h"

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

	CS_MakeSurface_Generic(CS_window_surface_width * 2, MAX_CLIENTS * 16, CS_SURFACE_ID_UNKNOWN_4);
}

void InactiveWindow()
{
	// nothing lol
}

static void SetWindowName(HWND hWnd)
{
	// CS_MakeSurface_Generic(CS_window_surface_width * 2, MAX_CLIENTS * 16, CS_SURFACE_ID_UNKNOWN_4);
	char* window_name;

	window_name = "CS Freeware Online";
	InitNetworking();
	JoinServer("10.0.0.75", "28000", "Freeware");
	SetWindowTextA(hWnd, window_name);
}

void ActStar()
{
	if (InServer())
		HandleClient();
	if (!(IsHosting() || InServer()))
		return ServerDisconnect();
}


void InitMod(void)
{
	ModLoader_WriteJump((void*)0x40AE30, (void*)DefaultConfigData);
	ModLoader_WriteJump((void*)0x412320, (void*)SetWindowName);
	ModLoader_WriteJump((void*)0x412BC0, (void*)InactiveWindow);
	ModLoader_WriteJump((void*)0x421040, (void*)ActStar);
}