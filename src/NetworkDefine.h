#pragma once
#include <stdint.h>

#define MAX_NAME 0x14
#define NAME_MIN 2

#define NET_VERSION 6

#define TICKRATE 60
#define MAX_CLIENTS 0x80
#define VIRTUAL_PLAYER_TIMEOUT 2000

#define PACKET_DATA 0x1000

#define CHAT_OFF_Y 32
#define CHAT_LINE_HEIGHT 7

enum CONNECT_CODES
{
	CONNECT_NORMAL,
};

enum DISCONNECT_CODES
{
	DISCONNECT_FORCE,
};

enum PACKET_CODES
{
	PACKETCODE_DEFINE_PLAYER,
	PACKETCODE_CHAT_MESSAGE,
	PACKETCODE_REPLICATE_PLAYER,
	PACKETCODE_SKIN,
};

struct VIRTUAL_PLAYER
{
	int cond;
	int unit;
	int flag;
	char name[MAX_NAME];
	int timeout;
	
	//Position
	int x;
	int y;
	int lerpX;
	int lerpY;
	int lerpTick;
	
	//Visual
	int up;
	int down;
	int arms;
	int equip;
	int ani_no;
	int direct;
	int shock;
	int shockT;
	int bubble;
	int stage;
};

struct PACKET
{
	uint32_t netVersion;
	uint32_t code;
	uint8_t data[PACKET_DATA];
};

struct CLIENT
{
	void *peer;
	char name[MAX_NAME];
	uint8_t *skinData;
	uint32_t skinSize;
};
