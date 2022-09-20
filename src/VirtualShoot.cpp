#include "VirtualShoot.h"

#include "cave_story.h"
#include "main.h"
#include "NetworkDefine.h"
#include "Networking.h"
#include <Windows.h>

// Virtual Players Max Bullets
BULLET gVul[BULLET_MAX * MAX_CLIENTS];

void SetVirtualBullet(int no, int x, int y, int dir)
{
	int i = 0;
	while (i < (BULLET_MAX * MAX_CLIENTS) && gVul[i].cond & 0x80)
		++i;

	if (i >= BULLET_MAX * MAX_CLIENTS)
		return;

	memset(&gVul[i], 0, sizeof(BULLET));
	gVul[i].code_bullet = no;
	gVul[i].cond = 0x80;
	gVul[i].direct = dir;
	gVul[i].damage = gBulTbl[no].damage;
	gVul[i].life = gBulTbl[no].life;
	gVul[i].life_count = gBulTbl[no].life_count;
	gVul[i].bbits = gBulTbl[no].bbits;
	gVul[i].enemyXL = gBulTbl[no].enemyXL * 0x200;
	gVul[i].enemyYL = gBulTbl[no].enemyYL * 0x200;
	gVul[i].blockXL = gBulTbl[no].blockXL * 0x200;
	gVul[i].blockYL = gBulTbl[no].blockYL * 0x200;
	gVul[i].view.back = gBulTbl[no].view.back * 0x200;
	gVul[i].view.front = gBulTbl[no].view.front * 0x200;
	gVul[i].view.top = gBulTbl[no].view.top * 0x200;
	gVul[i].view.bottom = gBulTbl[no].view.bottom * 0x200;
	gVul[i].x = x;
	gVul[i].y = y;
}

// Test function replacement
void CS_SetBullet(int no, int x, int y, int dir)
{
	int i = 0;
	while (i < BULLET_MAX && gBul[i].cond & 0x80)
		++i;

	if (i >= BULLET_MAX)
		return;

	memset(&gBul[i], 0, sizeof(BULLET));
	gBul[i].code_bullet = no;
	gBul[i].cond = 0x80;
	gBul[i].direct = dir;
	gBul[i].damage = gBulTbl[no].damage;
	gBul[i].life = gBulTbl[no].life;
	gBul[i].life_count = gBulTbl[no].life_count;
	gBul[i].bbits = gBulTbl[no].bbits;
	gBul[i].enemyXL = gBulTbl[no].enemyXL * 0x200;
	gBul[i].enemyYL = gBulTbl[no].enemyYL * 0x200;
	gBul[i].blockXL = gBulTbl[no].blockXL * 0x200;
	gBul[i].blockYL = gBulTbl[no].blockYL * 0x200;
	gBul[i].view.back = gBulTbl[no].view.back * 0x200;
	gBul[i].view.front = gBulTbl[no].view.front * 0x200;
	gBul[i].view.top = gBulTbl[no].view.top * 0x200;
	gBul[i].view.bottom = gBulTbl[no].view.bottom * 0x200;
	gBul[i].x = x;
	gBul[i].y = y;
}

void VPShootBullet_Snake(int level)
{
	int bul_no;

	switch (level)
	{
		case 1:
			bul_no = 1;
			break;

		case 2:
			bul_no = 2;
			break;

		case 3:
			bul_no = 3;
			break;
	}

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].up)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y - (10 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y - (10 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y - (10 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y - (10 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else if (gVirtualPlayers[i].down)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y + (10 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y + (10 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y + (10 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y + (10 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (6 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), 0);
				SetCaret(gVirtualPlayers[i].x - (12 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (6 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), 2);
				SetCaret(gVirtualPlayers[i].x + (12 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
	}

	PlaySoundObject(33, SOUND_MODE_PLAY);
}

void VPShootBullet_PolarStar(int level)
{
	int bul_no;

	switch (level)
	{
		case 1:
			bul_no = 4;
			break;

		case 2:
			bul_no = 5;
			break;

		case 3:
			bul_no = 6;
			break;
	}

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].up)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else if (gVirtualPlayers[i].down)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (6 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 0);
				SetCaret(gVirtualPlayers[i].x - (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (6 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 2);
				SetCaret(gVirtualPlayers[i].x + (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
	}

		if (level == 3)
			PlaySoundObject(49, SOUND_MODE_PLAY);
		else
			PlaySoundObject(32, SOUND_MODE_PLAY);
}

void VPShootBullet_FireBall(int level)
{
	int bul_no;

	switch (level)
	{
		case 1:
			bul_no = 7;
			break;

		case 2:
			bul_no = 8;
			break;

		case 3:
			bul_no = 9;
			break;
	}

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].up)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (4 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x - (4 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (4 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x + (4 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else if (gVirtualPlayers[i].down)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (4 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x - (4 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (4 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x + (4 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (6 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), 0);
				SetCaret(gVirtualPlayers[i].x - (12 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (6 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), 2);
				SetCaret(gVirtualPlayers[i].x + (12 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
	}

	PlaySoundObject(34, SOUND_MODE_PLAY);
}

void VPShootBullet_MachineGun(int level)
{
	int bul_no;
	static int wait;

	switch (level)
	{
	case 1:
		bul_no = 10;
		break;

	case 2:
		bul_no = 11;
		break;

	case 3:
		bul_no = 12;
		break;
	}


	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].up)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else if (gVirtualPlayers[i].down)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 0);
				SetCaret(gVirtualPlayers[i].x - (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 2);
				SetCaret(gVirtualPlayers[i].x + (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
	}

	if (level == 3)
		PlaySoundObject(49, SOUND_MODE_PLAY);
	else
		PlaySoundObject(32, SOUND_MODE_PLAY);
}

void VPShootBullet_Missile(int level, BOOL bSuper)
{
	int bul_no;

	if (bSuper)
	{
		switch (level)
		{
			case 1:
				bul_no = 28;
				break;

			case 2:
				bul_no = 29;
				break;

			case 3:
				bul_no = 30;
				break;
		}
	}
	else
	{
		switch (level)
		{
			case 1:
				bul_no = 13;
				break;

			case 2:
				bul_no = 14;
				break;

			case 3:
				bul_no = 15;
				break;
		}
	}

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (level < 3)
		{
			if (gVirtualPlayers[i].up)
			{
				if (gVirtualPlayers[i].direct == 0)
				{
					SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
					SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
				}
				else
				{
					SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
					SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
				}
			}
			else if (gVirtualPlayers[i].down)
			{
				if (gVirtualPlayers[i].direct == 0)
				{
					SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
					SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
				}
				else
				{
					SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
					SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
				}
			}
			else
			{
				if (gVirtualPlayers[i].direct == 0)
				{
					SetBullet(bul_no, gVirtualPlayers[i].x - (6 * 0x200), gVirtualPlayers[i].y, 0);
					SetCaret(gVirtualPlayers[i].x - (12 * 0x200), gVirtualPlayers[i].y, CARET_SHOOT, DIR_LEFT);
				}
				else
				{
					SetBullet(bul_no, gVirtualPlayers[i].x + (6 * 0x200), gVirtualPlayers[i].y, 2);
					SetCaret(gVirtualPlayers[i].x + (12 * 0x200), gVirtualPlayers[i].y, CARET_SHOOT, DIR_LEFT);
				}
			}
		}
		else
		{
			if (gVirtualPlayers[i].up)
			{
				if (gVirtualPlayers[i].direct == 0)
				{
					SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
					SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
					SetBullet(bul_no, gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y, 1);
					SetBullet(bul_no, gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y, 1);
				}
				else
				{
					SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
					SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
					SetBullet(bul_no, gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y, 1);
					SetBullet(bul_no, gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y, 1);
				}
			}
			else if (gVirtualPlayers[i].down)
			{
				if (gVirtualPlayers[i].direct == 0)
				{
					SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
					SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
					SetBullet(bul_no, gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y, 3);
					SetBullet(bul_no, gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y, 3);
				}
				else
				{
					SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
					SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
					SetBullet(bul_no, gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y, 3);
					SetBullet(bul_no, gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y, 3);
				}
			}
			else
			{
				if (gVirtualPlayers[i].direct == 0)
				{
					SetBullet(bul_no, gVirtualPlayers[i].x - (6 * 0x200), gVirtualPlayers[i].y + (1 * 0x200), 0);
					SetCaret(gVirtualPlayers[i].x - (12 * 0x200), gVirtualPlayers[i].y + (1 * 0x200), CARET_SHOOT, DIR_LEFT);
					SetBullet(bul_no, gVirtualPlayers[i].x, gVirtualPlayers[i].y - (8 * 0x200), 0);
					SetBullet(bul_no, gVirtualPlayers[i].x + (4 * 0x200), gVirtualPlayers[i].y - (1 * 0x200), 0);
				}
				else
				{
					SetBullet(bul_no, gVirtualPlayers[i].x + (6 * 0x200), gVirtualPlayers[i].y + (1 * 0x200), 2);
					SetCaret(gVirtualPlayers[i].x + (12 * 0x200), gVirtualPlayers[i].y + (1 * 0x200), CARET_SHOOT, DIR_LEFT);
					SetBullet(bul_no, gVirtualPlayers[i].x, gVirtualPlayers[i].y - (8 * 0x200), 2);
					SetBullet(bul_no, gVirtualPlayers[i].x - (4 * 0x200), gVirtualPlayers[i].y - (1 * 0x200), 2);
				}
			}
		}
	}

	PlaySoundObject(32, SOUND_MODE_PLAY);
}

void VPShootBullet_Bubblin1(void)
{
	static int wait;

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].up)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(19, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (2 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (2 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(19, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (2 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (2 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else if (gVirtualPlayers[i].down)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(19, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(19, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (2 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(19, gVirtualPlayers[i].x - (6 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 0);
				SetCaret(gVirtualPlayers[i].x - (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(19, gVirtualPlayers[i].x + (6 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 2);
				SetCaret(gVirtualPlayers[i].x + (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
	}

	PlaySoundObject(48, SOUND_MODE_PLAY);
}

void VPShootBullet_Bubblin2(int level)
{
	static int wait;

	level += 18;

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].up)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(level, gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y - (16 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(level, gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y - (16 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else if (gVirtualPlayers[i].down)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(level, gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x - (3 * 0x200), gVirtualPlayers[i].y + (16 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(level, gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x + (3 * 0x200), gVirtualPlayers[i].y + (16 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(level, gVirtualPlayers[i].x - (6 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 0);
				SetCaret(gVirtualPlayers[i].x - (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(level, gVirtualPlayers[i].x + (6 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 2);
				SetCaret(gVirtualPlayers[i].x + (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}

		PlaySoundObject(48, SOUND_MODE_PLAY);
	}
}

void VPShootBullet_Sword(int level)
{
	int bul_no;

	switch (level)
	{
		case 1:
			bul_no = 25;
			break;

		case 2:
			bul_no = 26;
			break;

		case 3:
			bul_no = 27;
			break;
	}

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].up)
		{
			if (gVirtualPlayers[i].direct == 0)
				SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (4 * 0x200), 1);
			else
				SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (4 * 0x200), 1);
		}
		else if (gVirtualPlayers[i].down)
		{
			if (gVirtualPlayers[i].direct == 0)
				SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (6 * 0x200), 3);
			else
				SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (6 * 0x200), 3);
		}
		else
		{
			if (gVirtualPlayers[i].direct == 0)
				SetBullet(bul_no, gVirtualPlayers[i].x + (6 * 0x200), gVirtualPlayers[i].y - (3 * 0x200), 0);
			else
				SetBullet(bul_no, gVirtualPlayers[i].x - (6 * 0x200), gVirtualPlayers[i].y - (3 * 0x200), 2);
		}

		PlaySoundObject(34, SOUND_MODE_PLAY);
	}
}

void VPShootBullet_Nemesis(int level)
{
	int bul_no;

	switch (level)
	{
	case 1:
		bul_no = 34;
		break;

	case 2:
		bul_no = 35;
		break;

	case 3:
		bul_no = 36;
		break;
	}

	if (CountArmsBullet(12) > 1)
		return;

	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].up)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (12 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (12 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (12 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (12 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else if (gVirtualPlayers[i].down)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (12 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (12 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (12 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (12 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else
		{
		if (gVirtualPlayers[i].direct == 0)
		{
			SetBullet(bul_no, gVirtualPlayers[i].x - (22 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 0);
			SetCaret(gVirtualPlayers[i].x - (16 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
		}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (22 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 2);
				SetCaret(gVirtualPlayers[i].x + (16 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}

		switch (level)
		{
			case 1:
				PlaySoundObject(117, SOUND_MODE_PLAY);
				break;

			case 2:
				PlaySoundObject(49, SOUND_MODE_PLAY);
				break;

			case 3:
				PlaySoundObject(60, SOUND_MODE_PLAY);
				break;
		}
	}
}

void VPShootBullet_Spur(int level)
{
	int bul_no;
	
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		switch (level)
		{
		case 1:
			bul_no = 6;
			break;

		case 2:
			bul_no = 37;
			break;

		case 3:
			if (gVirtualPlayers[i].spurMax)
				bul_no = 39;
			else
				bul_no = 38;

			break;
		}
		if (gVirtualPlayers[i].up)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), 1);
				SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y - (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else if (gVirtualPlayers[i].down)
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x - (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), 3);
				SetCaret(gVirtualPlayers[i].x + (1 * 0x200), gVirtualPlayers[i].y + (8 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}
		else
		{
			if (gVirtualPlayers[i].direct == 0)
			{
				SetBullet(bul_no, gVirtualPlayers[i].x - (6 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 0);
				SetCaret(gVirtualPlayers[i].x - (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
			else
			{
				SetBullet(bul_no, gVirtualPlayers[i].x + (6 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), 2);
				SetCaret(gVirtualPlayers[i].x + (12 * 0x200), gVirtualPlayers[i].y + (3 * 0x200), CARET_SHOOT, DIR_LEFT);
			}
		}

		switch (bul_no)
		{
			case 6:
				PlaySoundObject(49, SOUND_MODE_PLAY);
				break;

			case 37:
				PlaySoundObject(62, SOUND_MODE_PLAY);
				break;

			case 38:
				PlaySoundObject(63, SOUND_MODE_PLAY);
				break;

			case 39:
				PlaySoundObject(64, SOUND_MODE_PLAY);
				break;
		}
	}
}

void SetMyShooting()
{
	if (my_soft_rensha != 0)
		--my_soft_rensha;

	if ((gKeyTrg & gKeyShot) && g_GameFlags & 2)
	{
		if (gArmsData[gSelectedArms].code != 0 && my_soft_rensha == 0)
		{
			my_soft_rensha = 4;
			my_shooting = true;
		}
	}
	else if (my_soft_rensha == 0)
	{
		my_shooting = false;
	}
}

void VirtualShootBullet()
{
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (gVirtualPlayers[i].stage == gStageNo)
		{
			if (gVirtualPlayers[i].shooting == true && gVirtualPlayers[i].arms != 0)
			{
				switch (gVirtualPlayers[i].arms)
				{
					case 1:
						VPShootBullet_Snake(gVirtualPlayers[i].arms_level);
						break;

					case 2:
						VPShootBullet_PolarStar(gVirtualPlayers[i].arms_level);
						break;

					case 3:
						VPShootBullet_FireBall(gVirtualPlayers[i].arms_level);
						break;

					case 4:
						VPShootBullet_MachineGun(gVirtualPlayers[i].arms_level);
						break;

					case 5:
						VPShootBullet_Missile(gVirtualPlayers[i].arms_level, FALSE);
						break;

					case 7:
						switch (gVirtualPlayers[i].arms_level)
						{
							case 1:
								VPShootBullet_Bubblin1();
								break;

							case 2:
								VPShootBullet_Bubblin2(2);
								break;

							case 3:
								VPShootBullet_Bubblin2(3);
								break;
						}
						break;

					case 9:
						switch (gVirtualPlayers[i].arms_level)
						{
							case 1:
								VPShootBullet_Sword(1);
								break;

							case 2:
								VPShootBullet_Sword(2);
								break;

							case 3:
								VPShootBullet_Sword(3);
								break;
						}
						break;

					case 10:
						VPShootBullet_Missile(gVirtualPlayers[i].arms_level, TRUE);
						break;

					case 12:
						VPShootBullet_Nemesis(gVirtualPlayers[i].arms_level);
						break;

					case 13:
						VPShootBullet_Spur(gVirtualPlayers[i].arms_level);
						break;
				}
			}
		}
	}
}