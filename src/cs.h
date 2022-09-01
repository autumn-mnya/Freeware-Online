#pragma once
#include <windows.h>

//functions
typedef void CSplaySFX(const int soundID, const int channel);
CSplaySFX* playSFX = (CSplaySFX*)0x420640;

typedef void CSDamageMyChar(const int damage);
CSDamageMyChar* DamageMyChar = (CSDamageMyChar*)0x419910;

struct NPC
{
	BYTE cond;
	int flag;
	int x;
	int y;
	int xm;
	int ym;
	int xm2;
	int ym2;
	int tgt_x;
	int tgt_y;
	int code_char;
	int code_flag;
	int code_event;
	int surf;
	int hit_voice;
	int destroy_voice;
	int life;
	int exp;
	int size;
	int direct;
	unsigned __int16 bits;
	RECT rect;
	int ani_wait;
	int ani_no;
	int count1;
	int count2;
	int act_no;
	int act_wait;
	RECT hit;
	RECT view;
	BYTE shock;
	int damage_view;
	int damage;
	NPC *pNpc;
};

typedef void CScreateEntity(
	const int entityID,
	const int x,
	const int y,
	const int xvel,
	const int yvel,
	const int Direction,
	NPC* Parent,
	const int slot);

CScreateEntity* createEntity = (CScreateEntity*)0x46EFD0;
typedef void CScreateEffect(const int x, const int y, const int ID, const int mode);
CScreateEffect* createEffect = (CScreateEffect*)0x40AC90;
typedef int CScheckTSCflag(const int flag);
CScheckTSCflag* checkFlag = (CScheckTSCflag*)0x40E930;
typedef int CSgetTileID(const int tileX, const int tileY);
CSgetTileID* getTileID = (CSgetTileID*)0x4139A0;
typedef void CSrunEVE(const int event_num);
CSrunEVE* runEvent = (CSrunEVE*)0x421990;
typedef int CSrandom(const int min, const int max);
CSrandom* random = (CSrandom*)0x40F350;
typedef void CSexplosion(const int x, const int y, const int range, const int num_smoke);
CSexplosion* explosion = (CSexplosion*)0x46F150;

//player variables
struct player
{
	unsigned __int8 cond;
	unsigned int flag;
	int direct;
	int up;
	int down;
	int unit;
	int equip;
	int x;
	int y;
	int tgt_x;
	int tgt_y;
	int index_x;
	int index_y;
	int xm;
	int ym;
	int ani_wait;
	int ani_no;
	RECT hit;
	RECT view;
	RECT rect;
	RECT rect_arms;
	int level;
	int exp_wait;
	int exp_count;
	unsigned __int8 shock;
	unsigned __int8 no_life;
	unsigned __int8 rensha;
	unsigned __int8 bubble;
	__int16 life;
	__int16 star;
	__int16 max_life;
	__int16 a;
	int lifeBr;
	int lifeBr_count;
	int air;
	int air_get;
	char sprash;
	char ques;
	char boost_sw;
	int boost_cnt;
};

player *Player = (player*)0x49E638;

int *g_GameFlags = (int*)0x49E1E8;

#define TILE2COORD(tile)	tile << 13
#define PIXEL2COORD(pixel)	pixel << 9
