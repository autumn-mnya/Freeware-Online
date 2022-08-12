#pragma once

#include <windows.h>

//player variables
struct player3
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

player3* Player3 = (player3*)0x49E638;
