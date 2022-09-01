#pragma once

struct stageTbl
{
	char parts[0x20];
	char map[0x20];
	int bkType;
	char back[0x20];
	char npc[0x20];
	char boss[0x20];
	signed char boss_no;
	char name[0x20];
};

stageTbl* StageTbl = (stageTbl*)(*(unsigned*)0x420c2f);