// Mod loader for Freeware Cave Story
// Public domain
#pragma once

#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>
#include <windows.h>

static int& window_magnification = *reinterpret_cast<int*>(0x48F914); // Window magnification
static ::RECT& grcGame = *reinterpret_cast<::RECT*>(0x48F91C);
static ::RECT& grcFull = *reinterpret_cast<::RECT*>(0x48F92C);

#define WINDOW_WIDTH grcGame.right
#define WINDOW_HEIGHT grcGame.bottom

// Max amounts of X

#define ARMS_MAX 8
#define ITEM_MAX 32
#define BOSS_MAX 20
#define BULLET_MAX 0x40
#define CARET_MAX 0x40
#define MAX_STRIP ((240 / 16) + 1)
#define FADE_WIDTH	(((320 - 1) / 16) + 1)
#define FADE_HEIGHT	(((320 - 1) / 16) + 1)
#define PXM_BUFFER_SIZE 0x4B000
#define NPC_MAX 0x200
#define STAGE_MAX 8
#define SE_MAX 160
#define TSC_BUFFER_SIZE 0x5000
#define VALUEVIEW_MAX 0x10

// Input key detection

static int& gKey = *reinterpret_cast<int*>(0x49E210);
static int& gKeyTrg = *reinterpret_cast<int*>(0x49E214);
static int& gKeyJump = *reinterpret_cast<int*>(0x493610);
static int& gKeyShot = *reinterpret_cast<int*>(0x493614);
static int& gKeyArms = *reinterpret_cast<int*>(0x493618);
static int& gKeyArmsRev = *reinterpret_cast<int*>(0x49361C);
static int& gKeyItem = *reinterpret_cast<int*>(0x493620);
static int& gKeyMap = *reinterpret_cast<int*>(0x493624);
static int& gKeyOk = *reinterpret_cast<int*>(0x493628);
static int& gKeyCancel = *reinterpret_cast<int*>(0x49362C);
static int& gKeyLeft = *reinterpret_cast<int*>(0x493630);
static int& gKeyUp = *reinterpret_cast<int*>(0x493634);
static int& gKeyRight = *reinterpret_cast<int*>(0x493638);
static int& gKeyDown = *reinterpret_cast<int*>(0x49363C);

#define KEY_ALT_LEFT 0x10000
#define KEY_ALT_DOWN 0x20000
#define KEY_ALT_RIGHT 0x40000
#define KEY_ALT_UP 0x180000
#define KEY_L 0x80000
#define KEY_PLUS 0x100000
#define KEY_ESCAPE 0x8000

// Variables
static HWND& ghWnd = *reinterpret_cast<HWND*>(0x49E458);
static const char*& lpWindowName = *reinterpret_cast<const char**>(0x493640);
static HINSTANCE ghInstance = *reinterpret_cast<HINSTANCE*>(0x49E44C);

#define hObject (*(HANDLE*)0x49E478)
#define hMutex (*(HANDLE*)0x49E47C)

#define background_tile_width (*(int*)0x499C78)
#define background_tile_height (*(int*)0x499C7C)

#define dword_499C8C (*(int*)0x499C8C)

#define window_padding_h (*(int*)0x49CDA8)
#define window_padding_w (*(int*)0x49CDAC)

#define window_surface_width (*(int*)0x49D374)
#define window_surface_height (*(int*)0x49D378)
#define directdraw (*(IDirectDraw7**)0x49D37C)
#define screen_primary_surface (*(IDirectDrawSurface7** const)0x49D380)
#define screen_surface (*(IDirectDrawSurface7** const)0x49D384)
#define surfaces (*(IDirectDrawSurface7*(*)[40])0x49D388)
#define fade_counter (*(int*)0x49DB38)
#define camera_x_pos (*(signed int*)0x49E1C8)
#define camera_y_pos (*(signed int*)0x49E1CC)
#define camera_x_destination (*(signed int*)0x49E1D0)
#define camera_y_destination (*(signed int*)0x49E1D4)
#define gamemode_flags (*(unsigned int*)0x49E1E8)
#define tsc_buffer (*(char**)0x4A5AD8)
#define tsc_offset (*(unsigned int*)0x4A5AE0)
#define pxm_buffer (*(unsigned char**)0x49E480)
#define pxa_buffer ((unsigned char*)0x49E484)
#define gbUseJoystick (*(int*)0x49E45C)
#define MapWidth (*(unsigned short*)0x49E586)
#define MapHeight (*(unsigned short*)0x49E588)
#define gMC_cond (*(char*)0x49E638)
#define quote_facing_right (*(BOOL*)0x49E640)
#define gMC_x (*(int*)0x49E654) // gMC.x
#define gMC_y (*(int*)0x49E658) // gMC.y
#define gMC_ani_no (*(int*)0x49E678) // gMC.ani_no
#define quote_sprite_half_width (*(int*)0x49E68C)
#define quote_sprite_half_height (*(int*)0x49E690)
#define gSelectedArms (*(int*)0x499C68)
#define gSelectedItem (*(int*)0x499C6C)
#define music_fade_flag (*(int*)0x4A4E10)
#define gStageNo (*(int*)0x4A57F0) // gStageNo
#define bContinue (*(BOOL*)0x49E1E4)
static BOOL& bFPS = *reinterpret_cast<BOOL*>(0x49E464);
static BOOL& bActive = *reinterpret_cast<BOOL*>(0x49E468);
static BOOL& bFullscreen = *reinterpret_cast<BOOL*>(0x49E460);
#define BoosterFuel (*(int*)0x49E6E8)

#define gConfigHeader (*(char*)0x48F908) // config header
#define gConfigFileName (*(char**)0x48F90C) // config filename

// <MIM Compatibility
#define CSM_MIM_unobstructive (*(unsigned int*)0x49E184)
#define CSM_MIM_tsc_plus  (*(int*)0x49E09C)

// Hookspaces & Hookjumps

#define TextScriptBuffer (*(char**)0x4A5AD8) // I renamed this one but you get the idea
#define CS_tsc_offset (*(unsigned int*)0x4A5AE0) // gTS.p_read

#define CSH_tsc_start (void*) 0x4225D5, 12
#define CSH_tsc_end (void*) 0x425244, 12
#define CSJ_tsc_done 0x4225CB

// String array

struct OTHER_RECT	// The original name for this struct is unknown
{
	int front;
	int top;
	int back;
	int bottom;
};

// Enums

enum
{
	enum_ESCRETURN_exit,
	enum_ESCRETURN_continue,
	enum_ESCRETURN_restart
};

enum
{
	CARET_NULL = 0,
	CARET_BUBBLE = 1,
	CARET_PROJECTILE_DISSIPATION = 2,
	CARET_SHOOT = 3,
	CARET_SNAKE_AFTERIMAGE = 4,
	CARET_ZZZ = 5,
	CARET_SNAKE_AFTERIMAGE_DUPLICATE = 6,
	CARET_EXHAUST = 7,
	CARET_DROWNED_QUOTE = 8,
	CARET_QUESTION_MARK = 9,
	CARET_LEVEL_UP = 10,
	CARET_HURT_PARTICLES = 11,
	CARET_EXPLOSION = 12,
	CARET_TINY_PARTICLES = 13,
	CARET_UNKNOWN = 14,
	CARET_PROJECTILE_DISSIPATION_TINY = 15,
	CARET_EMPTY = 16,
	CARET_PUSH_JUMP_KEY = 17
};

enum
{
	EQUIP_BOOSTER_0_8 = 1,
	EQUIP_MAP = 2,
	EQUIP_ARMS_BARRIER = 4,
	EQUIP_TURBOCHARGE = 8,
	EQUIP_AIR_TANK = 0x10,
	EQUIP_BOOSTER_2_0 = 0x20,
	EQUIP_MIMIGA_MASK = 0x40,
	EQUIP_WHIMSICAL_STAR = 0x80,
	EQUIP_NIKUMARU_COUNTER = 0x100
};

enum SoundEffectNames
{
	SND_YES_NO_CHANGE_CHOICE = 1,
	SND_MESSAGE_TYPING = 2,
	SND_QUOTE_BUMP_HEAD = 3,
	SND_SWITCH_WEAPON = 4,
	SND_YES_NO_PROMPT = 5,
	// To be continued
	SND_SILLY_EXPLOSION = 25,
	SND_LARGE_OBJECT_HIT_GROUND = 26,
	// To be continued
	SND_ENEMY_SHOOT_PROJECTILE = 39,
	// To be continued
	SND_BEHEMOTH_LARGE_HURT = 52,
	// To be continued
	SND_EXPLOSION = 72
	// To be continued
};

enum Collisions
{
	COLL_LEFT_WALL = 1,     // Touching a left wall
	COLL_CEILING = 2,       // Touching a ceiling
	COLL_RIGHT_WALL = 4,    // Touching a right wall
	COLL_GROUND = 8         // Touching the ground
	// To be continued
};

enum Direction
{
	DIR_LEFT = 0,
	DIR_UP = 1,
	DIR_RIGHT = 2,
	DIR_DOWN = 3,
	DIR_AUTO = 4,
	DIR_OTHER = 5
};

enum FlashMode
{
	FLASH_MODE_EXPLOSION = 1,
	FLASH_MODE_FLASH = 2
};

typedef enum SurfaceID
{
	SURFACE_ID_TITLE = 0,
	SURFACE_ID_PIXEL = 1,
	SURFACE_ID_LEVEL_TILESET = 2,
	SURFACE_ID_USERNAME = 3,
	SURFACE_ID_FADE = 6,
	SURFACE_ID_ITEM_IMAGE = 8,
	SURFACE_ID_MAP = 9,
	SURFACE_ID_SCREEN_GRAB = 10,
	SURFACE_ID_ARMS = 11,
	SURFACE_ID_ARMS_IMAGE = 12,
	SURFACE_ID_ROOM_NAME = 13,
	SURFACE_ID_STAGE_ITEM = 14,
	SURFACE_ID_LOADING = 15,
	SURFACE_ID_MY_CHAR = 16,
	SURFACE_ID_BULLET = 17,
	SURFACE_ID_CARET = 19,
	SURFACE_ID_NPC_SYM = 20,
	SURFACE_ID_LEVEL_SPRITESET_1 = 21,
	SURFACE_ID_LEVEL_SPRITESET_2 = 22,
	SURFACE_ID_NPC_REGU = 23,
	SURFACE_ID_TEXT_BOX = 26,
	SURFACE_ID_FACE = 27,
	SURFACE_ID_LEVEL_BACKGROUND = 28,
	SURFACE_ID_VALUE_VIEW = 29,
	SURFACE_ID_TEXT_LINE1 = 30,
	SURFACE_ID_TEXT_LINE2 = 31,
	SURFACE_ID_TEXT_LINE3 = 32,
	SURFACE_ID_TEXT_LINE4 = 33,
	SURFACE_ID_TEXT_LINE5 = 34,
	SURFACE_ID_CREDIT_CAST = 35,
	SURFACE_ID_CREDITS_IMAGE = 36,
	SURFACE_ID_CASTS = 37,
	SURFACE_ID_MAX = 40
} SurfaceID;

// Structs

// inventory
typedef struct ARMS
{
	int code;

	int level;

	int exp;

	int max_num;

	int num;
} ARMS;

typedef struct ITEM
{
	int code;
} ITEM;

// background

typedef struct BACK
{
	BOOL flag;	// Unused - purpose unknown
	int partsW;
	int partsH;
	int numX;
	int numY;
	int type;
	int fx;
} BACK;

// Boss

typedef struct BOSSLIFE	// Not the original struct name
{
	BOOL flag;
	int* pLife;
	int max;
	int br;
	int count;
} BOSSLIFE;

// Config

typedef struct ConfigData
{
	char proof[0x20];
	char font_name[0x40];
	long move_button_mode;
	long attack_button_mode;
	long ok_button_mode;
	long display_mode;
	BOOL bJoystick;
	long joystick_button[8];
} ConfigData;

// Bullet
typedef struct BULLET
{
	int flag;
	int code_bullet;
	int bbits;
	int cond;
	int x;
	int y;
	int xm;
	int ym;
	int tgt_x;
	int tgt_y;
	int act_no;
	int act_wait;
	int ani_wait;
	int ani_no;
	unsigned char direct;
	RECT rect;
	int count1;
	int count2;
	int life_count;
	int damage;
	int life;
	int enemyXL;
	int enemyYL;
	int blockXL;
	int blockYL;
	OTHER_RECT view;
} BULLET;

// Bullet Table
typedef struct BULLET_TABLE
{
	signed char damage;
	signed char life;
	int life_count;
	int bbits;
	int enemyXL;
	int enemyYL;
	int blockXL;
	int blockYL;
	OTHER_RECT view;
} BULLET_TABLE;

// Caret
struct CARET
{
	int cond;
	int code;
	int direct;
	int x;
	int y;
	int xm;
	int ym;
	int act_no;
	int act_wait;
	int ani_no;
	int ani_wait;
	int view_left;
	int view_top;
	RECT rect;
};

struct CARET_TABLE
{
	int view_left;
	int view_top;
};

// Ending

enum CREDIT_MODE
{
	CREDIT_MODE_STOP,
	CREDIT_MODE_SCROLL_READ,
	CREDIT_MODE_SCROLL_WAIT
};

enum ILLUSTRATION_ACTION
{
	ILLUSTRATION_ACTION_IDLE,
	ILLUSTRATION_ACTION_SLIDE_IN,
	ILLUSTRATION_ACTION_SLIDE_OUT
};

struct CREDIT
{
	long size;
	char* pData;
	int offset;
	int wait;
	CREDIT_MODE mode;
	int start_x;
};

struct STRIP
{
	int flag;
	int x;
	int y;
	int cast;
	char str[0x40];
};

struct ILLUSTRATION
{
	ILLUSTRATION_ACTION act_no;
	int x;
};

struct ISLAND_SPRITE
{
	int x;
	int y;
};

// Fade

struct FADE
{
	int mode;
	BOOL bMask;
	int count;
	signed char ani_no[FADE_HEIGHT][FADE_WIDTH];
	signed char flag[FADE_HEIGHT][FADE_WIDTH];	// Not a BOOLEAN (those are unsigned)
	signed char dir;
};

// Flash

struct FLASH
{
	int mode;
	int act_no;
	BOOL flag;
	int cnt;
	int width;
	int x;
	int y;
	RECT rect1;
	RECT rect2;
};

// Frame

typedef struct FRAME
{
	int x;
	int y;
	int* tgt_x;
	int* tgt_y;
	int wait;
	int quake;
	int quake2;
} FRAME;

// Input

struct DIRECTINPUTSTATUS
{
	BOOL bLeft;
	BOOL bRight;
	BOOL bUp;
	BOOL bDown;
	BOOL bButton[32]; // 32 is the number of buttons in DirectInput's `DIJOYSTATE` struct
};

// Mapping

typedef struct MAP_DATA
{
	unsigned char* data;
	unsigned char atrb[0x101]; // this should be bigger than 0x100
	short width;
	short length;
} MAP_DATA;

// Map Name

typedef struct MAP_NAME
{
	BOOL flag;
	int wait;
	char name[0x20];
} MAP_NAME;

// MyChar

typedef struct MYCHAR
{
	unsigned char cond;
	unsigned int flag;
	int direct;
	BOOL up;
	BOOL down;
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
	OTHER_RECT hit;
	OTHER_RECT view;
	RECT rect;
	RECT rect_arms;
	int level;
	int exp_wait;
	int exp_count;
	unsigned char shock;
	unsigned char no_life;
	unsigned char rensha;
	unsigned char bubble;
	short life;
	short star;
	short max_life;
	short a;
	int lifeBr;
	int lifeBr_count;
	int air;
	int air_get;
	signed char sprash;
	signed char ques;
	signed char boost_sw;
	int boost_cnt;
} MYCHAR;

// MycParam

typedef struct ARMS_LEVEL
{
	int exp[3];
} ARMS_LEVEL;

typedef struct REC
{
	long counter[4];
	unsigned char random[4];
} REC;

// Npc Entity flags
enum NPCFlags
{
	NPC_SOLID_SOFT = 1 << 0,                // Pushes Quote out
	NPC_IGNORE_TILE_44 = 1 << 1,            // Ignores tile 44, which normally blocks NPCs
	NPC_INVULNERABLE = 1 << 2,              // Can't be hurt
	NPC_IGNORE_SOLIDITY = 1 << 3,           // Doesn't collide with anything
	NPC_BOUNCY = 1 << 4,                    // Quote bounces on top of NPC
	NPC_SHOOTABLE = 1 << 5,                 // Can be shot
	NPC_SOLID_HARD = 1 << 6,                // Essentially acts as level tiles
	NPC_REAR_AND_TOP_DONT_HURT = 1 << 7,    // Rear and top don't hurt when touched
	NPC_EVENT_WHEN_TOUCHED = 1 << 8,        // Run event when touched
	NPC_EVENT_WHEN_KILLED = 1 << 9,         // Run event when killed
	NPC_APPEAR_WHEN_FLAG_SET = 1 << 11,     // Only appear when flag is set
	NPC_SPAWN_IN_OTHER_DIRECTION = 1 << 12, // Spawn facing to the right (or however the NPC interprets the direction)
	NPC_INTERACTABLE = 1 << 13,             // Run event when interacted with
	NPC_HIDE_WHEN_FLAG_SET = 1 << 14,       // Hide when flag is set
	NPC_SHOW_DAMAGE = 1 << 15               // Show the number of damage taken when harmed
};

// NpChar
typedef struct NPCHAR
{
	unsigned char cond;
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
	SurfaceID surf;
	int hit_voice;
	int destroy_voice;
	int life;
	int exp;
	int size;
	int direct;
	unsigned short bits;
	RECT rect;
	int ani_wait;
	int ani_no;
	int count1;
	int count2;
	int act_no;
	int act_wait;
	OTHER_RECT hit;
	OTHER_RECT view;
	unsigned char shock;
	int damage_view;
	int damage;
	struct NPCHAR* pNpc;
} NPCHAR;

// NpChar Event

struct EVENT
{
	short x;
	short y;
	short code_flag;
	short code_event;
	short code_char;
	unsigned short bits;
};

// Npc Table

struct NPC_TBL_RECT
{
	unsigned char front;
	unsigned char top;
	unsigned char back;
	unsigned char bottom;
};

struct NPC_TABLE
{
	unsigned short bits;
	unsigned short life;
	unsigned char surf;
	unsigned char hit_voice;
	unsigned char destroy_voice;
	unsigned char size;
	long exp;
	long damage;
	NPC_TBL_RECT hit;
	NPC_TBL_RECT view;
};

// PixTone

typedef struct PIXTONEPARAMETER2
{
	int model;
	double num;
	int top;
	int offset;
} PIXTONEPARAMETER2;

typedef struct PIXTONEPARAMETER
{
	int use;
	int size;
	PIXTONEPARAMETER2 oMain;
	PIXTONEPARAMETER2 oPitch;
	PIXTONEPARAMETER2 oVolume;
	int initial;
	int pointAx;
	int pointAy;
	int pointBx;
	int pointBy;
	int pointCx;
	int pointCy;
} PIXTONEPARAMETER;

// Permit Stage

typedef struct PERMIT_STAGE
{
	int index;
	int event;
} PERMIT_STAGE;

// Stage Table

typedef struct STAGE_TABLE
{
	char parts[0x20];
	char map[0x20];
	int bkType;
	char back[0x20];
	char npc[0x20];
	char boss[0x20];
	signed char boss_no;
	char name[0x20];
} STAGE_TABLE;

// MusicID
typedef enum MusicID
{
	MUS_SILENCE = 0x0,
	MUS_MISCHIEVOUS_ROBOT = 0x1,
	MUS_SAFETY = 0x2,
	MUS_GAME_OVER = 0x3,
	MUS_GRAVITY = 0x4,
	MUS_ON_TO_GRASSTOWN = 0x5,
	MUS_MELTDOWN2 = 0x6,
	MUS_EYES_OF_FLAME = 0x7,
	MUS_GESTATION = 0x8,
	MUS_MIMIGA_TOWN = 0x9,
	MUS_GOT_ITEM = 0xA,
	MUS_BALROGS_THEME = 0xB,
	MUS_CEMETERY = 0xC,
	MUS_PLANT = 0xD,
	MUS_PULSE = 0xE,
	MUS_VICTORY = 0xF,
	MUS_GET_HEART_TANK = 0x10,
	MUS_TYRANT = 0x11,
	MUS_RUN = 0x12,
	MUS_JENKA1 = 0x13,
	MUS_LABYRINTH_FIGHT = 0x14,
	MUS_ACCESS = 0x15,
	MUS_OPPRESSION = 0x16,
	MUS_GEOTHERMAL = 0x17,
	MUS_CAVE_STORY = 0x18,
	MUS_MOONSONG = 0x19,
	MUS_HEROS_END = 0x1A,
	MUS_SCORCHING_BACK = 0x1B,
	MUS_QUIET = 0x1C,
	MUS_LAST_CAVE = 0x1D,
	MUS_BALCONY = 0x1E,
	MUS_CHARGE = 0x1F,
	MUS_LAST_BATTLE = 0x20,
	MUS_THE_WAY_BACK_HOME = 0x21,
	MUS_ZOMBIE = 0x22,
	MUS_BREAK_DOWN = 0x23,
	MUS_RUNNING_HELL = 0x24,
	MUS_JENKA2 = 0x25,
	MUS_LIVING_WATERWAY = 0x26,
	MUS_SEAL_CHAMBER = 0x27,
	MUS_TOROKOS_THEME = 0x28,
	MUS_WHITE = 0x29
} MusicID;

// Profile

typedef struct PROFILEDATA
{
	char code[8];
	int stage;
	int music;
	int x;
	int y;
	int direct;
	short max_life;
	short star;
	short life;
	short a;
	int select_arms;
	int select_item;
	int equip;
	int unit;
	int counter;
	ARMS arms[8];
	ITEM items[32];
	PERMIT_STAGE permitstage[8];
	signed char permit_mapping[0x80];
	char FLAG[4];
	unsigned char flags[1000];
} PROFILEDATA;

// Organya

struct ORGANYATRACK
{
	unsigned short freq;
	unsigned char wave_no;
	unsigned char pipi;
	unsigned short note_num;
};

struct ORGANYADATA
{
	unsigned short wait;
	unsigned char line;
	unsigned char dot;
	long repeat_x;
	long end_x;
	ORGANYATRACK tdata[16];
};

struct NOTELIST
{
	NOTELIST* from;
	NOTELIST* to;
	long x;
	unsigned char length;
	unsigned char y;
	unsigned char volume;
	unsigned char pan;
};

struct TRACKDATA
{
	unsigned short freq;
	unsigned char wave_no;
	signed char pipi;
	NOTELIST* note_p;
	NOTELIST* note_list;
};

struct MUSICINFO
{
	unsigned short wait;
	unsigned char line;
	unsigned char dot;
	unsigned short alloc_note;
	long repeat_x;
	long end_x;
	TRACKDATA tdata[16];
};

struct ORGDATA
{
	MUSICINFO info;
	char track;
	char mute[16];
	unsigned char def_pan;
	unsigned char def_volume;

	ORGDATA();
	void InitOrgData();
	void GetMusicInfo(MUSICINFO* mi);
	BOOL SetMusicInfo(MUSICINFO* mi, unsigned long flag);
	BOOL NoteAlloc(unsigned short note_num);
	void ReleaseNote(void);
	void PlayData(void);
	void SetPlayPointer(long x);
	BOOL InitMusicData(const char* path);
};

struct OCTWAVE
{
	short wave_size;
	short oct_par;
	short oct_size;
};

// Sound

enum SoundMode
{
	SOUND_MODE_PLAY_LOOP = -1,
	SOUND_MODE_STOP = 0,
	SOUND_MODE_PLAY = 1
};

// TextScript

typedef struct TEXT_SCRIPT
{
	// Path (reload when exit teleporter menu/inventory)
	char path[MAX_PATH];

	// Script buffer
	long size;
	char* data;

	// Mode (ex. NOD, WAI)
	signed char mode;

	// Flags
	signed char flags;

	// Current positions (read position in buffer, x position in line)
	int p_read;
	int p_write;

	// Current line to write to
	int line;

	// Line y positions
	int ypos_line[4];

	// Event stuff
	int wait;
	int wait_next;
	int next_event;

	// Yes/no selected
	signed char select;

	// Current face
	int face;
	int face_x;

	// Current item
	int item;
	int item_y;

	// Text rect
	RECT rcText;

	// ..?
	int offsetY;

	// NOD cursor blink
	unsigned char wait_beam;
} TEXT_SCRIPT;

// ValueView

typedef struct VALUEVIEW
{
	BOOL flag;
	int* px;
	int* py;
	int offset_y;
	int value;
	int count;
	RECT rect;
} VALUEVIEW;

// Pointers to structs
typedef void (*BOSSFUNCTION)(void);
typedef void (*CARETFUNCTION)(CARET*);
typedef void (*NPCFUNCTION)(NPCHAR*);

static auto& gArmsData = *reinterpret_cast<ARMS(*)[8]>(0x499BC8);
static auto& gItemData = *reinterpret_cast<ITEM(*)[32]>(0x499B40);
static ARMS_LEVEL* gArmsLevelTable = (ARMS_LEVEL*)0x493660;

static BACK& gBack = *reinterpret_cast<BACK*>(0x499C74);
static int& gWaterY = *reinterpret_cast<int*>(0x499C90); // Global water level

static auto& gBul = *reinterpret_cast<BULLET(*)[64]>(0x499C98);
static auto& gBulTbl = *reinterpret_cast<BULLET_TABLE(*)[46]>(0x48F048);
static int& spur_charge = *reinterpret_cast<int*>(0x4A5550);
static int& empty_caret_timer = *reinterpret_cast<int*>(0x4A554C);

static auto& gBoss = *reinterpret_cast<NPCHAR(*)[20]>(0x4BBA58);
static auto& gpBossFuncTbl = *reinterpret_cast<BOSSFUNCTION(*)[10]>(0x498AEC);
static BOSSLIFE& gBL = *reinterpret_cast<BOSSLIFE*>(0x4BBA44);

static auto& gCrt = *reinterpret_cast<CARET(*)[64]>(0x49BCA8); // idk if i did this right actually
static auto& gCaretTable = *reinterpret_cast<CARET_TABLE(*)[18]>(0x48F830);
static auto& gpCaretFuncTbl = *reinterpret_cast<CARETFUNCTION(*)[18]>(0x48F8C0);
static auto& star = *reinterpret_cast<CARET(*)[3]>(0x4A5800);

static const char*& gProof = *reinterpret_cast<const char**>(0x48F908);
static const char*& gConfigName = *reinterpret_cast<const char**>(0x48F90C);

static FADE& gFade = *reinterpret_cast<FADE*>(0x49DB30);
static unsigned long& mask_color = *reinterpret_cast<unsigned long*>(0x49DB28);

static auto& gFlagNPC = *reinterpret_cast<unsigned char(*)[1000]>(0x49DDA0);
static auto& gSkipFlag = *reinterpret_cast<unsigned char(*)[8]>(0x49DD98);

static FLASH& flash = *reinterpret_cast<FLASH*>(0x49E188);
static unsigned long& gFlashColor = *reinterpret_cast<unsigned long*>(0x49E1C4);

static FRAME& gFrame = *reinterpret_cast<FRAME*>(0x49E1C8);

static MYCHAR& gMC = *reinterpret_cast<MYCHAR*>(0x49E638);
static int& time_count = *reinterpret_cast<int*>(0x49E6F4); // Nikumaru/290 counter value

static MAP_DATA& gMap = *reinterpret_cast<MAP_DATA*>(0x49E480);
static const char*& code_pxma = *reinterpret_cast<const char**>(0x49364C);
static MAP_NAME& gMapName = *reinterpret_cast<MAP_NAME*>(0x49E590);
static RECT& mapname_rect = *reinterpret_cast<RECT*>(0x493650); // Not original name

static auto& gNPC = *reinterpret_cast<NPCHAR(*)[0x200]>(0x4A6220);
static int& gCurlyShoot_wait = *reinterpret_cast<int*>(0x4BBA2C);
static int& gCurlyShoot_x = *reinterpret_cast<int*>(0x4BBA20);
static int& gCurlyShoot_y = *reinterpret_cast<int*>(0x4BBA24);
static int& gSuperXpos = *reinterpret_cast<int*>(0x4BBA30);
static int& gSuperYpos = *reinterpret_cast<int*>(0x4BBA28);
static const char*& gPassPixEve = *reinterpret_cast<const char**>(0x498540);

static NPC_TABLE** gNpcTable = (NPC_TABLE**)0x4BBA34;
static NPCFUNCTION* gpNpcFuncTbl = (NPCFUNCTION*)0x498548;

static auto& gPermitStage = *reinterpret_cast<PERMIT_STAGE(*)[8]>(0x4A5500);

static STAGE_TABLE* oTMT = (STAGE_TABLE*)0x4937B0; // Default stage table in the exe.
static STAGE_TABLE* gTMT = (STAGE_TABLE*)(*(unsigned*)0x420C2F); // This is a pointer to where it gets used, instead of the actual table, so that it has compatibility with mods.

static auto& lpORGANBUFFER = *reinterpret_cast<LPDIRECTSOUNDBUFFER(*)[8][8][2]>(0x4A4B48);
static auto& oct_wave = *reinterpret_cast<OCTWAVE(*)[8]>(0x493708);
static WAVEFORMATEX& format_tbl2 = *reinterpret_cast<WAVEFORMATEX*>(0x493738);
static auto& freq_tbl = *reinterpret_cast<short(*)[12]>(0x49374C);
static auto& pan_tbl = *reinterpret_cast<short(*)[13]>(0x493764);
static auto& g_mute = *reinterpret_cast<BOOL(*)[16]>(0x4A4D48);
static auto& old_key = *reinterpret_cast<unsigned char(*)[16]>(0x493780);
static auto& key_on = *reinterpret_cast<unsigned char(*)[16]>(0x4A4D88);
static auto& key_twin = *reinterpret_cast<unsigned char(*)[16]>(0x4A4D98);
static auto& wave_data = *reinterpret_cast<signed char(*)[100][0x100]>(0x49E700);
static ORGDATA& org_data = *reinterpret_cast<ORGDATA*>(0x4A4E18);
static long& PlayPos = *reinterpret_cast<LONG*>(0x4A4B00);
static auto& np = *reinterpret_cast<NOTELIST * (*)[16]>(0x4A4B08);
static auto& now_leng = *reinterpret_cast<long(*)[8]>(0x4A4DB0);
static int& Volume = *reinterpret_cast<int*>(0x4937A4);
static auto& TrackVol = *reinterpret_cast<int(*)[16]>(0x4A4DD0);
static BOOL& bFadeout = *reinterpret_cast<BOOL*>(0x4A4E10);

static LPDIRECTSOUND& lpDS = *reinterpret_cast<LPDIRECTSOUND*>(0x4A57E8);
static LPDIRECTSOUNDBUFFER& lpPRIMARYBUFFER = *reinterpret_cast<LPDIRECTSOUNDBUFFER*>(0x4A57EC);
static auto& lpSECONDARYBUFFER = *reinterpret_cast<LPDIRECTSOUNDBUFFER(*)[160]>(0x4A5568);

static int& gMusicNo = *reinterpret_cast<int*>(0x4A57F4);
static unsigned int& gOldPos = *reinterpret_cast<unsigned int*>(0x4A57F8);
static int& gOldNo = *reinterpret_cast<int*>(0x4A57FC);
static auto& gMusicTable = *reinterpret_cast<const char* (*)[42]>(0x4981E8);

static auto& gPtpTable = *reinterpret_cast<PIXTONEPARAMETER(*)[139]>(0x48F940);
static auto& gWaveModelTable = *reinterpret_cast<signed char(*)[6][0x100]>(0x4A4F00);

static const char*& gDefaultName = *reinterpret_cast<const char**>(0x4937A8);
static const char*& gProfileCode = *reinterpret_cast<const char**>(0x4937AC);

static int& noise_no = *reinterpret_cast<int*>(0x49E6EC);
static unsigned int& noise_freq = *reinterpret_cast<unsigned int*>(0x49E6F0);

static TEXT_SCRIPT& gTS = *reinterpret_cast<TEXT_SCRIPT*>(0x4A59D0);
static auto& text = *reinterpret_cast<char(*)[4][0x40]>(0x4A58D0);
static RECT& gRect_line = *reinterpret_cast<RECT*>(0x498290);
static auto& gNumberTextScript = *reinterpret_cast<int(*)[4]>(0x4A5B34);

static auto& gVV = *reinterpret_cast<VALUEVIEW(*)[16]>(0x4A5F98);
static int& gVVIndex = *reinterpret_cast<int*>(0x4A5F90);

static const char*& gVersionString = *reinterpret_cast<const char**>(0x48F910);

static auto& gMapping = *reinterpret_cast<signed char(*)[0x80]>(0x49E5B8);

static auto& gSin = *reinterpret_cast<int(*)[0x100]>(0x4A5B48);
static auto& gTan = *reinterpret_cast<short(*)[0x21]>(0x4A5F48);

static int& g_GameFlags = *reinterpret_cast<int*>(0x49E1E8);
static int& gCounter = *reinterpret_cast<int*>(0x49E1EC);

///////////////
// Functions //
///////////////


//ArmsItem functions
const auto ClearArmsData = reinterpret_cast<void(*)(void)>(0x401000);
const auto ClearItemData = reinterpret_cast<void(*)(void)>(0x401030);
const auto AddArmsData = reinterpret_cast<BOOL(*)(int, int)>(0x401050);
const auto SubArmsData = reinterpret_cast<BOOL(*)(int)>(0x401160);
const auto TradeArms = reinterpret_cast<BOOL(*)(int, int, int)>(0x401220);
const auto AddItemData = reinterpret_cast<BOOL(*)(int)>(0x4012D0);
const auto SubItemData = reinterpret_cast<BOOL(*)(int)>(0x401330);
const auto MoveCampCursor = reinterpret_cast<void(*)(void)>(0x4013C0);
const auto PutCampObject = reinterpret_cast<void(*)(void)>(0x4016F0);
const auto CampLoop = reinterpret_cast<int(*)(void)>(0x401D10);
const auto CheckItem = reinterpret_cast<BOOL(*)(int)>(0x401F20);
const auto CheckArms = reinterpret_cast<BOOL(*)(int)>(0x401F60);
const auto UseArmsEnergy = reinterpret_cast<BOOL(*)(int)>(0x401FA0);
const auto ChargeArmsEnergy = reinterpret_cast<BOOL(*)(int)>(0x402020);
const auto FullArmsEnergy = reinterpret_cast<void(*)(void)>(0x402090);
const auto RotationArms = reinterpret_cast<int(*)(void)>(0x4020E0);
const auto RotationArmsRev = reinterpret_cast<int(*)(void)>(0x402190);
const auto ChangeToFirstArms = reinterpret_cast<void(*)(void)>(0x402240);
// Background functions
const auto InitBack = reinterpret_cast<int(*)(const char*, int)>(0x402270);
const auto ActBack = reinterpret_cast<void(*)(void)>(0x402370);
const auto PutBack = reinterpret_cast<void(*)(int, int)>(0x4023D0);
const auto PutFront = reinterpret_cast<void(*)(int, int)>(0x402830);
// Bullet Collision functions
const auto JudgeHitBulletBlock = reinterpret_cast<int(*)(int, int, BULLET*)>(0x4029B0);
const auto JudgeHitBulletBlock2 = reinterpret_cast<int(*)(int, int, unsigned char*, BULLET*)>(0x402B30);
const auto JudgeHitBulletTriangleA = reinterpret_cast<int(*)(int, int, BULLET*)>(0x402FC0);
const auto JudgeHitBulletTriangleB = reinterpret_cast<int(*)(int, int, BULLET*)>(0x4030B0);
const auto JudgeHitBulletTriangleC = reinterpret_cast<int(*)(int, int, BULLET*)>(0x4031A0);
const auto JudgeHitBulletTriangleD = reinterpret_cast<int(*)(int, int, BULLET*)>(0x403290);
const auto JudgeHitBulletTriangleE = reinterpret_cast<int(*)(int, int, BULLET*)>(0x403380);
const auto JudgeHitBulletTriangleF = reinterpret_cast<int(*)(int, int, BULLET*)>(0x403470);
const auto JudgeHitBulletTriangleG = reinterpret_cast<int(*)(int, int, BULLET*)>(0x403560);
const auto JudgeHitBulletTriangleH = reinterpret_cast<int(*)(int, int, BULLET*)>(0x403650);
const auto HitBulletMap = reinterpret_cast<void(*)(void)>(0x403740);
// Bullet functions
const auto InitBullet = reinterpret_cast<void(*)(void)>(0x403C00);
const auto CountArmsBullet = reinterpret_cast<int(*)(int)>(0x403C40);
const auto CountBulletNum = reinterpret_cast<int(*)(int)>(0x403CB0);
const auto DeleteBullet = reinterpret_cast<void(*)(int)>(0x403D10);
const auto ClearBullet = reinterpret_cast<void(*)(void)>(0x403D80);
const auto PutBullet = reinterpret_cast<void(*)(int, int)>(0x403DC0);
const auto SetBullet = reinterpret_cast<void(*)(int, int, int, int)>(0x403F80);
// Bullet act functions
const auto ActBullet_Frontia1 = reinterpret_cast<void(*)(BULLET*)>(0x404160);
const auto ActBullet_Frontia2 = reinterpret_cast<void(*)(BULLET*, int)>(0x4043F0);
const auto ActBullet_PoleStar = reinterpret_cast<void(*)(BULLET*, int)>(0x4047B0);
const auto ActBullet_FireBall = reinterpret_cast<void(*)(BULLET*, int)>(0x404B30);
const auto ActBullet_MachineGun = reinterpret_cast<void(*)(BULLET*, int)>(0x405120);
const auto ActBullet_Missile = reinterpret_cast<void(*)(BULLET*, int)>(0x4055A0);
const auto ActBullet_Bom = reinterpret_cast<void(*)(BULLET*, int)>(0x405D80);
const auto ActBullet_Bubblin1 = reinterpret_cast<void(*)(BULLET*)>(0x405F30);
const auto ActBullet_Bubblin2 = reinterpret_cast<void(*)(BULLET*)>(0x406190);
const auto ActBullet_Bubblin3 = reinterpret_cast<void(*)(BULLET*)>(0x4064D0);
const auto ActBullet_Spine = reinterpret_cast<void(*)(BULLET*)>(0x4068B0);
const auto ActBullet_Sword1 = reinterpret_cast<void(*)(BULLET*)>(0x406BB0);
const auto ActBullet_Sword2 = reinterpret_cast<void(*)(BULLET*)>(0x406E60);
const auto ActBullet_Sword3 = reinterpret_cast<void(*)(BULLET*)>(0x407110);
const auto ActBullet_Edge = reinterpret_cast<void(*)(BULLET*)>(0x4075E0);
const auto ActBullet_Drop = reinterpret_cast<void(*)(BULLET*)>(0x4078A0);
const auto ActBullet_SuperMissile = reinterpret_cast<void(*)(BULLET*, int)>(0x407910);
const auto ActBullet_SuperBom = reinterpret_cast<void(*)(BULLET*, int)>(0x408080);
const auto ActBullet_Nemesis = reinterpret_cast<void(*)(BULLET*, int)>(0x408230);
const auto ActBullet_Spur = reinterpret_cast<void(*)(BULLET*, int)>(0x408710);
const auto ActBullet_SpurTail = reinterpret_cast<void(*)(BULLET*, int)>(0x408AE0);
const auto ActBullet_EnemyClear = reinterpret_cast<void(*)(BULLET*)>(0x408F40);
const auto ActBullet_Star = reinterpret_cast<void(*)(BULLET*)>(0x408F90);
const auto ActBullet = reinterpret_cast<void(*)(void)>(0x408FC0);
const auto IsActiveSomeBullet = reinterpret_cast<BOOL(*)(void)>(0x4095C0);
// Caret functions
const auto InitCaret = reinterpret_cast<void(*)(void)>(0x409650);
const CARETFUNCTION ActCaretFn[18] = {
	reinterpret_cast<CARETFUNCTION>(0x409670), // 00
	reinterpret_cast<CARETFUNCTION>(0x409680), // 01
	reinterpret_cast<CARETFUNCTION>(0x409880), // 02
	reinterpret_cast<CARETFUNCTION>(0x409B80), // 03
	reinterpret_cast<CARETFUNCTION>(0x409C70), // 04
	reinterpret_cast<CARETFUNCTION>(0x409E00), // 05
	nullptr,                                   // 06 (nonexistent)
	reinterpret_cast<CARETFUNCTION>(0x409F60), // 07
	reinterpret_cast<CARETFUNCTION>(0x40A120), // 08
	reinterpret_cast<CARETFUNCTION>(0x40A1B0), // 09
	reinterpret_cast<CARETFUNCTION>(0x40A280), // 10
	reinterpret_cast<CARETFUNCTION>(0x40A3F0), // 11
	reinterpret_cast<CARETFUNCTION>(0x40A5A0), // 12
	reinterpret_cast<CARETFUNCTION>(0x40A650), // 13
	reinterpret_cast<CARETFUNCTION>(0x40A7E0), // 14
	reinterpret_cast<CARETFUNCTION>(0x40A8F0), // 15
	reinterpret_cast<CARETFUNCTION>(0x40A9E0), // 16
	reinterpret_cast<CARETFUNCTION>(0x40AAA0)  // 17
};
const auto ActCaret = reinterpret_cast<void(*)(void)>(0x40AB50);
const auto PutCaret = reinterpret_cast<void(*)(int, int)>(0x40ABC0);
const auto SetCaret = reinterpret_cast<void(*)(int, int, int, int)>(0x40AC90);
// Config functions
const auto LoadConfigData = reinterpret_cast<BOOL(*)(ConfigData*)>(0x40AD60);
const auto DefaultConfigData = reinterpret_cast<void(*)(ConfigData*)>(0x40AE30);
// Dialog functions
const auto VersionDialog = reinterpret_cast<DLGPROC>(0x40AEC0);
const auto DebugMuteDialog = reinterpret_cast<DLGPROC>(0x40AFC0);
const auto DebugSaveDialog = reinterpret_cast<DLGPROC>(0x40B1D0);
const auto QuitDialog = reinterpret_cast<DLGPROC>(0x40B290);
// Draw functions
const auto SetClientOffset = reinterpret_cast<void(*)(int, int)>(0x40B320);
const auto Flip_SystemTask = reinterpret_cast<BOOL(*)(HWND)>(0x40B340);
const auto StartDirectDraw = reinterpret_cast<BOOL(*)(HWND, int, int)>(0x40B450);
const auto EndDirectDraw = reinterpret_cast<void(*)(HWND)>(0x40B6C0);
const auto ReleaseSurface = reinterpret_cast<void(*)(int)>(0x40B7A0);
const auto MakeSurface_Resource = reinterpret_cast<BOOL(*)(const char*, int)>(0x40B800);
const auto MakeSurface_File = reinterpret_cast<BOOL(*)(const char*, int)>(0x40BAC0);
const auto ReloadBitmap_Resource = reinterpret_cast<BOOL(*)(const char*, int)>(0x40BE10);
const auto ReloadBitmap_File = reinterpret_cast<BOOL(*)(const char*, int)>(0x40BFD0);
const auto MakeSurface_Generic = reinterpret_cast<BOOL(*)(int, int, int, BOOL)>(0x40C1D0);
const auto BackupSurface = reinterpret_cast<void(*)(int, const ::RECT*)>(0x40C320);
const auto PutBitmap3 = reinterpret_cast<void(*)(const ::RECT*, int, int, const ::RECT*, int)>(0x40C3C0);
const auto PutBitmap4 = reinterpret_cast<void(*)(const ::RECT*, int, int, const ::RECT*, int)>(0x40C5B0);
const auto Surface2Surface = reinterpret_cast<void(*)(int, int, const ::RECT*, int, int)>(0x40C7A0);
const auto GetCortBoxColor = reinterpret_cast<unsigned long(*)(COLORREF)>(0x40C8B0);
const auto CortBox = reinterpret_cast<void(*)(const ::RECT*, unsigned long)>(0x40C9E0);
const auto CortBox2 = reinterpret_cast<void(*)(const ::RECT*, unsigned long, int)>(0x40CA80);
const auto out = reinterpret_cast<BOOL(*)(char)>(0x40CB30);
const auto RestoreSurfaces = reinterpret_cast<int(*)(void)>(0x40CB60);
const auto InitTextObject = reinterpret_cast<void(*)(const char*)>(0x40CD50);
const auto PutText = reinterpret_cast<void(*)(int, int, const char*, unsigned long)>(0x40CE00);
const auto PutText2 = reinterpret_cast<void(*)(int, int, const char*, unsigned long, int)>(0x40CEB0);
const auto EndTextObject = reinterpret_cast<void(*)(void)>(0x40CF70);
// Ending functions
const auto ActionStripper = reinterpret_cast<void(*)(void)>(0x40CF90);
const auto PutStripper = reinterpret_cast<void(*)(void)>(0x40D010);
const auto SetStripper = reinterpret_cast<void(*)(int, int, const char*, int)>(0x40D150);
const auto RestoreStripper = reinterpret_cast<void(*)(void)>(0x40D240);
const auto ActionIllust = reinterpret_cast<void(*)(void)>(0x40D2D0);
const auto PutIllust = reinterpret_cast<void(*)(void)>(0x40D350);
const auto ReloadIllust = reinterpret_cast<void(*)(int)>(0x40D3A0);
const auto InitCreditScript = reinterpret_cast<void(*)(void)>(0x40D3E0);
const auto ReleaseCreditScript = reinterpret_cast<void(*)(void)>(0x40D410);
const auto StartCreditScript = reinterpret_cast<BOOL(*)(void)>(0x40D440);
const auto ActionCredit = reinterpret_cast<void(*)(void)>(0x40D5C0);
const auto ActionCredit_Read = reinterpret_cast<void(*)(void)>(0x40D620);
const auto GetScriptNumber = reinterpret_cast<int(*)(const char*)>(0x40DB00);
const auto SetCreditIllust = reinterpret_cast<void(*)(int)>(0x40DB40);
const auto CutCreditIllust = reinterpret_cast<void(*)(void)>(0x40DB60);
const auto Scene_DownIsland = reinterpret_cast<void(*)(void*, int)>(0x40DB70);
// Escape menu
const auto Call_Escape = reinterpret_cast<int(*)(void*)>(0x40DD70);
// Fade functions
const auto InitFade = reinterpret_cast<void(*)(void)>(0x40DE60);
const auto SetFadeMask = reinterpret_cast<void(*)(void)>(0x40DE90);
const auto ClearFade = reinterpret_cast<void(*)(void)>(0x40DEA0);
const auto StartFadeOut = reinterpret_cast<void(*)(int)>(0x40DEC0);
const auto StartFadeIn = reinterpret_cast<void(*)(int)>(0x40DF50);
const auto ProcFade = reinterpret_cast<void(*)(void)>(0x40DFE0);
const auto PutFade = reinterpret_cast<void(*)(void)>(0x40E770);
const auto GetFadeActive = reinterpret_cast<BOOL(*)(void)>(0x40E830);
// Flag functions
const auto InitFlags = reinterpret_cast<void(*)(void)>(0x40E850);
const auto InitSkipFlags = reinterpret_cast<void(*)(void)>(0x40E870);
const auto SetNPCFlag = reinterpret_cast<void(*)(int)>(0x40E890);
const auto CutNPCFlag = reinterpret_cast<void(*)(int)>(0x40E8E0);
const auto GetNPCFlag = reinterpret_cast<BOOL(*)(int)>(0x40E930);
const auto SetSkipFlag = reinterpret_cast<void(*)(int)>(0x40E970);
const auto CutSkipFlag = reinterpret_cast<void(*)(int)>(0x40E9C0);
const auto GetSkipFlag = reinterpret_cast<BOOL(*)(int)>(0x40EA10);
// Flash functions
const auto InitFlash = reinterpret_cast<void(*)(void)>(0x40EA50);
const auto SetFlash = reinterpret_cast<void(*)(int, int, int)>(0x40EA70);
const auto ActFlash_Explosion = reinterpret_cast<void(*)(int, int)>(0x40EAC0);
const auto ActFlash_Flash = reinterpret_cast<void(*)(void)>(0x40ED20);
const auto ActFlash = reinterpret_cast<void(*)(int, int)>(0x40EDE0);
const auto PutFlash = reinterpret_cast<void(*)(void)>(0x40EE20);
const auto ResetFlash = reinterpret_cast<void(*)(void)>(0x40EE60);
// Frame / camera functions
const auto MoveFrame3 = reinterpret_cast<void(*)(void)>(0x40EE70);
const auto GetFramePosition = reinterpret_cast<void(*)(int*, int*)>(0x40F020);
const auto SetFramePosition = reinterpret_cast<void(*)(int, int)>(0x40F040);
const auto SetFrameMyChar = reinterpret_cast<void(*)(void)>(0x40F130);
const auto SetFrameTargetMyChar = reinterpret_cast<void(*)(int)>(0x40F220);
const auto SetFrameTargetNpChar = reinterpret_cast<void(*)(int, int)>(0x40F250);
const auto SetFrameTargetBoss = reinterpret_cast<void(*)(int, int)>(0x40F2D0);
const auto SetQuake = reinterpret_cast<void(*)(int)>(0x40F310);
const auto SetQuake2 = reinterpret_cast<void(*)(int)>(0x40F320);
const auto ResetQuake = reinterpret_cast<void(*)(void)>(0x40F330);
// Game functions
const auto Random = reinterpret_cast<int(*)(int, int)>(0x40F350);
const auto PutNumber4 = reinterpret_cast<int(*)(int, int, int, BOOL)>(0x40F380);
const auto Game = reinterpret_cast<BOOL(*)(void*)>(0x40F5F0);
const auto ModeOpening = reinterpret_cast<int(*)(void*)>(0x40F730);
const auto ModeTitle = reinterpret_cast<int(*)(void*)>(0x40F9B0);
const auto ModeAction = reinterpret_cast<int(*)(void*)>(0x410400);
// Generic functions
const auto GetCompileDate = reinterpret_cast<void(*)(int*, int*, int*)>(0x4108B0);
const auto GetCompileVersion = reinterpret_cast<BOOL(*)(int*, int*, int*, int*)>(0x410990);
const auto OpenSoundVolume = reinterpret_cast<BOOL(*)(void*)>(0x410AB0); // Technically an HWND parameter
const auto DeleteLog = reinterpret_cast<void(*)(void)>(0x410BC0);
const auto WriteLog = reinterpret_cast<BOOL(*)(const char*, int, int, int)>(0x410C10);
const auto GetDateLimit = reinterpret_cast<int(*)(SYSTEMTIME*, SYSTEMTIME*)>(0x410CA0);
const auto IsKeyFile = reinterpret_cast<BOOL(*)(const char*)>(0x410D10);
const auto GetFileSizeLong = reinterpret_cast<int(*)(const char*)>(0x410D80);
const auto ErrorLog = reinterpret_cast<BOOL(*)(const char*, int)>(0x410DE0);
const auto IsShiftJIS = reinterpret_cast<BOOL(*)(unsigned char)>(0x410E90);
const auto CenteringWindowByParent = reinterpret_cast<BOOL(*)(void*)>(0x410EE0);
const auto LoadWindowRect = reinterpret_cast<BOOL(*)(void*, const char*, BOOL)>(0x410FE0);
const auto SaveWindowRect = reinterpret_cast<BOOL(*)(void*, const char*)>(0x4111F0);
const auto IsEnableBitmap = reinterpret_cast<BOOL(*)(const char*)>(0x4112E0);
// GenericLoad functions
const auto LoadGenericData = reinterpret_cast<BOOL(*)(void)>(0x411390);
// Input functions
const auto ReleaseDirectInput = reinterpret_cast<void(*)(void)>(0x411E10);
const auto ActivateDirectInput = reinterpret_cast<BOOL(*)(BOOL)>(0x411E60);
const auto InitDirectInput = reinterpret_cast<BOOL(*)(HINSTANCE, HWND)>(0x411EB0);
const auto FindAndOpenDirectInputDevice = reinterpret_cast<BOOL(*)(HWND)>(0x411EF0);
const auto EnumDevices_Callback = reinterpret_cast<BOOL(CALLBACK*)(LPCDIDEVICEINSTANCE, LPVOID)>(0x411FC0);
const auto GetJoystickStatus = reinterpret_cast<BOOL(*)(DIRECTINPUTSTATUS*)>(0x4120F0);
const auto ResetJoystickStatus = reinterpret_cast<BOOL(*)(void)>(0x412250);
// KeyControl functions
const auto GetTrg = reinterpret_cast<void(*)(void)>(0x4122E0);
// Main functions
const auto SetWindowName = reinterpret_cast<void(*)(HWND)>(0x412320); // Not the original name
const auto PutFramePerSecound = reinterpret_cast<void(*)(void)>(0x412370);
const auto CountFramePerSecound = reinterpret_cast<unsigned long(*)(void)>(0x4123A0);
// This function is called Freeware_WinMain because we can't call it WinMain
const auto Freeware_WinMain = reinterpret_cast<int(WINAPI*)(HINSTANCE, HINSTANCE, LPSTR, int)>(0x412420);
const auto InactiveWindow = reinterpret_cast<void(*)(void)>(0x412BC0);
const auto ActiveWindow = reinterpret_cast<void(*)(void)>(0x412BF0);
const auto DragAndDropHandler = reinterpret_cast<BOOL(*)(HWND, WPARAM)>(0x412C30);
const auto WindowProcedure = reinterpret_cast<LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM)>(0x412CA0);
const auto SystemTask = reinterpret_cast<BOOL(*)(void)>(0x413570);
const auto JoystickProc = reinterpret_cast<void(*)(void)>(0x4135E0);
// Map functions
const auto InitMapData2 = reinterpret_cast<BOOL(*)(void)>(0x413750);
const auto LoadMapData2 = reinterpret_cast<BOOL(*)(const char*)>(0x413770);
const auto LoadAttributeData = reinterpret_cast<BOOL(*)(const char*)>(0x4138A0);
const auto EndMapData = reinterpret_cast<void(*)(void)>(0x413930);
const auto ReleasePartsImage = reinterpret_cast<void(*)(void)>(0x413950);
const auto GetMapData = reinterpret_cast<void(*)(unsigned char**, short*, short*)>(0x413960);
const auto GetAttribute = reinterpret_cast<unsigned char(*)(int, int)>(0x4139A0);
const auto DeleteMapParts = reinterpret_cast<void(*)(int, int)>(0x413A00);
const auto ShiftMapParts = reinterpret_cast<void(*)(int, int)>(0x413A20);
const auto ChangeMapParts = reinterpret_cast<BOOL(*)(int, int, unsigned char)>(0x413A60);
const auto PutStage_Back = reinterpret_cast<void(*)(int, int)>(0x413AF0);
const auto PutStage_Front = reinterpret_cast<void(*)(int, int)>(0x413C60);
const auto PutMapDataVector = reinterpret_cast<void(*)(int, int)>(0x413E40);
// Map name functions
const auto ReadyMapName = reinterpret_cast<void(*)(const char*)>(0x4140F0);
const auto PutMapName = reinterpret_cast<void(*)(BOOL)>(0x414250);
const auto StartMapName = reinterpret_cast<void(*)(void)>(0x414310);
const auto RestoreMapName = reinterpret_cast<void(*)(void)>(0x414330);
// MiniMap / Map System functions
const auto WriteMiniMapLine = reinterpret_cast<void(*)(int)>(0x4143C0);
const auto MiniMapLoop = reinterpret_cast<int(*)(void)>(0x414640);
const auto IsMapping = reinterpret_cast<BOOL(*)(void)>(0x414B00);
const auto StartMapping = reinterpret_cast<void(*)(void)>(0x414B20);
const auto SetMapping = reinterpret_cast<void(*)(int)>(0x414B40);
// MyChar functions
const auto InitMyChar = reinterpret_cast<void(*)(void)>(0x414B50);
const auto AnimationMyChar = reinterpret_cast<void(*)(BOOL)>(0x414BF0);
const auto ShowMyChar = reinterpret_cast<void(*)(BOOL)>(0x415220);
const auto PutMyChar = reinterpret_cast<void(*)(int, int)>(0x415250);
const auto ActMyChar_Normal = reinterpret_cast<void(*)(BOOL)>(0x4156C0);
const auto ActMyChar_Stream = reinterpret_cast<void(*)(BOOL)>(0x416470);
const auto ActMyChar = reinterpret_cast<void(*)(BOOL)>(0x4168C0);
const auto AirProcess = reinterpret_cast<void(*)(void)>(0x416990);
const auto GetMyCharPosition = reinterpret_cast<void(*)(int*, int*)>(0x416AA0);
const auto SetMyCharPosition = reinterpret_cast<void(*)(int, int)>(0x416AC0);
const auto MoveMyChar = reinterpret_cast<void(*)(int, int)>(0x416B30);
const auto ZeroMyCharXMove = reinterpret_cast<void(*)(void)>(0x416B50);
const auto GetUnitMyChar = reinterpret_cast<int(*)(void)>(0x416B60);
const auto SetMyCharDirect = reinterpret_cast<void(*)(unsigned char)>(0x416B70);
const auto ChangeMyUnit = reinterpret_cast<void(*)(unsigned char)>(0x416C40);
const auto PitMyChar = reinterpret_cast<void(*)(void)>(0x416C50);
const auto EquipItem = reinterpret_cast<void(*)(int, BOOL)>(0x416C70);
const auto ResetCheck = reinterpret_cast<void(*)(void)>(0x416CA0);
// MycHit / MyChar collision functions
const auto ResetMyCharFlag = reinterpret_cast<void(*)(void)>(0x416E20);
const auto JudgeHitMyCharBlock = reinterpret_cast<int(*)(int, int)>(0x416E30);
const auto PutlittleStar = reinterpret_cast<void(*)(void)>(0x417160);
const auto JudgeHitMyCharTriangleA = reinterpret_cast<int(*)(int, int)>(0x4171D0);
const auto JudgeHitMyCharTriangleB = reinterpret_cast<int(*)(int, int)>(0x4172E0);
const auto JudgeHitMyCharTriangleC = reinterpret_cast<int(*)(int, int)>(0x4173F0);
const auto JudgeHitMyCharTriangleD = reinterpret_cast<int(*)(int, int)>(0x417500);
const auto JudgeHitMyCharTriangleE = reinterpret_cast<int(*)(int, int)>(0x417610);
const auto JudgeHitMyCharTriangleF = reinterpret_cast<int(*)(int, int)>(0x417720);
const auto JudgeHitMyCharTriangleG = reinterpret_cast<int(*)(int, int)>(0x417830);
const auto JudgeHitMyCharTriangleH = reinterpret_cast<int(*)(int, int)>(0x417940);
const auto JudgeHitMyCharWater = reinterpret_cast<int(*)(int, int)>(0x417A50);
const auto JudgeHitMyCharDamage = reinterpret_cast<int(*)(int, int)>(0x417AE0);
const auto JudgeHitMyCharDamageW = reinterpret_cast<int(*)(int, int)>(0x417B70);
const auto JudgeHitMyCharVectLeft = reinterpret_cast<int(*)(int, int)>(0x417C00);
const auto JudgeHitMyCharVectUp = reinterpret_cast<int(*)(int, int)>(0x417C90);
const auto JudgeHitMyCharVectRight = reinterpret_cast<int(*)(int, int)>(0x417D20);
const auto JudgeHitMyCharVectDown = reinterpret_cast<int(*)(int, int)>(0x417DB0);
const auto HitMyCharMap = reinterpret_cast<void(*)(void)>(0x417E40);
const auto JudgeHitMyCharNPC = reinterpret_cast<int(*)(NPCHAR*)>(0x4187F0);
const auto JudgeHitMyCharNPC3 = reinterpret_cast<unsigned char(*)(NPCHAR*)>(0x418B10);
const auto JudgeHitMyCharNPC4 = reinterpret_cast<int(*)(NPCHAR*)>(0x418C20);
const auto HitMyCharNpChar = reinterpret_cast<void(*)(void)>(0x419030);
const auto HitMyCharBoss = reinterpret_cast<void(*)(void)>(0x419450);
// MycParam functions
const auto AddExpMyChar = reinterpret_cast<void(*)(int)>(0x4196F0);
const auto ZeroExpMyChar = reinterpret_cast<void(*)(void)>(0x419890);
const auto IsMaxExpMyChar = reinterpret_cast<BOOL(*)(void)>(0x4198C0);
const auto DamageMyChar = reinterpret_cast<void(*)(int)>(0x419910);
const auto ZeroArmsEnergy_All = reinterpret_cast<void(*)(void)>(0x419B50);
const auto AddBulletMyChar = reinterpret_cast<void(*)(int, int)>(0x419BA0);
const auto AddLifeMyChar = reinterpret_cast<void(*)(int)>(0x419C60);
const auto AddMaxLifeMyChar = reinterpret_cast<void(*)(int)>(0x419CB0);
const auto PutArmsEnergy = reinterpret_cast<void(*)(BOOL)>(0x419D10);
const auto PutActiveArmsList = reinterpret_cast<void(*)(void)>(0x41A0B0);
const auto PutMyLife = reinterpret_cast<void(*)(BOOL)>(0x41A1D0);
const auto PutMyAir = reinterpret_cast<void(*)(int, int)>(0x41A350);
const auto PutTimeCounter = reinterpret_cast<void(*)(int, int)>(0x41A430);
const auto SaveTimeCounter = reinterpret_cast<BOOL(*)(void)>(0x41A5D0);
const auto LoadTimeCounter = reinterpret_cast<int(*)(void)>(0x41A7C0);
// Organya functions
const auto MakeSoundObject8 = reinterpret_cast<BOOL(*)(signed char*, signed char, signed char)>(0x41A8F0);
const auto ChangeOrganFrequency = reinterpret_cast<void(*)(unsigned char, signed char, long)>(0x41ABA0);
const auto ChangeOrganPan = reinterpret_cast<void(*)(unsigned char, unsigned char, signed char)>(0x41AC70);
const auto ChangeOrganVolume = reinterpret_cast<void(*)(int, long, signed char)>(0x41AD20);
const auto PlayOrganObject = reinterpret_cast<void(*)(unsigned char, int, signed char, long)>(0x41ADC0);
const auto ReleaseOrganyaObject = reinterpret_cast<void(*)(signed char)>(0x41B2A0);
const auto InitWaveData100 = reinterpret_cast<BOOL(*)(void)>(0x41B380);
const auto MakeOrganyaWave = reinterpret_cast<BOOL(*)(signed char, signed char, signed char)>(0x41B3F0);
const auto ChangeDramFrequency = reinterpret_cast<void(*)(unsigned char, signed char)>(0x41B440);
const auto ChangeDramPan = reinterpret_cast<void(*)(unsigned char, signed char)>(0x41B480);
const auto ChangeDramVolume = reinterpret_cast<void(*)(long, signed char)>(0x41B4D0);
const auto PlayDramObject = reinterpret_cast<void(*)(unsigned char, int, signed char)>(0x41B510);
// Pointers to ORGDATA member functions
namespace OrgData
{
	const auto ctor = reinterpret_cast<ORGDATA * (__thiscall*)(ORGDATA*)>(0x41B600);
	const auto InitOrgData = reinterpret_cast<void(__thiscall*)(ORGDATA*)>(0x41B650);
	const auto SetMusicInfo = reinterpret_cast<BOOL(__thiscall*)(ORGDATA*, MUSICINFO*, unsigned long)>(0x41B730);
	const auto NoteAlloc = reinterpret_cast<BOOL(__thiscall*)(ORGDATA*, unsigned short)>(0x41B890);
	const auto ReleaseNote = reinterpret_cast<void(__thiscall*)(ORGDATA*)>(0x41BA70);
	const auto InitMusicData = reinterpret_cast<BOOL(__thiscall*)(ORGDATA*, const char*)>(0x41BAD0);
	const auto PlayData = reinterpret_cast<void(__thiscall*)(ORGDATA*)>(0x41C2B0);
	const auto SetPlayPointer = reinterpret_cast<void(__thiscall*)(ORGDATA*, long)>(0x41C630);
	const auto GetMusicInfo = reinterpret_cast<void(__thiscall*)(ORGDATA*, MUSICINFO*)>(0x41C0B0);
}
// Wrappers for the above in case you need to call them from within your own code
inline ORGDATA::ORGDATA() : info{}, track{}, mute{}, def_pan{}, def_volume{} // Initialize to shut up compiler warnings
{
	OrgData::ctor(this);
}
inline void ORGDATA::InitOrgData()
{
	return OrgData::InitOrgData(this);
}
inline BOOL ORGDATA::SetMusicInfo(MUSICINFO* mi, unsigned long flag)
{
	return OrgData::SetMusicInfo(this, mi, flag);
}
inline BOOL ORGDATA::NoteAlloc(unsigned short note_num)
{
	return OrgData::NoteAlloc(this, note_num);
}
inline void ORGDATA::ReleaseNote(void)
{
	return OrgData::ReleaseNote(this);
}
inline BOOL ORGDATA::InitMusicData(const char* path)
{
	return OrgData::InitMusicData(this, path);
}
inline void ORGDATA::GetMusicInfo(MUSICINFO* mi)
{
	return OrgData::GetMusicInfo(this, mi);
}
inline void ORGDATA::PlayData(void)
{
	return OrgData::PlayData(this);
}
inline void ORGDATA::SetPlayPointer(long x)
{
	return OrgData::SetPlayPointer(this, x);
}
const auto StartOrganya = reinterpret_cast<BOOL(*)(LPDIRECTSOUND, const char*)>(0x41C6C0);
const auto LoadOrganya = reinterpret_cast<BOOL(*)(const char*)>(0x41C6F0);
const auto SetOrganyaPosition = reinterpret_cast<void(*)(unsigned int)>(0x41C730);
const auto GetOrganyaPosition = reinterpret_cast<unsigned int(*)(void)>(0x41C770);
const auto PlayOrganyaMusic = reinterpret_cast<void(*)(void)>(0x41C790);
const auto ChangeOrganyaVolume = reinterpret_cast<BOOL(*)(int)>(0x41C7C0);
const auto StopOrganyaMusic = reinterpret_cast<void(*)(void)>(0x41C7F0);
const auto SetOrganyaFadeout = reinterpret_cast<void(*)(void)>(0x41C880);
const auto EndOrganya = reinterpret_cast<void(*)(void)>(0x41C890);
// PixTone functions
const auto MakeWaveTables = reinterpret_cast<void(*)(void)>(0x41C8F0);
const auto MakePixelWaveData = reinterpret_cast<BOOL(*)(const PIXTONEPARAMETER*, unsigned char)>(0x41CB10);
// Profile / Save data functions
const auto IsProfile = reinterpret_cast<BOOL(*)(void)>(0x41CFC0);
const auto SaveProfile = reinterpret_cast<BOOL(*)(const char*)>(0x41D040);
const auto LoadProfile = reinterpret_cast<BOOL(*)(const char*)>(0x41D260);
const auto InitializeGame = reinterpret_cast<BOOL(*)(void*)>(0x41D550); // Parameter is technically HWND
// SelStage / Teleporter Menu functions
const auto ClearPermitStage = reinterpret_cast<void(*)(void)>(0x41D610);
const auto AddPermitStage = reinterpret_cast<BOOL(*)(int, int)>(0x41D630);
const auto SubPermitStage = reinterpret_cast<BOOL(*)(int)>(0x41D6A0);
const auto MoveStageSelectCursor = reinterpret_cast<void(*)(void)>(0x41D740);
const auto PutStageSelectObject = reinterpret_cast<void(*)(void)>(0x41D840);
const auto StageSelectLoop = reinterpret_cast<int(*)(int*)>(0x41DA00);
// Shoot functions
const auto ShootBullet_Frontia1 = reinterpret_cast<void(*)(int)>(0x41DBD0);
const auto ShootBullet_PoleStar = reinterpret_cast<void(*)(int)>(0x41DE60);
const auto ShootBullet_FireBall = reinterpret_cast<void(*)(int)>(0x41E110);
const auto ShootBullet_Machinegun1 = reinterpret_cast<void(*)(int)>(0x41E3D0);
const auto ShootBullet_Missile = reinterpret_cast<void(*)(int, BOOL)>(0x41E7B0);
const auto ShootBullet_Bubblin1 = reinterpret_cast<void(*)(void)>(0x41EFD0);
const auto ShootBullet_Bubblin2 = reinterpret_cast<void(*)(int)>(0x41F280);
const auto ShootBullet_Sword = reinterpret_cast<void(*)(int)>(0x41F580);
const auto ShootBullet_Nemesis = reinterpret_cast<void(*)(int)>(0x41F710);
const auto ResetSpurCharge = reinterpret_cast<void(*)(void)>(0x41F9E0);
const auto ShootBullet_Spur = reinterpret_cast<void(*)(int)>(0x41FA10);
const auto ShootBullet = reinterpret_cast<void(*)(void)>(0x41FE70);
// Sound functions
const auto SetNoise = reinterpret_cast<void(*)(int, int)>(0x416CC0);
const auto CutNoise = reinterpret_cast<void(*)(void)>(0x416D40);
const auto ResetNoise = reinterpret_cast<void(*)(void)>(0x416D80);
const auto SleepNoise = reinterpret_cast<void(*)(void)>(0x416DF0);
const auto InitDirectSound = reinterpret_cast<BOOL(*)(HWND)>(0x4200C0);
const auto EndDirectSound = reinterpret_cast<void(*)(void)>(0x4201A0);
const auto InitSoundObject = reinterpret_cast<BOOL(*)(LPCSTR, int)>(0x420240);
const auto LoadSoundObject = reinterpret_cast<BOOL(*)(LPCSTR, int)>(0x420390);
const auto PlaySoundObject = reinterpret_cast<void(*)(int, int)>(0x420640);
const auto ChangeSoundFrequency = reinterpret_cast<void(*)(int, DWORD)>(0x420720);
const auto ChangeSoundVolume = reinterpret_cast<void(*)(int, long)>(0x420760);
const auto ChangeSoundPan = reinterpret_cast<void(*)(int, long)>(0x4207A0);
const auto MakePixToneObject = reinterpret_cast<int(*)(const PIXTONEPARAMETER*, int, int)>(0x4207E0);
// Stage functions
const auto TransferStage = reinterpret_cast<BOOL(*)(int, int, int, int)>(0x420BE0);
const auto ChangeMusic = reinterpret_cast<void(*)(int)>(0x420EE0);
const auto ReCallMusic = reinterpret_cast<void(*)(void)>(0x420F50);
// Star / Whimsical Star functions
const auto InitStar = reinterpret_cast<void(*)(void)>(0x420FA0);
const auto ActStar = reinterpret_cast<void(*)(void)>(0x421040);
const auto PutStar = reinterpret_cast<void(*)(int, int)>(0x4213B0);
// TextScript / TSC functions
const auto InitTextScript2 = reinterpret_cast<BOOL(*)(void)>(0x4214E0);
const auto EndTextScript = reinterpret_cast<void(*)(void)>(0x421570);
const auto EncryptionBinaryData2 = reinterpret_cast<void(*)(unsigned char*, int)>(0x4215C0);
const auto LoadTextScript2 = reinterpret_cast<BOOL(*)(const char*)>(0x421660);
const auto LoadTextScript_Stage = reinterpret_cast<BOOL(*)(const char*)>(0x421750);
const auto GetTextScriptPath = reinterpret_cast<void(*)(char*)>(0x4218E0);
const auto GetTextScriptNo = reinterpret_cast<int(*)(int)>(0x421900);
const auto StartTextScript = reinterpret_cast<BOOL(*)(int)>(0x421990);
const auto JumpTextScript = reinterpret_cast<BOOL(*)(int)>(0x421AF0);
const auto StopTextScript = reinterpret_cast<void(*)(void)>(0x421C50);
const auto CheckNewLine = reinterpret_cast<void(*)(void)>(0x421C80);
const auto SetNumberTextScript = reinterpret_cast<void(*)(int)>(0x421D10);
const auto ClearTextLine = reinterpret_cast<void(*)(void)>(0x421E90);
const auto PutTextScript = reinterpret_cast<void(*)(void)>(0x421F10);
const auto TextScriptProc = reinterpret_cast<int(*)(void)>(0x422510);
const auto RestoreTextScript = reinterpret_cast<void(*)(void)>(0x425790);
// Triangle functions
const auto InitTriangleTable = reinterpret_cast<void(*)(void)>(0x4257F0);
const auto GetSin = reinterpret_cast<int(*)(unsigned char)>(0x4258B0);
const auto GetCos = reinterpret_cast<int(*)(unsigned char)>(0x4258C0);
const auto GetArktan = reinterpret_cast<unsigned char(*)(int, int)>(0x4258E0);
// ValueView functions
const auto ClearValueView = reinterpret_cast<void(*)(void)>(0x425BC0);
const auto SetValueView = reinterpret_cast<void(*)(int*, int*, int)>(0x425BF0);
const auto ActValueView = reinterpret_cast<void(*)(void)>(0x426360);
const auto PutValueView = reinterpret_cast<void(*)(int, int)>(0x426430);
// ActNpc function list (000 - 361)
static void (* const ActNpc000)(NPCHAR* npc) = (void(*)(NPCHAR*))0x426530;
static void (* const ActNpc001)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4265B0;
static void (* const ActNpc002)(NPCHAR* npc) = (void(*)(NPCHAR*))0x426AF0;
static void (* const ActNpc003)(NPCHAR* npc) = (void(*)(NPCHAR*))0x426FD0;
static void (* const ActNpc004)(NPCHAR* npc) = (void(*)(NPCHAR*))0x427040;
static void (* const ActNpc005)(NPCHAR* npc) = (void(*)(NPCHAR*))0x427480;
static void (* const ActNpc006)(NPCHAR* npc) = (void(*)(NPCHAR*))0x427820;
static void (* const ActNpc007)(NPCHAR* npc) = (void(*)(NPCHAR*))0x427C60;
static void (* const ActNpc008)(NPCHAR* npc) = (void(*)(NPCHAR*))0x427F00;
static void (* const ActNpc009)(NPCHAR* npc) = (void(*)(NPCHAR*))0x428260;
static void (* const ActNpc010)(NPCHAR* npc) = (void(*)(NPCHAR*))0x428540;
static void (* const ActNpc011)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4289B0;
static void (* const ActNpc012)(NPCHAR* npc) = (void(*)(NPCHAR*))0x428B10;
static void (* const ActNpc013)(NPCHAR* npc) = (void(*)(NPCHAR*))0x429940;
static void (* const ActNpc014)(NPCHAR* npc) = (void(*)(NPCHAR*))0x429A30;
static void (* const ActNpc015)(NPCHAR* npc) = (void(*)(NPCHAR*))0x429BF0;
static void (* const ActNpc016)(NPCHAR* npc) = (void(*)(NPCHAR*))0x429E00;
static void (* const ActNpc017)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42A0B0;
static void (* const ActNpc018)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42A360;
static void (* const ActNpc019)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42A490;
static void (* const ActNpc020)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42A830;
static void (* const ActNpc021)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42A940;
static void (* const ActNpc022)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42A9C0;
static void (* const ActNpc023)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42AA70;
static void (* const ActNpc024)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42ABD0;
static void (* const ActNpc025)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42B280;
static void (* const ActNpc026)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42B5E0;
static void (* const ActNpc027)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42BA90;
static void (* const ActNpc028)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42BAE0;
static void (* const ActNpc029)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42C1A0;
static void (* const ActNpc030)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42C320;
static void (* const ActNpc031)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42C4C0;
static void (* const ActNpc032)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42CA10;
static void (* const ActNpc033)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42CAC0;
static void (* const ActNpc034)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42CC20;
static void (* const ActNpc035)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42CCB0;
static void (* const ActNpc036)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42D010;
static void (* const ActNpc037)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42D760;
static void (* const ActNpc038)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42D810;
static void (* const ActNpc039)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42D960;
static void (* const ActNpc040)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42D9F0;
static void (* const ActNpc041)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42DE00;
static void (* const ActNpc042)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42DE70;
static void (* const ActNpc043)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42E9F0;
static void (* const ActNpc044)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42EAB0;
static void (* const ActNpc045)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42F060;
static void (* const ActNpc046)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42F320;
static void (* const ActNpc047)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42F3F0;
static void (* const ActNpc048)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42F780;
static void (* const ActNpc049)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42F9E0;
static void (* const ActNpc050)(NPCHAR* npc) = (void(*)(NPCHAR*))0x42FEC0;
static void (* const ActNpc051)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4301B0;
static void (* const ActNpc052)(NPCHAR* npc) = (void(*)(NPCHAR*))0x430780;
static void (* const ActNpc053)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4307D0;
static void (* const ActNpc054)(NPCHAR* npc) = (void(*)(NPCHAR*))0x430B00;
static void (* const ActNpc055)(NPCHAR* npc) = (void(*)(NPCHAR*))0x430EB0;
static void (* const ActNpc056)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4311D0;
static void (* const ActNpc057)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4315E0;
static void (* const ActNpc058)(NPCHAR* npc) = (void(*)(NPCHAR*))0x431C20;
static void (* const ActNpc059)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4321F0;
static void (* const ActNpc060)(NPCHAR* npc) = (void(*)(NPCHAR*))0x432460;
static void (* const ActNpc061)(NPCHAR* npc) = (void(*)(NPCHAR*))0x432B50;
static void (* const ActNpc062)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4334C0;
static void (* const ActNpc063)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4336C0;
static void (* const ActNpc064)(NPCHAR* npc) = (void(*)(NPCHAR*))0x433C00;
static void (* const ActNpc065)(NPCHAR* npc) = (void(*)(NPCHAR*))0x433FC0;
static void (* const ActNpc066)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4342B0;
static void (* const ActNpc067)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4345E0;
static void (* const ActNpc068)(NPCHAR* npc) = (void(*)(NPCHAR*))0x434D10;
static void (* const ActNpc069)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4355F0;
static void (* const ActNpc070)(NPCHAR* npc) = (void(*)(NPCHAR*))0x435AB0;
static void (* const ActNpc071)(NPCHAR* npc) = (void(*)(NPCHAR*))0x435BA0;
static void (* const ActNpc072)(NPCHAR* npc) = (void(*)(NPCHAR*))0x435DE0;
static void (* const ActNpc073)(NPCHAR* npc) = (void(*)(NPCHAR*))0x435FC0;
static void (* const ActNpc074)(NPCHAR* npc) = (void(*)(NPCHAR*))0x436180;
static void (* const ActNpc075)(NPCHAR* npc) = (void(*)(NPCHAR*))0x436540;
static void (* const ActNpc076)(NPCHAR* npc) = (void(*)(NPCHAR*))0x436650;
static void (* const ActNpc077)(NPCHAR* npc) = (void(*)(NPCHAR*))0x436690;
static void (* const ActNpc078)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4367E0;
static void (* const ActNpc079)(NPCHAR* npc) = (void(*)(NPCHAR*))0x436870;
static void (* const ActNpc080)(NPCHAR* npc) = (void(*)(NPCHAR*))0x436AE0;
static void (* const ActNpc081)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4370F0;
static void (* const ActNpc082)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4375E0;
static void (* const ActNpc083)(NPCHAR* npc) = (void(*)(NPCHAR*))0x437D90;
static void (* const ActNpc084)(NPCHAR* npc) = (void(*)(NPCHAR*))0x438250;
static void (* const ActNpc085)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4383D0;
static void (* const ActNpc086)(NPCHAR* npc) = (void(*)(NPCHAR*))0x438590;
static void (* const ActNpc087)(NPCHAR* npc) = (void(*)(NPCHAR*))0x438850;
static void (* const ActNpc088)(NPCHAR* npc) = (void(*)(NPCHAR*))0x438B10;
static void (* const ActNpc089)(NPCHAR* npc) = (void(*)(NPCHAR*))0x439580;
static void (* const ActNpc090)(NPCHAR* npc) = (void(*)(NPCHAR*))0x439B00;
static void (* const ActNpc091)(NPCHAR* npc) = (void(*)(NPCHAR*))0x439B50;
static void (* const ActNpc092)(NPCHAR* npc) = (void(*)(NPCHAR*))0x439BC0;
static void (* const ActNpc093)(NPCHAR* npc) = (void(*)(NPCHAR*))0x439DC0;
static void (* const ActNpc094)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43A220;
static void (* const ActNpc095)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43A680;
static void (* const ActNpc096)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43AAF0;
static void (* const ActNpc097)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43AD10;
static void (* const ActNpc098)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43AF20;
static void (* const ActNpc099)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43B140;
static void (* const ActNpc100)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43B350;
static void (* const ActNpc101)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43B410;
static void (* const ActNpc102)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43B4E0;
static void (* const ActNpc103)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43B5F0;
static void (* const ActNpc104)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43B7F0;
static void (* const ActNpc105)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43BD00;
static void (* const ActNpc106)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43BDB0;
static void (* const ActNpc107)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43BE00;
static void (* const ActNpc108)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43C4B0;
static void (* const ActNpc109)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43C610;
static void (* const ActNpc110)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43C8E0;
static void (* const ActNpc111)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43CDE0;
static void (* const ActNpc112)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43D0A0;
static void (* const ActNpc113)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43D320;
static void (* const ActNpc114)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43D860;
static void (* const ActNpc115)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43DAE0;
static void (* const ActNpc116)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43E190;
static void (* const ActNpc117)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43E1E0;
static void (* const ActNpc118)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43E9B0;
static void (* const ActNpc119)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43F230;
static void (* const ActNpc120)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43F280;
static void (* const ActNpc121)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43F310;
static void (* const ActNpc122)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43F4A0;
static void (* const ActNpc123)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43FC70;
static void (* const ActNpc124)(NPCHAR* npc) = (void(*)(NPCHAR*))0x43FEF0;
static void (* const ActNpc125)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4400D0;
static void (* const ActNpc126)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4401F0;
static void (* const ActNpc127)(NPCHAR* npc) = (void(*)(NPCHAR*))0x440760;
static void (* const ActNpc128)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4408B0;
static void (* const ActNpc129)(NPCHAR* npc) = (void(*)(NPCHAR*))0x440CF0;
static void (* const ActNpc130)(NPCHAR* npc) = (void(*)(NPCHAR*))0x441000;
static void (* const ActNpc131)(NPCHAR* npc) = (void(*)(NPCHAR*))0x441360;
static void (* const ActNpc132)(NPCHAR* npc) = (void(*)(NPCHAR*))0x441440;
static void (* const ActNpc133)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4419B0;
static void (* const ActNpc134)(NPCHAR* npc) = (void(*)(NPCHAR*))0x441B20;
static void (* const ActNpc135)(NPCHAR* npc) = (void(*)(NPCHAR*))0x441EC0;
static void (* const ActNpc136)(NPCHAR* npc) = (void(*)(NPCHAR*))0x442340;
static void (* const ActNpc137)(NPCHAR* npc) = (void(*)(NPCHAR*))0x442540;
static void (* const ActNpc138)(NPCHAR* npc) = (void(*)(NPCHAR*))0x442590;
static void (* const ActNpc139)(NPCHAR* npc) = (void(*)(NPCHAR*))0x442790;
static void (* const ActNpc140)(NPCHAR* npc) = (void(*)(NPCHAR*))0x442BF0;
static void (* const ActNpc141)(NPCHAR* npc) = (void(*)(NPCHAR*))0x443AC0;
static void (* const ActNpc142)(NPCHAR* npc) = (void(*)(NPCHAR*))0x443EC0;
static void (* const ActNpc143)(NPCHAR* npc) = (void(*)(NPCHAR*))0x444190;
static void (* const ActNpc144)(NPCHAR* npc) = (void(*)(NPCHAR*))0x444230;
static void (* const ActNpc145)(NPCHAR* npc) = (void(*)(NPCHAR*))0x444620;
static void (* const ActNpc146)(NPCHAR* npc) = (void(*)(NPCHAR*))0x444780;
static void (* const ActNpc147)(NPCHAR* npc) = (void(*)(NPCHAR*))0x444930;
static void (* const ActNpc148)(NPCHAR* npc) = (void(*)(NPCHAR*))0x445050;
static void (* const ActNpc149)(NPCHAR* npc) = (void(*)(NPCHAR*))0x445170;
static void (* const ActNpc150)(NPCHAR* npc) = (void(*)(NPCHAR*))0x445660;
static void (* const ActNpc151)(NPCHAR* npc) = (void(*)(NPCHAR*))0x445E30;
static void (* const ActNpc152)(NPCHAR* npc) = (void(*)(NPCHAR*))0x445FA0;
static void (* const ActNpc153)(NPCHAR* npc) = (void(*)(NPCHAR*))0x446020;
static void (* const ActNpc154)(NPCHAR* npc) = (void(*)(NPCHAR*))0x446500;
static void (* const ActNpc155)(NPCHAR* npc) = (void(*)(NPCHAR*))0x446710;
static void (* const ActNpc156)(NPCHAR* npc) = (void(*)(NPCHAR*))0x446B60;
static void (* const ActNpc157)(NPCHAR* npc) = (void(*)(NPCHAR*))0x446CA0;
static void (* const ActNpc158)(NPCHAR* npc) = (void(*)(NPCHAR*))0x447180;
static void (* const ActNpc159)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4474C0;
static void (* const ActNpc160)(NPCHAR* npc) = (void(*)(NPCHAR*))0x447700;
static void (* const ActNpc161)(NPCHAR* npc) = (void(*)(NPCHAR*))0x447CB0;
static void (* const ActNpc162)(NPCHAR* npc) = (void(*)(NPCHAR*))0x447E90;
static void (* const ActNpc163)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4482A0;
static void (* const ActNpc164)(NPCHAR* npc) = (void(*)(NPCHAR*))0x448410;
static void (* const ActNpc165)(NPCHAR* npc) = (void(*)(NPCHAR*))0x448580;
static void (* const ActNpc166)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4486E0;
static void (* const ActNpc167)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4487F0;
static void (* const ActNpc168)(NPCHAR* npc) = (void(*)(NPCHAR*))0x448A10;
static void (* const ActNpc169)(NPCHAR* npc) = (void(*)(NPCHAR*))0x448BE0;
static void (* const ActNpc170)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4495A0;
static void (* const ActNpc171)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4498C0;
static void (* const ActNpc172)(NPCHAR* npc) = (void(*)(NPCHAR*))0x449C10;
static void (* const ActNpc173)(NPCHAR* npc) = (void(*)(NPCHAR*))0x449D70;
static void (* const ActNpc174)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44A3C0;
static void (* const ActNpc175)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44A610;
static void (* const ActNpc176)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44A7D0;
static void (* const ActNpc177)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44ABB0;
static void (* const ActNpc178)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44AEE0;
static void (* const ActNpc179)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44B080;
static void (* const ActNpc180)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44B210;
static void (* const ActNpc181)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44BE10;
static void (* const ActNpc182)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44C220;
static void (* const ActNpc183)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44C630;
static void (* const ActNpc184)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44C7A0;
static void (* const ActNpc185)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44CA60;
static void (* const ActNpc186)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44CBE0;
static void (* const ActNpc187)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44CDB0;
static void (* const ActNpc188)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44D070;
static void (* const ActNpc189)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44D3A0;
static void (* const ActNpc190)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44D5E0;
static void (* const ActNpc191)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44D740;
static void (* const ActNpc192)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44DA00;
static void (* const ActNpc193)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44DE20;
static void (* const ActNpc194)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44DEA0;
static void (* const ActNpc195)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44DF10;
static void (* const ActNpc196)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44DF60;
static void (* const ActNpc197)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44E020;
static void (* const ActNpc198)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44E260;
static void (* const ActNpc199)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44E400;
static void (* const ActNpc200)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44E5F0;
static void (* const ActNpc201)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44EC40;
static void (* const ActNpc202)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44ECE0;
static void (* const ActNpc203)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44EE40;
static void (* const ActNpc204)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44F1F0;
static void (* const ActNpc205)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44F3E0;
static void (* const ActNpc206)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44F6D0;
static void (* const ActNpc207)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44FB40;
static void (* const ActNpc208)(NPCHAR* npc) = (void(*)(NPCHAR*))0x44FCB0;
static void (* const ActNpc209)(NPCHAR* npc) = (void(*)(NPCHAR*))0x450280;
static void (* const ActNpc210)(NPCHAR* npc) = (void(*)(NPCHAR*))0x450400;
static void (* const ActNpc211)(NPCHAR* npc) = (void(*)(NPCHAR*))0x450760;
static void (* const ActNpc212)(NPCHAR* npc) = (void(*)(NPCHAR*))0x450810;
static void (* const ActNpc213)(NPCHAR* npc) = (void(*)(NPCHAR*))0x450BF0;
static void (* const ActNpc214)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4512A0;
static void (* const ActNpc215)(NPCHAR* npc) = (void(*)(NPCHAR*))0x451430;
static void (* const ActNpc216)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4517F0;
static void (* const ActNpc217)(NPCHAR* npc) = (void(*)(NPCHAR*))0x451840;
static void (* const ActNpc218)(NPCHAR* npc) = (void(*)(NPCHAR*))0x451CA0;
static void (* const ActNpc219)(NPCHAR* npc) = (void(*)(NPCHAR*))0x451DA0;
static void (* const ActNpc220)(NPCHAR* npc) = (void(*)(NPCHAR*))0x451E90;
static void (* const ActNpc221)(NPCHAR* npc) = (void(*)(NPCHAR*))0x452000;
static void (* const ActNpc222)(NPCHAR* npc) = (void(*)(NPCHAR*))0x452470;
static void (* const ActNpc223)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4524E0;
static void (* const ActNpc224)(NPCHAR* npc) = (void(*)(NPCHAR*))0x452700;
static void (* const ActNpc225)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4528D0;
static void (* const ActNpc226)(NPCHAR* npc) = (void(*)(NPCHAR*))0x452A50;
static void (* const ActNpc227)(NPCHAR* npc) = (void(*)(NPCHAR*))0x452D10;
static void (* const ActNpc228)(NPCHAR* npc) = (void(*)(NPCHAR*))0x452D60;
static void (* const ActNpc229)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4530D0;
static void (* const ActNpc230)(NPCHAR* npc) = (void(*)(NPCHAR*))0x453190;
static void (* const ActNpc231)(NPCHAR* npc) = (void(*)(NPCHAR*))0x453260;
static void (* const ActNpc232)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4536F0;
static void (* const ActNpc233)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4539B0;
static void (* const ActNpc234)(NPCHAR* npc) = (void(*)(NPCHAR*))0x453E60;
static void (* const ActNpc235)(NPCHAR* npc) = (void(*)(NPCHAR*))0x453F20;
static void (* const ActNpc236)(NPCHAR* npc) = (void(*)(NPCHAR*))0x454310;
static void (* const ActNpc237)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4548B0;
static void (* const ActNpc238)(NPCHAR* npc) = (void(*)(NPCHAR*))0x454A00;
static void (* const ActNpc239)(NPCHAR* npc) = (void(*)(NPCHAR*))0x454DF0;
static void (* const ActNpc240)(NPCHAR* npc) = (void(*)(NPCHAR*))0x454F00;
static void (* const ActNpc241)(NPCHAR* npc) = (void(*)(NPCHAR*))0x455370;
static void (* const ActNpc242)(NPCHAR* npc) = (void(*)(NPCHAR*))0x455710;
static void (* const ActNpc243)(NPCHAR* npc) = (void(*)(NPCHAR*))0x455A10;
static void (* const ActNpc244)(NPCHAR* npc) = (void(*)(NPCHAR*))0x455AB0;
static void (* const ActNpc245)(NPCHAR* npc) = (void(*)(NPCHAR*))0x455C10;
static void (* const ActNpc246)(NPCHAR* npc) = (void(*)(NPCHAR*))0x455E00;
static void (* const ActNpc247)(NPCHAR* npc) = (void(*)(NPCHAR*))0x456110;
static void (* const ActNpc248)(NPCHAR* npc) = (void(*)(NPCHAR*))0x456F50;
static void (* const ActNpc249)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4570B0;
static void (* const ActNpc250)(NPCHAR* npc) = (void(*)(NPCHAR*))0x457180;
static void (* const ActNpc251)(NPCHAR* npc) = (void(*)(NPCHAR*))0x457470;
static void (* const ActNpc252)(NPCHAR* npc) = (void(*)(NPCHAR*))0x457570;
static void (* const ActNpc253)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4579D0;
static void (* const ActNpc254)(NPCHAR* npc) = (void(*)(NPCHAR*))0x457B00;
static void (* const ActNpc255)(NPCHAR* npc) = (void(*)(NPCHAR*))0x457D70;
static void (* const ActNpc256)(NPCHAR* npc) = (void(*)(NPCHAR*))0x458010;
static void (* const ActNpc257)(NPCHAR* npc) = (void(*)(NPCHAR*))0x458360;
static void (* const ActNpc258)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4585A0;
static void (* const ActNpc259)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4585F0;
static void (* const ActNpc260)(NPCHAR* npc) = (void(*)(NPCHAR*))0x458810;
static void (* const ActNpc261)(NPCHAR* npc) = (void(*)(NPCHAR*))0x458A70;
static void (* const ActNpc262)(NPCHAR* npc) = (void(*)(NPCHAR*))0x458C30;
static void (* const ActNpc263)(NPCHAR* npc) = (void(*)(NPCHAR*))0x458DF0;
static void (* const ActNpc264)(NPCHAR* npc) = (void(*)(NPCHAR*))0x459950;
static void (* const ActNpc265)(NPCHAR* npc) = (void(*)(NPCHAR*))0x459B30;
static void (* const ActNpc266)(NPCHAR* npc) = (void(*)(NPCHAR*))0x459C00;
static void (* const ActNpc267)(NPCHAR* npc) = (void(*)(NPCHAR*))0x459D80;
static void (* const ActNpc268)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45B3D0;
static void (* const ActNpc269)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45BCB0;
static void (* const ActNpc270)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45BF10;
static void (* const ActNpc271)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45C230;
static void (* const ActNpc272)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45C500;
static void (* const ActNpc273)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45C5A0;
static void (* const ActNpc274)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45C750;
static void (* const ActNpc275)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45CC80;
static void (* const ActNpc276)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45CEA0;
static void (* const ActNpc277)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45D780;
static void (* const ActNpc278)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45D930;
static void (* const ActNpc279)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45DCF0;
static void (* const ActNpc280)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45E110;
static void (* const ActNpc281)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45E360;
static void (* const ActNpc282)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45E4C0;
static void (* const ActNpc283)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45E950;
static void (* const ActNpc284)(NPCHAR* npc) = (void(*)(NPCHAR*))0x45F910;
static void (* const ActNpc285)(NPCHAR* npc) = (void(*)(NPCHAR*))0x460910;
static void (* const ActNpc286)(NPCHAR* npc) = (void(*)(NPCHAR*))0x460AE0;
static void (* const ActNpc287)(NPCHAR* npc) = (void(*)(NPCHAR*))0x460BB0;
static void (* const ActNpc288)(NPCHAR* npc) = (void(*)(NPCHAR*))0x460D70;
static void (* const ActNpc289)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4610D0;
static void (* const ActNpc290)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4614A0;
static void (* const ActNpc291)(NPCHAR* npc) = (void(*)(NPCHAR*))0x461800;
static void (* const ActNpc292)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4618B0;
static void (* const ActNpc293)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4618C0;
static void (* const ActNpc294)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4619E0;
static void (* const ActNpc295)(NPCHAR* npc) = (void(*)(NPCHAR*))0x461B90;
static void (* const ActNpc296)(NPCHAR* npc) = (void(*)(NPCHAR*))0x461E40;
static void (* const ActNpc297)(NPCHAR* npc) = (void(*)(NPCHAR*))0x461FD0;
static void (* const ActNpc298)(NPCHAR* npc) = (void(*)(NPCHAR*))0x462050;
static void (* const ActNpc299)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4623D0;
static void (* const ActNpc300)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4624E0;
static void (* const ActNpc301)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4625A0;
static void (* const ActNpc302)(NPCHAR* npc) = (void(*)(NPCHAR*))0x462890;
static void (* const ActNpc303)(NPCHAR* npc) = (void(*)(NPCHAR*))0x462AF0;
static void (* const ActNpc304)(NPCHAR* npc) = (void(*)(NPCHAR*))0x462C80;
static void (* const ActNpc305)(NPCHAR* npc) = (void(*)(NPCHAR*))0x462E00;
static void (* const ActNpc306)(NPCHAR* npc) = (void(*)(NPCHAR*))0x462F60;
static void (* const ActNpc307)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4630F0;
static void (* const ActNpc308)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4632B0;
static void (* const ActNpc309)(NPCHAR* npc) = (void(*)(NPCHAR*))0x463710;
static void (* const ActNpc310)(NPCHAR* npc) = (void(*)(NPCHAR*))0x463AC0;
static void (* const ActNpc311)(NPCHAR* npc) = (void(*)(NPCHAR*))0x464090;
static void (* const ActNpc312)(NPCHAR* npc) = (void(*)(NPCHAR*))0x464740;
static void (* const ActNpc313)(NPCHAR* npc) = (void(*)(NPCHAR*))0x464BB0;
static void (* const ActNpc314)(NPCHAR* npc) = (void(*)(NPCHAR*))0x465CC0;
static void (* const ActNpc315)(NPCHAR* npc) = (void(*)(NPCHAR*))0x465F60;
static void (* const ActNpc316)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4664B0;
static void (* const ActNpc317)(NPCHAR* npc) = (void(*)(NPCHAR*))0x466790;
static void (* const ActNpc318)(NPCHAR* npc) = (void(*)(NPCHAR*))0x466B80;
static void (* const ActNpc319)(NPCHAR* npc) = (void(*)(NPCHAR*))0x466E50;
static void (* const ActNpc320)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4670C0;
static void (* const ActNpc321)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4673F0;
static void (* const ActNpc322)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4676D0;
static void (* const ActNpc323)(NPCHAR* npc) = (void(*)(NPCHAR*))0x467C60;
static void (* const ActNpc324)(NPCHAR* npc) = (void(*)(NPCHAR*))0x467F40;
static void (* const ActNpc325)(NPCHAR* npc) = (void(*)(NPCHAR*))0x467FE0;
static void (* const ActNpc326)(NPCHAR* npc) = (void(*)(NPCHAR*))0x468230;
static void (* const ActNpc327)(NPCHAR* npc) = (void(*)(NPCHAR*))0x468830;
static void (* const ActNpc328)(NPCHAR* npc) = (void(*)(NPCHAR*))0x468990;
static void (* const ActNpc329)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4689E0;
static void (* const ActNpc330)(NPCHAR* npc) = (void(*)(NPCHAR*))0x468A90;
static void (* const ActNpc331)(NPCHAR* npc) = (void(*)(NPCHAR*))0x468D70;
static void (* const ActNpc332)(NPCHAR* npc) = (void(*)(NPCHAR*))0x468F50;
static void (* const ActNpc333)(NPCHAR* npc) = (void(*)(NPCHAR*))0x469140;
static void (* const ActNpc334)(NPCHAR* npc) = (void(*)(NPCHAR*))0x469290;
static void (* const ActNpc335)(NPCHAR* npc) = (void(*)(NPCHAR*))0x469430;
static void (* const ActNpc336)(NPCHAR* npc) = (void(*)(NPCHAR*))0x469610;
static void (* const ActNpc337)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4696B0;
static void (* const ActNpc338)(NPCHAR* npc) = (void(*)(NPCHAR*))0x469800;
static void (* const ActNpc339)(NPCHAR* npc) = (void(*)(NPCHAR*))0x469AA0;
static void (* const ActNpc340)(NPCHAR* npc) = (void(*)(NPCHAR*))0x469B40;
static void (* const ActNpc341)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46B240;
static void (* const ActNpc342)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46B340;
static void (* const ActNpc343)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46BD80;
static void (* const ActNpc344)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46BE10;
static void (* const ActNpc345)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46BF00;
static void (* const ActNpc346)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46C1D0;
static void (* const ActNpc347)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46C710;
static void (* const ActNpc348)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46C9B0;
static void (* const ActNpc349)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46CAC0;
static void (* const ActNpc350)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46CB50;
static void (* const ActNpc351)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46D340;
static void (* const ActNpc352)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46D5D0;
static void (* const ActNpc353)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46DBE0;
static void (* const ActNpc354)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46E110;
static void (* const ActNpc355)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46E280;
static void (* const ActNpc356)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46E480;
static void (* const ActNpc357)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46E730;
static void (* const ActNpc358)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46E870;
static void (* const ActNpc359)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46E9E0;
static void (* const ActNpc360)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46EA90;
// NpChar functions
const auto InitNpChar = reinterpret_cast<void(*)(void)>(0x46EB30);
const auto LoadEvent = reinterpret_cast<BOOL(*)(const char*)>(0x46EB50);
const auto SetUniqueParameter = reinterpret_cast<void(*)(NPCHAR*)>(0x46EE50);
const auto SetNpChar = reinterpret_cast<void(*)(int, int, int, int, int, int, NPCHAR*, int)>(0x46EFD0);
const auto SetDestroyNpChar = reinterpret_cast<void(*)(int, int, int, int)>(0x46F150);
const auto SetDestroyNpCharUp = reinterpret_cast<void(*)(int, int, int, int)>(0x46F200);
const auto SetExpObjects = reinterpret_cast<void(*)(int, int, int)>(0x46F2B0);
const auto SetBulletObject = reinterpret_cast<BOOL(*)(int, int, int)>(0x46F430);
const auto SetLifeObject = reinterpret_cast<BOOL(*)(int, int, int)>(0x46F630);
const auto VanishNpChar = reinterpret_cast<void(*)(NPCHAR*)>(0x46F760);
const auto PutNpChar = reinterpret_cast<void(*)(int, int)>(0x46F810);
const auto ActNpChar = reinterpret_cast<void(*)(void)>(0x46FA00);
const auto ChangeNpCharByEvent = reinterpret_cast<void(*)(int, int, int)>(0x46FAB0);
const auto ChangeCheckableNpCharByEvent = reinterpret_cast<void(*)(int, int, int)>(0x46FD10);
const auto SetNpCharActionNo = reinterpret_cast<void(*)(int, int, int)>(0x46FF90);
const auto MoveNpChar = reinterpret_cast<void(*)(int, int, int, int)>(0x470060);
const auto BackStepMyChar = reinterpret_cast<void(*)(int)>(0x470150);
const auto DeleteNpCharEvent = reinterpret_cast<void(*)(int)>(0x470250);
const auto DeleteNpCharCode = reinterpret_cast<void(*)(int, BOOL)>(0x4702D0);
const auto GetNpCharPosition = reinterpret_cast<void(*)(int*, int*, int)>(0x470460);
const auto IsNpCharCode = reinterpret_cast<BOOL(*)(int)>(0x470490);
const auto GetNpCharAlive = reinterpret_cast<BOOL(*)(int)>(0x4704F0);
const auto CountAliveNpChar = reinterpret_cast<int(*)(void)>(0x470560);
// NpcHit / Npc collision functions
const auto JadgeHitNpCharBlock = reinterpret_cast<void(*)(NPCHAR*, int, int)>(0x4705C0);
const auto JudgeHitNpCharTriangleA = reinterpret_cast<void(*)(NPCHAR*, int, int)>(0x470870);
const auto JudgeHitNpCharTriangleB = reinterpret_cast<void(*)(NPCHAR*, int, int)>(0x470970);
const auto JudgeHitNpCharTriangleC = reinterpret_cast<void(*)(NPCHAR*, int, int)>(0x470A70);
const auto JudgeHitNpCharTriangleD = reinterpret_cast<void(*)(NPCHAR*, int, int)>(0x470B70);
const auto JudgeHitNpCharTriangleE = reinterpret_cast<void(*)(NPCHAR*, int, int)>(0x470C70);
const auto JudgeHitNpCharTriangleF = reinterpret_cast<void(*)(NPCHAR*, int, int)>(0x470D80);
const auto JudgeHitNpCharTriangleG = reinterpret_cast<void(*)(NPCHAR*, int, int)>(0x470E90);
const auto JudgeHitNpCharTriangleH = reinterpret_cast<void(*)(NPCHAR*, int, int)>(0x470FA0);
const auto JudgeHitNpCharWater = reinterpret_cast<void(*)(NPCHAR*, int, int)>(0x4710B0);
const auto HitNpCharMap = reinterpret_cast<void(*)(void)>(0x471160);
const auto LoseNpChar = reinterpret_cast<void(*)(NPCHAR*, BOOL)>(0x471B80);
const auto HitNpCharBullet = reinterpret_cast<void(*)(void)>(0x471D50);
// NpcTbl / Npc Table functions
const auto LoadNpcTable = reinterpret_cast<BOOL(*)(const char*)>(0x472400);
const auto ReleaseNpcTable = reinterpret_cast<void(*)(void)>(0x472710);
// Boss functions
const auto InitBossChar = reinterpret_cast<void(*)(int)>(0x472740);
const auto PutBossChar = reinterpret_cast<void(*)(int, int)>(0x472770);
const auto SetBossCharActNo = reinterpret_cast<void(*)(int)>(0x472940);
const auto HitBossBullet = reinterpret_cast<void(*)(void)>(0x472950);
const auto ActBossChar_0 = reinterpret_cast<void(*)(void)>(0x472FF0);
const auto ActBossChar = reinterpret_cast<void(*)(void)>(0x473000);
const auto HitBossMap = reinterpret_cast<void(*)(void)>(0x473080);
// Core boss
const auto ActBossChar_Core_Face = reinterpret_cast<void(*)(NPCHAR*)>(0x4739B0);
const auto ActBossChar_Core_Tail = reinterpret_cast<void(*)(NPCHAR*)>(0x473BD0);
const auto ActBossChar_Core_Mini = reinterpret_cast<void(*)(NPCHAR*)>(0x473DE0);
const auto ActBossChar_Core_Hit = reinterpret_cast<void(*)(NPCHAR*)>(0x474340);
const auto ActBossChar_Core = reinterpret_cast<void(*)(void)>(0x474400);
// Undead Core boss
const auto ActBossChar_Undead = reinterpret_cast<void(*)(void)>(0x4753D0);
const auto ActBossCharA_Head = reinterpret_cast<void(*)(NPCHAR*)>(0x476790);
const auto ActBossCharA_Tail = reinterpret_cast<void(*)(NPCHAR*)>(0x4769A0);
const auto ActBossCharA_Face = reinterpret_cast<void(*)(NPCHAR*)>(0x476B90);
const auto ActBossCharA_Mini = reinterpret_cast<void(*)(NPCHAR*)>(0x476E50);
const auto ActBossCharA_Hit = reinterpret_cast<void(*)(NPCHAR*)>(0x477230);
// Ballos boss
const auto ActBossChar_Ballos = reinterpret_cast<void(*)(void)>(0x4772F0);
const auto ActBossChar_Eye = reinterpret_cast<void(*)(NPCHAR*)>(0x478AA0);
const auto ActBossChar_Body = reinterpret_cast<void(*)(NPCHAR*)>(0x478F20);
const auto ActBossChar_HITAI = reinterpret_cast<void(*)(NPCHAR*)>(0x478FE0);
const auto ActBossChar_HARA = reinterpret_cast<void(*)(NPCHAR*)>(0x479010);
// Balfrog boss
const auto ActBossChar_Frog = reinterpret_cast<void(*)(void)>(0x479030);
const auto ActBossChar02_01 = reinterpret_cast<void(*)(void)>(0x47A6A0);
const auto ActBossChar02_02 = reinterpret_cast<void(*)(void)>(0x47A800);
// Ironhead boss
const auto ActBossChar_Ironhead = reinterpret_cast<void(*)(void)>(0x47A8A0);
// Boss Life functions
const auto InitBossLife = reinterpret_cast<void(*)(void)>(0x47B450);
const auto StartBossLife = reinterpret_cast<BOOL(*)(int)>(0x47B460);
const auto StartBossLife2 = reinterpret_cast<BOOL(*)(void)>(0x47B500);
const auto PutBossLife = reinterpret_cast<void(*)(void)>(0x47B540);
// Omega boss
const auto ActBossChar_Omega = reinterpret_cast<void(*)(void)>(0x47B6F0);
const auto ActBoss01_12 = reinterpret_cast<void(*)(void)>(0x47C380);
const auto ActBoss01_34 = reinterpret_cast<void(*)(void)>(0x47C4E0);
const auto ActBoss01_5 = reinterpret_cast<void(*)(void)>(0x47C7A0);
// Heavy Press boss
const auto ActBossChar_Press = reinterpret_cast<void(*)(void)>(0x47C820);
// The Sisters boss
const auto ActBossChar_Twin = reinterpret_cast<void(*)(void)>(0x47D170);
const auto ActBossCharT_DragonBody = reinterpret_cast<void(*)(NPCHAR*)>(0x47DAA0);
const auto ActBossCharT_DragonHead = reinterpret_cast<void(*)(NPCHAR*)>(0x47DF10);
// Monster X boss
const auto ActBossChar_MonstX = reinterpret_cast<void(*)(void)>(0x47E6F0);
const auto ActBossChar03_01 = reinterpret_cast<void(*)(NPCHAR*)>(0x47F710);
const auto ActBossChar03_02 = reinterpret_cast<void(*)(NPCHAR*)>(0x480090);
const auto ActBossChar03_03 = reinterpret_cast<void(*)(NPCHAR*)>(0x4802A0);
const auto ActBossChar03_04 = reinterpret_cast<void(*)(NPCHAR*)>(0x480550);
const auto ActBossChar03_face = reinterpret_cast<void(*)(NPCHAR*)>(0x4808C0);
// Freeware Functions -- periwinkle headers
const auto Freeware_memset = reinterpret_cast<void* (*)(void*, int, size_t)>(0x480D30);
const auto Freeware_fclose = reinterpret_cast<int(*)(FILE*)>(0x480E1B);
const auto Freeware_fread = reinterpret_cast<size_t(*)(void*, size_t, size_t, FILE*)>(0x480F55);
const auto Freeware_fopen = reinterpret_cast<FILE * (*)(const char*, const char*)>(0x480FFD);
const auto Freeware_sprintf = reinterpret_cast<int(*)(char*, const char*, ...)>(0x481010);
const auto Freeware_strcmp = reinterpret_cast<int(*)(const char*, const char*)>(0x481070);
const auto Freeware_strcpy = reinterpret_cast<char* (*)(char*, const char*)>(0x481100);
const auto Freeware_strcat = reinterpret_cast<char* (*)(char*, const char*)>(0x481110);
const auto Freeware_strlen = reinterpret_cast<size_t(*)(const char*)>(0x481200);
const auto Freeware_free = reinterpret_cast<void(*)(void*)>(0x48128B);
const auto Freeware_malloc = reinterpret_cast<void* (*)(size_t)>(0x4813A3);
const auto Freeware_memcpy = reinterpret_cast<void* (*)(void*, const void*, size_t)>(0x4813C0);
const auto Freeware_srand = reinterpret_cast<void(*)(unsigned)>(0x4816FD);
const auto Freeware_rand = reinterpret_cast<int(*)(void)>(0x48170A);
const auto Freeware_memcmp = reinterpret_cast<int(*)(const void*, const void*, size_t)>(0x481730);
const auto Freeware_sscanf = reinterpret_cast<int(*)(const char*, const char*, ...)>(0x4817E8);
const auto Freeware_fprintf = reinterpret_cast<int(*)(FILE*, const char*, ...)>(0x48181C);
const auto Freeware_fwrite = reinterpret_cast<int(*)(void*, size_t, size_t, FILE*)>(0x481981);
const auto Freeware_fseek = reinterpret_cast<int(*)(FILE*, int, int)>(0x481A5C);