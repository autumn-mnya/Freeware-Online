#include "cave_story.h"
#include "main.h"
#include "NetworkDefine.h"
#include "Networking.h"

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
						ShootBullet_FireBall(gVirtualPlayers[i].arms_level);
						break;

					case 4:
						VPShootBullet_MachineGun(gVirtualPlayers[i].arms_level);
						break;

					case 5:
						break;

					case 6:
						break;

					case 7:
						break;

					case 8:
						break;

					case 9:
						break;

					case 10:
						break;

					case 11:
						break;

					case 12:
						break;

					case 13:
						break;
				}
			}
		}
	}
}