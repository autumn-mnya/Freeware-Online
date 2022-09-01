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
int mim_compatibility;
int show_player_names;

int frame_x = 0;
int frame_y = 0;

void ServerHandler()
{
	if (InServer())
		HandleClient();
	else
		KillClient();
}

// ok but actually this is nice
void InactiveWindow()
{
	// nothing lol
}

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
		if (gKey & KEY_ALT_DOWN)
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

	ServerHandler();
	PutServer();
}


void InitMod(void)
{
	gameIp = ModLoader_GetSettingString("IP", "127.0.0.1");
	gamePort = ModLoader_GetSettingString("PORT", "28000");
	gamePlyrName = ModLoader_GetSettingString("PLAYER_NAME", "Player");
	japanese = ModLoader_GetSettingBool("JAPANESE", false);
	mim_compatibility = ModLoader_GetSettingInt("MIM_Compatibility", 0);
	show_player_names = ModLoader_GetSettingInt("NAME_DISPLAY", 0);

	ModLoader_WriteJump((void*)0x412BC0, (void*)InactiveWindow);
	
	//Hooking into the end of PutBullet
	ModLoader_WriteByte((void*)0x403F65, 0xC9); //write LEAVE
	ModLoader_WriteWordBE((void*)0x403F66, 0xEB11); //write short JMP to get past the switch table
	ModLoader_WriteJump((void*)0x403F79, (void*)PutVirtualPlayers); //JMP to PutVirtualPlayers instead of returning
	
	ModLoader_WriteJump((void*)0x40EE20, (void*)PutFlash);
}
