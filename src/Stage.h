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

stageTbl* StageTbl = (stageTbl*)0x4937B0;

//so I think if you do
stageTbl* MySuperAwesomeTable = (stageTbl*)0x420C2F;
//or
stageTbl* MySuperAwesomeTable2 = (stageTbl*)0x420C73;
//Then you'll get the proper table...?
//My pointer syntax might be a little :whack: though...