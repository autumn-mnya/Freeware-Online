#pragma once

#include <ddraw.h>
#include <dinput.h>
#include <dsound.h>
#include "Windows.h"

extern const char* gameIp;
extern const char* gamePort;
extern int mim_compatibility;
extern int show_player_names;
extern bool hide_me_on_map;
extern bool im_being_held;
extern bool my_shooting;
extern int my_soft_rensha;

// <MIM Compatibility
#define CSM_MIM_unobstructive (*(unsigned int*)0x49E184)
#define CSM_MIM_tsc_plus  (*(int*)0x49E09C)

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 240

// Max amounts of X

#define ARMS_MAX 8
#define ITEM_MAX 32
#define BOSS_MAX 20
#define BULLET_MAX 0x40
#define CARET_MAX 0x40
#define MAX_STRIP ((240 / 16) + 1)
#define FADE_WIDTH	(((WINDOW_WIDTH - 1) / 16) + 1)
#define FADE_HEIGHT	(((WINDOW_HEIGHT - 1) / 16) + 1)
#define PXM_BUFFER_SIZE 0x4B000
#define NPC_MAX 0x200
#define STAGE_MAX 8
#define SE_MAX 160
#define TSC_BUFFER_SIZE 0x5000
#define VALUEVIEW_MAX 0x10

// Input key detection

#define gKey (*(int*)0x49E210)
#define gKeyTrg (*(int*)0x49E214)

#define gKeyArms (*(int*)0x493618)
#define gKeyArmsRev (*(int*)0x49361C)
#define gKeyItem (*(int*)0x493620)
#define gKeyMap (*(int*)0x493624)
#define gKeyJump (*(int*)0x493628)
#define gKeyShot (*(int*)0x49362C)
#define gKeyLeft (*(int*)0x493630)
#define gKeyUp (*(int*)0x493634)
#define gKeyRight (*(int*)0x493638)
#define gKeyDown (*(int*)0x49363C)
#define KEY_ALT_LEFT 0x10000
#define KEY_ALT_DOWN 0x20000
#define KEY_ALT_RIGHT 0x40000
#define KEY_ALT_UP 0x180000
#define KEY_L 0x80000
#define KEY_PLUS 0x100000
#define KEY_ESCAPE 0x8000
// Freeware Online keys
#define KEY_TAB 0x200000
#define KEY_T 0x400000
#define KEY_ENTER 0x800000

// Variables
#define ghWnd (*(HWND*)0x49E458) //ghWnd
#define mag (*(int*)0x48F914) // mag
#define grcGame (*(RECT*)0x48F91C) // grcGame
#define grcFull (*(RECT*)0x48F92C) // grcFull
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
#define gMusicNo (*(int*)0x4A57F4) // gMusicNo
#define gOldPos (*(int*)0x4A57F8) // gOldPos (previous position in music)
#define gOldNo (*(int*)0x4A57FC) // gOldNo (previous music)
#define g_GameFlags (*(int*)0x49E1E8)
#define gCounter (*(int*)0x49E1EC)
static int* gun_empty = (int*)0x4A554C;
static int* gNumberTextScript = (int*)0x4A5B34;
#define gWaterY (*(int*)0x499C90)
#define bContinue (*(BOOL*)0x49E1E4)

// <MIM Compatibility
#define CSM_MIM_unobstructive (*(unsigned int*)0x49E184)
#define CSM_MIM_tsc_plus  (*(int*)0x49E09C)

// String array
#define gMusicTable (*(char*(*)[42])0x4981E8)

struct OTHER_RECT	// The original name for this struct is unknown
{
	int front;
	int top;
	int back;
	int bottom;
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

// Enums
typedef enum SurfaceID
{
	SURFACE_ID_TITLE = 0,
	SURFACE_ID_PIXEL = 1,
	SURFACE_ID_LEVEL_TILESET = 2,
	SURFACE_ID_USERNAME = 3,
	SURFACE_ID_SKIN = 4,
	SURFACE_ID_CHAT = 5,
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
	SURFACE_ID_NES = 38,
	SURFACE_ID_UI = 39,
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
	char magic_string[0x20];
	char font_name[0x40];
	unsigned long directional_keys;
	unsigned long jump_shoot_keys;
	unsigned long jump_shoot_keys_2;
	unsigned long window_size;
	unsigned long gamepad_enabled;
	unsigned long gamepad_buttons[8];
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

enum FlashMode
{
	FLASH_MODE_EXPLOSION = 1,
	FLASH_MODE_FLASH = 2
};

static struct
{
	FlashMode mode;
	int act_no;
	BOOL flag;
	int cnt;
	int width;
	int x;
	int y;
	RECT rect1;
	RECT rect2;
} flash;

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
	unsigned char atrb[0x100];
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

// Sound

enum SoundMode
{
	SOUND_MODE_PLAY_LOOP = -1,
	SOUND_MODE_STOP = 0,
	SOUND_MODE_PLAY = 1
};

// Star

static struct
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
} star[3];

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

static ARMS* gArmsData = (ARMS*)0x499BC8;
static ARMS_LEVEL* gArmsLevelTable = (ARMS_LEVEL*)0x493660;
static BULLET* gBul = (BULLET*)0x499C98;
static BULLET_TABLE* gBulTbl = (BULLET_TABLE*)0x48F044;
static NPCHAR* gBoss = (NPCHAR*)0x4BBA58;
static CARET* gCrt = (CARET*)0x49BCA8;
static CARET_TABLE* gCaretTable = (CARET_TABLE*)0x48F830;
static ITEM* gItemData = (ITEM*)0x499B40;
static MYCHAR* gMC = (MYCHAR*)0x49E638;
static MAP_DATA* gMap = (MAP_DATA*)0x49E480;
static NPCHAR* gNPC = (NPCHAR*)0x4A6220;
static PERMIT_STAGE* gPermitStage = (PERMIT_STAGE*)0x4A5500;
static STAGE_TABLE* gTMT = (STAGE_TABLE*)(*(unsigned*)0x420c2f); // This is a pointer to where it gets used, instead of the actual table, so that it has compatibility with mods.
static TEXT_SCRIPT* gTS = (TEXT_SCRIPT*)0x4A59D0;
static VALUEVIEW* gVV = (VALUEVIEW*)0x4A5F98;
static signed char* gMapping = (signed char*)0x49E5B8;
static unsigned char* gFlagNPC = (unsigned char*)0x49DDA0;
#define gCurlyShoot_wait (*(int*)0x4BBA2C)


///////////////
// Functions //
///////////////


//ArmsItem functions
static void (* const ClearArmsData)(void) = (void(*)(void))0x401000;
static void (* const ClearItemData)(void) = (void(*)(void))0x401030;
static BOOL(* const AddArmsData)(long code, long max_num) = (BOOL(*)(long, long))0x401050;
static BOOL(* const SubArmsData)(long code) = (BOOL(*)(long))0x401160;
static BOOL(* const TradeArms)(long code, long code2, long max_num) = (BOOL(*)(long, long, long))0x401220;
static BOOL(* const AddItemData)(long code) = (BOOL(*)(long))0x4012D0;
static BOOL(* const SubItemData)(long code) = (BOOL(*)(long))0x401330;
static void (* const MoveCampCursor)(void) = (void(*)(void))0x4013C0;
static void (* const PutCampObject)(void) = (void(*)(void))0x4016F0;
static void (* const CampLoop)(void) = (void(*)(void))0x401D10;
static BOOL(* const CheckItem)(long a) = (BOOL(*)(long))0x401F20;
static BOOL(* const CheckArms)(long a) = (BOOL(*)(long))0x401F60;
static BOOL(* const UseArmsEnergy)(long num) = (BOOL(*)(long))0x401FA0;
static BOOL(* const ChargeArmsEnergy)(long num) = (BOOL(*)(long))0x402020;
static void (* const FullArmsEnergy)(void) = (void(*)(void))0x402090;
static int (* const RotationArms)(void) = (int(*)(void))0x4020E0;
static int (* const RotationArmsRev)(void) = (int(*)(void))0x402190;
static void (* const ChangeToFirstArms)(void) = (void(*)(void))0x402240;
// Background functions
static BOOL(* const InitBack)(const char* background_filename, int background_type) = (BOOL(*)(const char*, int))0x402270;
static void (* const ActBack)(void) = (void (*)(void))0x402370;
static void (* const PutBack)(int x_pos, int y_pos) = (void(*)(int, int))0x4023D0;
static void (* const PutFront)(int x_pos, int y_pos) = (void(*)(int, int))0x402830;
// Bullet Collision functions
static int (* const JudgeHitBulletBlock)(int x, int y, BULLET* bul) = (int(*)(int, int, BULLET*))0x4029B0;
static int (* const JudgeHitBulletBlock2)(int x, int y, unsigned char* atrb, BULLET* bul) = (int(*)(int, int, unsigned char*, BULLET*))0x402B30;
static int (* const JudgeHitBulletTriangleA)(int x, int y, BULLET* bul) = (int(*)(int, int, BULLET*))0x402FC0;
static int (* const JudgeHitBulletTriangleB)(int x, int y, BULLET* bul) = (int(*)(int, int, BULLET*))0x4030B0;
static int (* const JudgeHitBulletTriangleC)(int x, int y, BULLET* bul) = (int(*)(int, int, BULLET*))0x4031A0;
static int (* const JudgeHitBulletTriangleD)(int x, int y, BULLET* bul) = (int(*)(int, int, BULLET*))0x403290;
static int (* const JudgeHitBulletTriangleE)(int x, int y, BULLET* bul) = (int(*)(int, int, BULLET*))0x403380;
static int (* const JudgeHitBulletTriangleF)(int x, int y, BULLET* bul) = (int(*)(int, int, BULLET*))0x403470;
static int (* const JudgeHitBulletTriangleG)(int x, int y, BULLET* bul) = (int(*)(int, int, BULLET*))0x403560;
static int (* const JudgeHitBulletTriangleH)(int x, int y, BULLET* bul) = (int(*)(int, int, BULLET*))0x403650;
static void (* const HitBulletMap)(void) = (void(*)(void))0x403740;
// Bullet functions
static void (* const InitBullet)(void) = (void(*)(void))0x403C00;
static int (* const CountArmsBullet)(int arms_code) = (int(*)(int))0x403C40;
static int (* const CountBulletNum)(int bullet_code) = (int(*)(int))0x403CB0;
static void (* const DeleteBullet)(int code) = (void(*)(int))0x403D10;
static void (* const ClearBullet)(void) = (void(*)(void))0x403D80;
static void (* const PutBullet)(int fx, int fy) = (void(*)(int, int))0x403DC0;
static void (* const SetBullet)(int no, int x, int y, int dir) = (void(*)(int, int, int, int))0x403F80;
static void (* const ActBullet_Frontia1)(BULLET* bul) = (void(*)(BULLET*))0x404160;
static void (* const ActBullet_Frontia2)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x4043F0;
static void (* const ActBullet_PoleStar)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x4047B0;
static void (* const ActBullet_FireBall)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x404B30;
static void (* const ActBullet_MachineGun)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x405120;
static void (* const ActBullet_Missile)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x4055A0;
static void (* const ActBullet_Bom)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x405D80;
static void (* const ActBullet_Bubblin1)(BULLET* bul) = (void(*)(BULLET*))0x405F30;
static void (* const ActBullet_Bubblin2)(BULLET* bul) = (void(*)(BULLET*))0x406190;
static void (* const ActBullet_Bubblin3)(BULLET* bul) = (void(*)(BULLET*))0x4064D0;
static void (* const ActBullet_Spine)(BULLET* bul) = (void(*)(BULLET*))0x4068B0;
static void (* const ActBullet_Sword1)(BULLET* bul) = (void(*)(BULLET*))0x406BB0;
static void (* const ActBullet_Sword2)(BULLET* bul) = (void(*)(BULLET*))0x406E60;
static void (* const ActBullet_Sword3)(BULLET* bul) = (void(*)(BULLET*))0x407110;
static void (* const ActBullet_Edge)(BULLET* bul) = (void(*)(BULLET*))0x4075E0;
static void (* const ActBullet_Drop)(BULLET* bul) = (void(*)(BULLET*))0x4078A0;
static void (* const ActBullet_SuperMissile)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x407910;
static void (* const ActBullet_SuperBom)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x408080;
static void (* const ActBullet_Nemesis)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x408230;
static void (* const ActBullet_Spur)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x408710;
static void (* const ActBullet_SpurTail)(BULLET* bul, int level) = (void(*)(BULLET*, int))0x408AE0;
static void (* const ActBullet_EnemyClear)(BULLET* bul) = (void(*)(BULLET*))0x408F40;
static void (* const ActBullet_Star)(BULLET* bul) = (void(*)(BULLET*))0x408F90;
static void (* const ActBullet)(void) = (void(*)(void))0x408FC0;
static BOOL(* const IsSomeActiveBullet)(void) = (BOOL(*)(void))0x4095C0;
// Caret functions
static void (* const InitCaret)(void) = (void(*)(void))0x409650;
static void (* const ActCaret00)(CARET* crt) = (void(*)(CARET*))0x409670;
static void (* const ActCaret01)(CARET* crt) = (void(*)(CARET*))0x409680;
static void (* const ActCaret02)(CARET* crt) = (void(*)(CARET*))0x409880;
static void (* const ActCaret03)(CARET* crt) = (void(*)(CARET*))0x409B80;
static void (* const ActCaret04)(CARET* crt) = (void(*)(CARET*))0x409C70;
static void (* const ActCaret05)(CARET* crt) = (void(*)(CARET*))0x409E00;
static void (* const ActCaret07)(CARET* crt) = (void(*)(CARET*))0x409F60;
static void (* const ActCaret08)(CARET* crt) = (void(*)(CARET*))0x40A120;
static void (* const ActCaret09)(CARET* crt) = (void(*)(CARET*))0x40A1B0;
static void (* const ActCaret10)(CARET* crt) = (void(*)(CARET*))0x40A280;
static void (* const ActCaret11)(CARET* crt) = (void(*)(CARET*))0x40A3F0;
static void (* const ActCaret12)(CARET* crt) = (void(*)(CARET*))0x40A5A0;
static void (* const ActCaret13)(CARET* crt) = (void(*)(CARET*))0x40A650;
static void (* const ActCaret14)(CARET* crt) = (void(*)(CARET*))0x40A7E0;
static void (* const ActCaret15)(CARET* crt) = (void(*)(CARET*))0x40A8F0;
static void (* const ActCaret16)(CARET* crt) = (void(*)(CARET*))0x40A9E0;
static void (* const ActCaret17)(CARET* crt) = (void(*)(CARET*))0x40AAA0;
static void (* const ActCaret)(void) = (void(*)(void))0x40AB50;
static void (* const PutCaret)(int fx, int fy) = (void(*)(int, int))0x40ABC0;
static void (* const SetCaret)(int x, int y, int code, int dir) = (void(*)(int, int, int, int))0x40AC90;
static BOOL(* const LoadConfigData)(ConfigData* config_memory) = (BOOL(*)(ConfigData*))0x40AD60;
static void(* const DefaultConfigData)(ConfigData* config_memory) = (void(*)(ConfigData*))0x40AE30;
// Dialog functions (not implemented into cave_story.h yet)

// VersionDialog - 0x40AEC0

// DebugMuteDialog - 0x40AFC0

// DebugSaveDialog - 0x40B1D0

// QuitDialog - 0x40B290

// Draw functions
static void(* const SetClientOffset)(int width, int height) = (void(*)(int, int))0x40B320;
static BOOL(* const Flip_SystemTask)(HWND hWnd) = (BOOL(*)(HWND))0x40B340;
static BOOL(* const StartDirectDraw)(HWND hWnd, int lMagnification, int lColourDepth) = (BOOL(*)(HWND hWnd, int, int))0x40B340;
static BOOL(* const EndDirectDraw)(HWND hWnd) = (BOOL(*)(HWND))0x40B6C0;
static void (* const ReleaseSurface)(int s) = (void(*)(int))0x40B7A0;
static BOOL(* const MakeSurface_Resource)(const char* name, SurfaceID surf_no) = (BOOL(*)(const char*, SurfaceID))0x40B800;
static BOOL(* const MakeSurface_File)(const char* name, int surf_no) = (BOOL(*)(const char*, int))0x40BAC0;
static BOOL(* const ReloadBitmap_Resource)(const char* name, SurfaceID surf_no) = (BOOL(*)(const char*, SurfaceID))0x40BE10;
static BOOL(* const ReloadBitmap_File)(const char* name, int surf_no) = (BOOL(*)(const char*, int))0x40BFD0;
static BOOL(* const MakeSurface_Generic)(int bxsize, int bysize, int surf_no, BOOL bSystem) = (BOOL(*)(int, int, int, BOOL))0x40C1D0;
static void (* const BackupSurface)(SurfaceID surf_no, const RECT* rect) = (void(*)(SurfaceID, const RECT*))0x40C320;
static void (* const PutBitmap3)(const RECT*, int, int, const RECT*, SurfaceID) = (void(*)(const RECT*, int, int, const RECT*, SurfaceID))0x40C3C0;
static void (* const PutBitmap4)(const RECT*, int, int, const RECT*, SurfaceID) = (void(*)(const RECT*, int, int, const RECT*, SurfaceID))0x40C5B0;
static void (* const Surface2Surface)(int x, int y, const RECT* rect, SurfaceID to, SurfaceID from) = (void(*)(int, int, const RECT*, SurfaceID, SurfaceID))0x40C7A0;
static unsigned long (* const GetCortBoxColor)(COLORREF col) = (unsigned long(*)(COLORREF))0x40C8B0;
static void (* const CortBox)(RECT* dst_rect, int colour) = (void(*)(RECT*, int))0x40C9E0;
static void (* const CortBox2)(RECT* dst_rect, int colour, SurfaceID surf_no) = (void(*)(RECT*, int, SurfaceID))0x40CA80;
static BOOL(* const out)(char surface_identifier) = (BOOL(*)(char))0x40CB30;
static int (* const RestoreSurfaces)(void) = (int(*)(void))0x40CB60;
static void(* const InitTextObject)(const char* name) = (void(*)(const char*))0x40CD50;
static void (* const PutText)(int x, int y, const char* text, unsigned int colour) = (void(*)(int, int, const char*, unsigned int))0x40CE00;
static void (* const PutText2)(int x, int y, const char* text, unsigned int colour, SurfaceID) = (void(*)(int, int, const char*, unsigned int, SurfaceID))0x40CEB0;
static void (* const EndTextObject)(void) = (void(*)(void))0x40CF70;
// Ending functions
static void (* const ActionStripper)(void) = (void(*)(void))0x40CF90;
static void (* const PutStripper)(void) = (void(*)(void))0x40D010;
static void (* const SetStripper)(int x, int y, const char* text, int cast) = (void(*)(int, int, const char*, int))0x40D150;
static void (* const RestoreStripper)(void) = (void(*)(void))0x40D240;
static void (* const ActionIllust)(void) = (void(*)(void))0x40D2D0;
static void (* const PutIllust)(void) = (void(*)(void))0x40D350;
static void (* const ReloadIllust)(int a) = (void(*)(int))0x40D3A0;
static void (* const InitCreditScript)(void) = (void(*)(void))0x40D3E0;
static void (* const ReleaseCreditScript)(void) = (void(*)(void))0x40D410;
static BOOL(* const StartCreditScript)(void) = (BOOL(*)(void))0x40D440;
static void (* const ActionCredit)(void) = (void(*)(void))0x40D5C0;
static void (* const ActionCredit_Read)(void) = (void(*)(void))0x40D620;
static int (* const GetScriptNumber)(const char* text) = (int(*)(const char*))0x40DB00;
static void (* const SetCreditIllust)(int a) = (void(*)(int))0x40DB40;
static void (* const CutCreditIllust)(void) = (void(*)(void))0x40DB60;
static int (* const Scene_DownIsland)(HWND hWnd, int mode) = (int(*)(HWND, int))0x40DB70;
// Escape menu
static int (* const Call_Escape)(HWND hWnd) = (int(*)(HWND))0x40DD70;
// Fade functions
static void (* const InitFade)(void) = (void(*)(void))0x40DE60;
static void (* const SetFadeMask)(void) = (void(*)(void))0x40DE90;
static void (* const ClearFade)(void) = (void(*)(void))0x40DEA0;
static void (* const StartFadeOut)(signed char dir) = (void(*)(signed char))0x40DEC0;
static void (* const StartFadeIn)(signed char dir) = (void(*)(signed char))0x40DF50;
static void (* const ProcFade)(void) = (void(*)(void))0x40DFE0;
static void (* const PutFade)(void) = (void(*)(void))0x40E770;
static BOOL(* const GetFadeActive)(void) = (BOOL(*)(void))0x40E830;
// Flag functions
static void (* const InitFlags)(void) = (void(*)(void))0x40E850;
static void (* const InitSkipFlags)(void) = (void(*)(void))0x40E870;
static void (* const SetNPCFlag)(long a) = (void(*)(long))0x40E890;
static void (* const CutNPCFlag)(long a) = (void(*)(long))0x40E8E0;
static BOOL(* const GetNPCFlag)(long a) = (BOOL(*)(long))0x40E930;
static void (* const SetSkipFlag)(long a) = (void(*)(long))0x40E970;
static void (* const CutSkipFlag)(long a) = (void(*)(long))0x40E9C0;
static BOOL(* const GetSkipFlag)(long a) = (BOOL(*)(long))0x40EA10;
// Flash functions
static void (* const InitFlash)(void) = (void(*)(void))0x40EA50;
static void (* const SetFlash)(int x, int y, FlashMode mode) = (void(*)(int, int, FlashMode))0x40EA70;
static void (* const ActFlash_Explosion)(int flx, int fly) = (void(*)(int, int))0x40EAC0;
static void (* const ActFlash_Flash)(void) = (void(*)(void))0x40ED20;
static void (* const ActFlash)(int flx, int fly) = (void(*)(int, int))0x40EDE0;
static void (* const PutFlash)(void) = (void(*)(void))0x40EE20;
static void (* const ResetFlash)(void) = (void(*)(void))0x40EE60;
// Frame / camera functions
static void (* const MoveFrame3)(void) = (void(*)(void))0x40EE70;
static void (* const GetFramePosition)(int* fx, int* fy) = (void(*)(int*, int*))0x40F020;
static void (* const SetFramePosition)(int fx, int fy) = (void(*)(int, int))0x40F040;
static void (* const SetFrameMyChar)(void) = (void(*)(void))0x40F130;
static void (* const SetFrameTargetMyChar)(int wait) = (void(*)(int))0x40F220;
static void (* const SetFrameTargetNpChar)(int event, int wait) = (void(*)(int, int))0x40F250;
static void (* const SetFrameTargetBoss)(int no, int wait) = (void(*)(int, int))0x40F2D0;
static void (* const SetQuake)(int time) = (void(*)(int))0x40F310;
static void (* const SetQuake2)(int time) = (void(*)(int))0x40F320;
static void (* const ResetQuake)(void) = (void(*)(void))0x40F330;
// Game functions
static int (* const Random)(int min, int max) = (int(*)(int, int))0x40F350;
static void (* const PutNumber4)(int x, int y, int, int) = (void(*)(int, int, int, int))0x40F380;
static BOOL(* const Game)(HWND hWnd) = (BOOL(*)(HWND))0x40F5F0;
static int (* const ModeOpening)(HWND hWnd) = (int(*)(HWND))0x40F730;
static int (* const ModeTitle)(HWND hWnd) = (int(*)(HWND))0x40F9B0;
static int (* const ModeAction)(HWND hWnd) = (int(*)(HWND))0x410400;
// Generic functions
static void (* const GetCompileDate)(int* year, int* month, int* day) = (void(*)(int*, int*, int*))0x4108B0;
static BOOL(* const GetCompileVersion)(int* v1, int* v2, int* v3, int* v4) = (BOOL(*)(int*, int*, int*, int*))0x410990;
static BOOL(* const OpenSoundVolume)(HWND hWnd) = (BOOL(*)(HWND))0x410AB0;
static void (* const DeleteLog)(void) = (void(*)(void))0x410BC0;
static BOOL(* const WriteLog)(const char* string, int value1, int value2, int value3) = (BOOL(*)(const char*, int, int, int))0x410C10;
static int (* const GetDateLimit)(SYSTEMTIME* system_time_low, SYSTEMTIME* system_time_high) = (int(*)(SYSTEMTIME*, SYSTEMTIME*))0x410CA0;
static BOOL(* const IsKeyFile)(const char* name) = (BOOL(*)(const char*))0x410D10;
static long(* const GetFileSizeLong)(const char* path) = (long(*)(const char*))0x410D80;
static BOOL(* const ErrorLog)(const char* string, int value) = (BOOL(*)(const char*, int))0x410DE0;
static BOOL(* const IsShiftJIS)(unsigned char c) = (BOOL(*)(unsigned char))0x410E90;
static BOOL(* const CenteringWindowByParent)(HWND hWnd) = (BOOL(*)(HWND))0x410EE0;
static BOOL(* const LoadWindowRect)(HWND hWnd, const char* filename, BOOL unknown) = (BOOL(*)(HWND, const char*, BOOL))0x410FE0;
static BOOL(* const SaveWindowRect)(HWND hWnd, const char* filename) = (BOOL(*)(HWND, const char*))0x4111F0;
static BOOL(* const IsEnableBitmap)(const char* path) = (BOOL(*)(const char*))0x4112E0;
// GenericLoad functions
static BOOL(* const LoadGenericData)(void) = (BOOL(*)(void))0x411390;
// Input functions
static void(* const ReleaseDirectInput)(void) = (void(*)(void))0x411E10;
static BOOL(* const ActivateDirectInput)(BOOL aquire) = (BOOL(*)(BOOL))0x411E60;
static BOOL(* const InitDirectInput)(HINSTANCE hinst, HWND hWnd) = (BOOL(*)(HINSTANCE, HWND))0x411EB0;
static BOOL(* const FindAndOpenDirectInputDevice)(HWND hWnd) = (BOOL(*)(HWND))0x411EF0;
static BOOL(* const EnumDevices_Callback)(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef) = (BOOL(*)(LPCDIDEVICEINSTANCE, LPVOID))0x411FC0;
static BOOL(* const GetJoystickStatus)(DIRECTINPUTSTATUS* status) = (BOOL(*)(DIRECTINPUTSTATUS*))0x4120F0;
static BOOL(* const ResetJoystickStatus)(void) = (BOOL(*)(void))0x412250;
// KeyControl functions
static void (* const GetTrg)(void) = (void(*)(void))0x4122E0;
// Main functions
static void (* const SetWindowName)(HWND hWnd) = (void(*)(HWND))0x412320;
static void (* const PutFramePerSecound)(void) = (void(*)(void))0x412370;
static unsigned long (* const CountFramePerSecound)(void) = (unsigned long(*)(void))0x4123A0;
// This function is called CS_WinMain because we can't call it WinMain
static int (* const CS_WinMain)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) = (int(*)(HINSTANCE, HINSTANCE, LPSTR, int))0x412420;
static void (* const InactiveWindow)(void) = (void(*)(void))0x412BC0;
static void (* const ActiveWindow)(void) = (void(*)(void))0x412BF0;
static BOOL(* const DragAndDropHandler)(HWND hWnd, WPARAM wParam) = (BOOL(*)(HWND, WPARAM))0x412C30;
static LRESULT(* const WindowProcedure)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) = (LRESULT(*)(HWND, UINT, WPARAM, LPARAM))0x412CA0;
static BOOL(* const SystemTask)(void) = (BOOL(*)(void))0x413570;
static void (* const JoystickProc)(void) = (void(*)(void))0x4135E0;
// Map functions
static BOOL(* const InitMapData2)(void) = (BOOL(*)(void))0x413750;
static BOOL(* const LoadMapData2)(const char* path_map) = (BOOL(*)(const char*))0x413770;
static BOOL(* const LoadAttributeData)(const char* path_atrb) = (BOOL(*)(const char*))0x4138A0;
static void (* const EndMapData)(void) = (void(*)(void))0x413930;
static void (* const ReleasePartsImage)(void) = (void(*)(void))0x413950;
static void (* const GetMapData)(unsigned char** data, short* mw, short* ml) = (void(*)(unsigned char**, short*, short*))0x413960;
static unsigned char (* const GetAttribute)(int x, int y) = (unsigned char(*)(int, int))0x4139A0;
static void (* const DeleteMapParts)(int x, int y) = (void(*)(int, int))0x413A00;
static void (* const ShiftMapParts)(int x, int y) = (void(*)(int, int))0x413A20;
static BOOL(* const ChangeMapParts)(int x, int y, unsigned char no) = (BOOL(*)(int, int, unsigned char))0x413A60;
static void (* const PutStage_Back)(int fx, int fy) = (void(*)(int, int))0x413AF0;
static void (* const PutStage_Front)(int fx, int fy) = (void(*)(int, int))0x413C60;
static void (* const PutMapDataVector)(int fx, int fy) = (void(*)(int, int))0x413E40;
// Map name functions
static void (* const ReadyMapName)(const char* str) = (void(*)(const char*))0x4140F0;
static void (* const PutMapName)(BOOL bMini) = (void(*)(BOOL))0x414250;
static void (* const StartMapName)(void) = (void(*)(void))0x414310;
static void (* const RestoreMapName)(void) = (void(*)(void))0x414330;
// MiniMap / Map System functions
static void (* const WriteMiniMapLine)(int line) = (void(*)(int))0x4143C0;
static int (* const MiniMapLoop)(void) = (int(*)(void))0x414640;
static BOOL(* const IsMapping)(void) = (BOOL(*)(void))0x414B00;
static void (* const StartMapping)(void) = (void(*)(void))0x414B20;
static void (* const SetMapping)(int a) = (void(*)(int))0x414B40;
// MyChar functions
static void (* const InitMyChar)(void) = (void(*)(void))0x414B50;
static void (* const AnimationMyChar)(BOOL bKey) = (void(*)(BOOL))0x414BF0;
static void (* const ShowMyChar)(BOOL bShow) = (void(*)(BOOL))0x415220;
static void (* const PutMyChar)(int camera_x, int camera_y) = (void(*)(int, int))0x415250;
static void (* const ActMyChar_Normal)(BOOL bKey) = (void(*)(BOOL))0x4156C0;
static void (* const ActMyChar_Stream)(BOOL bKey) = (void(*)(BOOL))0x416470;
static void (* const ActMyChar)(BOOL bKey) = (void(*)(BOOL))0x4168C0;
static void (* const AirProcess)(void) = (void(*)(void))0x416990;
static void (* const GetMyCharPosition)(int* x, int* y) = (void(*)(int*, int*))0x416AA0;
static void (* const SetMyCharPosition)(int x, int y) = (void(*)(int, int))0x416AC0;
static void (* const MoveMyChar)(int x, int y) = (void(*)(int, int))0x416B30;
static void (* const ZeroMyCharXMove)(void) = (void(*)(void))0x416B50;
static int (* const GetUnitMyChar)(void) = (int(*)(void))0x416B60;
static void (* const SetMyCharDirect)(unsigned char dir) = (void(*)(unsigned char))0x416B70;
static void (* const ChangeMyUnit)(unsigned char a) = (void(*)(unsigned char))0x416C40;
static void (* const PitMyChar)(void) = (void(*)(void))0x416C50;
static void (* const EquipItem)(int flag, BOOL b) = (void(*)(int, BOOL))0x416C70;
static void (* const ResetCheck)(void) = (void(*)(void))0x416CA0;
static void (* const SetNoise)(int no, int freq) = (void(*)(int, int))0x416CC0;
static void (* const CutNoise)(void) = (void(*)(void))0x416D40;
static void (* const ResetNoise)(void) = (void(*)(void))0x416D80;
static void (* const SleepNoise)(void) = (void(*)(void))0x416DF0;
// MycHit / MyChar collision functions
static void (* const ResetMyCharFlag)(void) = (void(*)(void))0x416E20;
static int (* const JudgeHitMyCharBlock)(int x, int y) = (int(*)(int, int))0x416E30;
static void (* const PutlittleStar)(void) = (void(*)(void))0x417160;
static int (* const JudgeHitMyCharTriangleA)(int x, int y) = (int(*)(int, int))0x4171D0;
static int (* const JudgeHitMyCharTriangleB)(int x, int y) = (int(*)(int, int))0x4172E0;
static int (* const JudgeHitMyCharTriangleC)(int x, int y) = (int(*)(int, int))0x4173F0;
static int (* const JudgeHitMyCharTriangleD)(int x, int y) = (int(*)(int, int))0x417500;
static int (* const JudgeHitMyCharTriangleE)(int x, int y) = (int(*)(int, int))0x417610;
static int (* const JudgeHitMyCharTriangleF)(int x, int y) = (int(*)(int, int))0x417720;
static int (* const JudgeHitMyCharTriangleG)(int x, int y) = (int(*)(int, int))0x417830;
static int (* const JudgeHitMyCharTriangleH)(int x, int y) = (int(*)(int, int))0x417940;
static int (* const JudgeHitMyCharWater)(int x, int y) = (int(*)(int, int))0x417A50;
static int (* const JudgeHitMyCharDamage)(int x, int y) = (int(*)(int, int))0x417AE0;
static int (* const JudgeHitMyCharDamageW)(int x, int y) = (int(*)(int, int))0x417B70;
static int (* const JudgeHitMyCharVectLeft)(int x, int y) = (int(*)(int, int))0x417C00;
static int (* const JudgeHitMyCharVectUp)(int x, int y) = (int(*)(int, int))0x417C90;
static int (* const JudgeHitMyCharVectRight)(int x, int y) = (int(*)(int, int))0x417D20;
static int (* const JudgeHitMyCharVectDown)(int x, int y) = (int(*)(int, int))0x417DB0;
static void (* const HitMyCharMap)(void) = (void(*)(void))0x417E40;
static int (* const JudgeHitMyCharNPC)(NPCHAR* npc) = (int(*)(NPCHAR*))0x4187F0;
static unsigned char (* const JudgeHitMyCharNPC3)(NPCHAR* npc) = (unsigned char(*)(NPCHAR*))0x418B10;
static int (* const JudgeHitMyCharNPC4)(NPCHAR* npc) = (int(*)(NPCHAR*))0x418C20;
static void (* const HitMyCharNpChar)(void) = (void(*)(void))0x419030;
static void (* const HitMyCharBoss)(void) = (void(*)(void))0x417E40;
// MycParam functions
static void (* const AddExpMyChar)(int x) = (void(*)(int))0x4196F0;
static void (* const ZeroExpMyChar)(void) = (void(*)(void))0x419890;
static BOOL(* const IsExpMyChar)(void) = (BOOL(*)(void))0x4198C0;
static void (* const DamageMyChar)(int damage) = (void(*)(int))0x419910;
static void (* const ZeroArmsEnergy_All)(void) = (void(*)(void))0x419B50;
static void (* const AddBulletMyChar)(int no, int val) = (void(*)(int, int))0x419BA0;
static void (* const AddLifeMyChar)(int x) = (void(*)(int))0x419C60;
static void (* const AddMaxLifeMyChar)(int val) = (void(*)(int))0x419CB0;
static void (* const PutArmsEnergy)(BOOL flash) = (void(*)(BOOL))0x419D10;
static void (* const PutActiveArmsList)(void) = (void(*)(void))0x41A0B0;
static void (* const PutMyLife)(BOOL flash) = (void(*)(BOOL))0x41A1D0;
static void (* const PutMyAir)(int x, int y) = (void(*)(int, int))0x41A350;
static void (* const PutTimeCounter)(int x, int y) = (void(*)(int, int))0x41A430;
static BOOL(* const SaveTimeCounter)(void) = (BOOL(*)(void))0x41A5D0;
static int (* const LoadTimeCounter)(void) = (int(*)(void))0x41A7C0;
// Organya functions
static BOOL(* const MakeSoundObject8)(signed char* wavep, signed char track, signed char pipi) = (BOOL(*)(signed char*, signed char, signed char))0x41A8F0;
static void (* const ChangeOrganFrequency)(unsigned char key, signed char track, long a) = (void(*)(unsigned char, signed char, long))0x41ABA0;
static void (* const ChangeOrganPan)(unsigned char key, unsigned char pan, signed char track) = (void(*)(unsigned char, unsigned char, signed char))0x41AC70;
static void (* const ChangeOrganVolume)(int no, long volume, signed char track) = (void(*)(int, long, signed char))0x41AD20;
static void (* const PlayOrganObject)(unsigned char key, int mode, signed char track, long freq) = (void(*)(unsigned char, int, signed char, long))0x41ADC03;
static void (* const ReleaseOrganyaObject)(signed char track) = (void(*)(signed char))0x41B2A0;
static BOOL(* const InitWaveData100)(void) = (BOOL(*)(void))0x41B380;
static BOOL(* const MakeOrganyaWave)(signed char track, signed char wave_no, signed char pipi) = (BOOL(*)(signed char, signed char, signed char))0x41B3F0;
static void (* const ChangeDramFrequency)(unsigned char key, signed char track) = (void(*)(unsigned char, signed char))0x41B440;
static void (* const ChangeDramPan)(unsigned char pan, signed char track) = (void(*)(unsigned char, signed char))0x41B440;
static void (* const ChangeDramVolume)(long volume, signed char track) = (void(*)(long, signed char))0x41B4D0;
static void (* const PlayDramObject)(unsigned char key, int mode, signed char track) = (void(*)(unsigned char, int, signed char))0x41B510;

// These classes aren't implemented, as I, Kaitlyn, don't know how to implement them.
// OrgData::OrgData - 0x41B600

// OrgData::InitOrgData - 0x41B650

// OrgData::SetMusicInfo - 0x41B730

// OrgData::NoteAlloc - 0x41B890

// OrgData::ReleaseNote - 0x41BA70

// OrgData::InitMusicData - 0x41BAD0

// OrgData::GetMusicInfo - 0x41C0B0

// InitMMTimer - 0x41C180

// StartTimer - 0x41C1E0

// TimerProc - 0x41C230

// QuitMMTimer - 0x41C250

// OrgData::PlayData - 0x41C2B0

// OrgData::SetPlayerPointer - 0x41C630

static BOOL(* const StartOrganya)(LPDIRECTSOUND lpDS, const char* path_wave) = (BOOL(*)(LPDIRECTSOUND, const char*))0x41C6C0;
static void (* const LoadOrganya)(const char*) = (void(*)(const char*))0x41C6F0;
static void (* const SetOrganyaPosition)(int) = (void(*)(int))0x41C730;
static int (* const GetOrganyaPosition)(void) = (int(*)(void))0x41C770;
static void (* const PlayOrganyaMusic)(void) = (void(*)(void))0x41C790;
static void (* const ChangeOrganyaVolume)(int) = (void(*)(int))0x41C7C0;
static void (* const StopOrganyaMusic)(void) = (void(*)(void))0x41C7F0;
static void (* const SetOrganyaFadeout)(void) = (void(*)(void))0x41C880;
static void (* const EndOrganya)(void) = (void(*)(void))0x41C890;
// PixTone functions
static void (* const MakeWaveTables)(void) = (void(*)(void))0x41C8F0;
static BOOL(* const MakePixelWaveData)(const PIXTONEPARAMETER* ptp, unsigned char* pData) = (BOOL(*)(const PIXTONEPARAMETER*, unsigned char*))0x41CB10;
// Profile / Save data functions
static BOOL(* const IsProfile)(void) = (BOOL(*)(void))0x41CFC0;
static BOOL(* const SaveProfile)(const char* name) = (BOOL(*)(const char*))0x41D040;
static BOOL(* const LoadProfile)(const char* name) = (BOOL(*)(const char*))0x41D260;
static BOOL(* const InitializeGame)(HWND hWnd) = (BOOL(*)(HWND))0x41D550;
// SelStage / Teleporter Menu functions
static void (* const ClearPermitStage)(void) = (void(*)(void))0x41D610;
static BOOL(* const AddPermitStage)(int index, int event) = (BOOL(*)(int, int))0x41D630;
static BOOL(* const SubPermitStage)(int index) = (BOOL(*)(int))0x41D6A0;
static void (* const MoveStageSelectCursor)(void) = (void(*)(void))0x41D740;
static void (* const PutStageSelectObject)(void) = (void(*)(void))0x41D840;
static int (* const StageSelectLoop)(int* p_event) = (int(*)(int*))0x41DA00;
// Shoot functions
static void (* const ShootBullet_Frontia1)(int level) = (void(*)(int))0x41DBD0;
static void (* const ShootBullet_PoleStar)(int level) = (void(*)(int))0x41DE60;
static void (* const ShootBullet_FireBall)(int level) = (void(*)(int))0x41E110;
static void (* const ShootBullet_Machinegun1)(int level) = (void(*)(int))0x41E3D0;
static void (* const ShootBullet_Missile)(int level, BOOL bSuper) = (void(*)(int, BOOL))0x41E7B0;
static void (* const ShootBullet_Bubblin1)(void) = (void(*)(void))0x41EFD0;
static void (* const ShootBullet_Bubblin2)(int level) = (void(*)(int))0x41F280;
static void (* const ShootBullet_Sword)(int level) = (void(*)(int))0x41F580;
static void (* const ShootBullet_Nemesis)(int level) = (void(*)(int))0x41F710;
static void (* const ResetSpurCharge)(void) = (void(*)(void))0x41F9E0;
static void (* const ShootBullet_Spur)(int level) = (void(*)(int))0x41FA10;
static void (* const ShootBullet)(void) = (void(*)(void))0x41FE70;
// Sound functions
static BOOL(* const InitDirectSound)(HWND hWnd) = (BOOL(*)(HWND))0x4200C0;
static void (* const EndDirectSound)(void) = (void(*)(void))0x4201A0;
static BOOL(* const InitSoundObject)(LPCSTR resname, int no) = (BOOL(*)(LPCSTR, int))0x420240;
static BOOL(* const LoadSoundObject)(LPCSTR file_name, int no) = (BOOL(*)(LPCSTR, int))0x420390;
static BOOL(* const PlaySoundObject)(int no, SoundMode mode) = (BOOL(*)(int, SoundMode))0x420640;
static void (* const ChangeSoundFrequency)(int no, DWORD rate) = (void(*)(int, DWORD))0x420720;
static void (* const ChangeSoundVolume)(int no, long volume) = (void(*)(int, long))0x420760;
static void (* const ChangeSoundPan)(int no, long pan) = (void(*)(int, long))0x4207A0;
static int (* const MakePixToneObject)(const PIXTONEPARAMETER* ptp, int ptp_num, int no) = (int(*)(const PIXTONEPARAMETER*, int, int))0x4207E0;
// Stage functions
static BOOL(* const TransferStage)(int no, int w, int x, int y) = (BOOL(*)(int, int, int, int))0x420BE0;
static void (* const ChangeMusic)(int music_id) = (void(*)(int))0x420EE0;
static void (* const ReCallMusic)(void) = (void(*)(void))0x420F50;
// Star / Whimsical Star functions
static void (* const InitStar)(void) = (void(*)(void))0x420FA0;
static void (* const ActStar)(void) = (void(*)(void))0x421040;
static void (* const PutStar)(int fx, int fy) = (void(*)(int, int))0x4213B0;
// TextScript / TSC functions
static BOOL(* const InitTextScript2)(void) = (BOOL(*)(void))0x4214E0;
static void (* const EndTextScript)(void) = (void(*)(void))0x421570;
static void (* const EncryptionBinaryData2)(unsigned char* pData, long size) = (void(*)(unsigned char*, long))0x4215C0;
static BOOL(* const LoadTextScript2)(const char* name) = (BOOL(*)(const char*))0x421660;
static BOOL(* const LoadTextScript_Stage)(const char* name) = (BOOL(*)(const char*))0x421750;
static void (* const GetTextScriptPath)(char* path) = (void(*)(char*))0x4218E0;
static int (* const GetTextScriptNo)(int a) = (int(*)(int))0x421900;
static BOOL(* const StartTextScript)(int no) = (BOOL(*)(int))0x421990;
static BOOL(* const JumpTextScript)(int no) = (BOOL(*)(int))0x421AF0;
static void (* const StopTextScript)(void) = (void(*)(void))0x421C50;
static void (* const CheckNewLine)(void) = (void(*)(void))0x421C80;
static void (* const SetNumberTextScript)(int index) = (void(*)(int))0x421D10;
static void (* const ClearTextLine)(void) = (void(*)(void))0x421E90;
static void (* const PutTextScript)(void) = (void(*)(void))0x421F10;
static int (* const TextScriptProc)(void) = (int(*)(void))0x422510;
static void (* const RestoreTextScript)(void) = (void(*)(void))0x425790;
// Triangle functions
static void (* const InitTriangleTable)(void) = (void(*)(void))0x4257F0;
static int (* const GetSin)(unsigned char deg) = (int(*)(unsigned char))0x4258B0;
static int (* const GetCos)(unsigned char deg) = (int(*)(unsigned char))0x4258C0;
static unsigned char (* const GetArktan)(int x, int y) = (unsigned char(*)(int, int))0x4258E0;
// ValueView functions
static void (* const ClearValueView)(void) = (void(*)(void))0x425BC0;
static void (* const SetValueView)(int* px, int* py, int value) = (void(*)(int*, int*, int))0x425BF0;
static void (* const ActValueView)(void) = (void(*)(void))0x426360;
static void (* const PutValueView)(int flx, int fly) = (void(*)(int, int))0x426430;
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
static void (* const InitNpChar)(void) = (void(*)(void))0x46EB30;
static BOOL(* const LoadEvent)(const char* path_event) = (BOOL(*)(const char*))0x46EB50;
static void (* const SetUniqueParameter)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46EE50;
static void (* const SetNpChar)(int object_ID, int x_pos, int y_pos, int a4, int a5, int facing_right, int a7, int object_RAM_index) = (void(*)(int, int, int, int, int, int, int, int))0x46EFD0;
static void (* const SetDestroyNpChar)(int x, int y, signed int w, int num) = (void(*)(int, int, int, int))0x46F150;
static void (* const SetDestroyNpCharUp)(int x, int y, signed int w, int num) = (void(*)(int, int, int, int))0x46F200;
static void (* const SetExpObjects)(int x, int y, int exp) = (void(*)(int, int, int))0x46F2B0;
static BOOL(* const SetBulletObject)(int x, int y, int val) = (BOOL(*)(int, int, int))0x46F430;
static BOOL(* const SetLifeObject)(int x, int y, int val) = (BOOL(*)(int, int, int))0x46F630;
static void (* const VanishNpChar)(NPCHAR* npc) = (void(*)(NPCHAR*))0x46F760;
static void (* const PutNpChar)(int fx, int fy) = (void(*)(int, int))0x46F810;
static void (* const ActNpChar)(void) = (void(*)(void))0x46FA00;
static void (* const ChangeNpCharByEvent)(int code_event, int code_char, int dir) = (void(*)(int, int, int))0x46FAB0;
static void (* const ChangeCheckableNpCharByEvent)(int code_event, int code_char, int dir) = (void(*)(int, int, int))0x46FD10;
static void (* const SetNpCharActionNo)(int code_event, int code_char, int dir) = (void(*)(int, int, int))0x46FF90;
static void (* const MoveNpChar)(int code_event, int x, int y, int dir) = (void(*)(int, int, int, int))0x470060;
static void (* const BackStepMyChar)(int code_event) = (void(*)(int))0x470150;
static void (* const DeleteNpCharEvent)(int code) = (void(*)(int))0x470250;
static void (* const DeleteNpCharCode)(int code, BOOL bSmoke) = (void(*)(int, BOOL))0x4702D0;
static void (* const GetNpCharPosition)(int* x, int* y, int i) = (void(*)(int*, int*, int))0x470460;
static BOOL(* const IsNpCharCode)(int code) = (BOOL(*)(int))0x470490;
static BOOL(* const GetNpCharAlive)(int code_event) = (BOOL(*)(int))0x4704F0;
static int (* const CountAliveNpChar)(void) = (int(*)(void))0x470560;
// NpcHit / Npc collision functions
static void (* const JadgeHitNpCharBlock)(NPCHAR* npc, int x, int y) = (void(*)(NPCHAR*, int, int))0x4705C0;
static void (* const JudgeHitNpCharTriangleA)(NPCHAR* npc, int x, int y) = (void(*)(NPCHAR*, int, int))0x470870;
static void (* const JudgeHitNpCharTriangleB)(NPCHAR* npc, int x, int y) = (void(*)(NPCHAR*, int, int))0x470970;
static void (* const JudgeHitNpCharTriangleC)(NPCHAR* npc, int x, int y) = (void(*)(NPCHAR*, int, int))0x470A70;
static void (* const JudgeHitNpCharTriangleD)(NPCHAR* npc, int x, int y) = (void(*)(NPCHAR*, int, int))0x470B70;
static void (* const JudgeHitNpCharTriangleE)(NPCHAR* npc, int x, int y) = (void(*)(NPCHAR*, int, int))0x470C70;
static void (* const JudgeHitNpCharTriangleF)(NPCHAR* npc, int x, int y) = (void(*)(NPCHAR*, int, int))0x470D80;
static void (* const JudgeHitNpCharTriangleG)(NPCHAR* npc, int x, int y) = (void(*)(NPCHAR*, int, int))0x470E90;
static void (* const JudgeHitNpCharTriangleH)(NPCHAR* npc, int x, int y) = (void(*)(NPCHAR*, int, int))0x470FA0;
static void (* const JudgeHitNpCharWater)(NPCHAR* npc, int x, int y) = (void(*)(NPCHAR*, int, int))0x4710B0;
static void (* const HitNpCharMap)(void) = (void(*)(void))0x471160;
static void (* const LoseNpChar)(NPCHAR* npc, BOOL bVanish) = (void(*)(NPCHAR*, BOOL))0x471B80;
static void (* const JudgeHitNpCharBullet)(void) = (void(*)(void))0x471D50;
// NpcTbl / Npc Table functions
static BOOL(* const LoadNpcTable)(const char* path) = (BOOL(*)(const char*))0x472400;
static void (* const ReleaseNpcTable)(void) = (void(*)(void))0x472710;
// Boss functions
static void (* const InitBossChar)(int code) = (void(*)(int))0x472740;
static void (* const PutBossChar)(int fx, int fy) = (void(*)(int, int))0x472770;
static void (* const SetBossCharActNo)(int a) = (void(*)(int))0x472940;
static void (* const HitBossBullet)(void) = (void(*)(void))0x472950;
static void (* const ActBossChar_0)(void) = (void(*)(void))0x472FF0;
static void (* const ActBossChar)(void) = (void(*)(void))0x473000;
static void (* const HitBossMap)(void) = (void(*)(void))0x473080;
// Core boss
static void (* const ActBossChar_Core_Face)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4739B0;
static void (* const ActBossChar_Core_Tail)(NPCHAR* npc) = (void(*)(NPCHAR*))0x473BD0;
static void (* const ActBossChar_Core_Mini)(NPCHAR* npc) = (void(*)(NPCHAR*))0x473DE0;
static void (* const ActBossChar_Core_Hit)(NPCHAR* npc) = (void(*)(NPCHAR*))0x474340;
static void (* const ActBossChar_Core)(void) = (void(*)(void))0x474400;
// Undead Core boss
static void (* const ActBossChar_Undead)(void) = (void(*)(void))0x4753D0;
static void (* const ActBossCharA_Head)(NPCHAR* npc) = (void(*)(NPCHAR*))0x476790;
static void (* const ActBossCharA_Tail)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4769A0;
static void (* const ActBossCharA_Face)(NPCHAR* npc) = (void(*)(NPCHAR*))0x476B90;
static void (* const ActBossCharA_Mini)(NPCHAR* npc) = (void(*)(NPCHAR*))0x476E50;
static void (* const ActBossCharA_Hit)(NPCHAR* npc) = (void(*)(NPCHAR*))0x477230;
// Ballos boss
static void (* const ActBossChar_Ballos)(void) = (void(*)(void))0x4772F0;
static void (* const ActBossCharA_Eye)(NPCHAR* npc) = (void(*)(NPCHAR*))0x478AA0;
static void (* const ActBossCharA_Body)(NPCHAR* npc) = (void(*)(NPCHAR*))0x478F20;
static void (* const ActBossCharA_HITAI)(NPCHAR* npc) = (void(*)(NPCHAR*))0x478FE0;
static void (* const ActBossCharA_HARA)(NPCHAR* npc) = (void(*)(NPCHAR*))0x479010;
// Balfrog boss
static void (* const ActBossChar_Frog)(void) = (void(*)(void))0x479030;
static void (* const ActBossChar02_01)(void) = (void(*)(void))0x47A6A0;
static void (* const ActBossChar02_02)(void) = (void(*)(void))0x47A800;
// Ironhead boss
static void (* const ActBossChar_Ironhead)(void) = (void(*)(void))0x47A8A0;
// Boss Life functions
static void (* const InitBossLife)(void) = (void(*)(void))0x47B450;
static BOOL(* const StartBossLife)(int code_event) = (BOOL(*)(int))0x47B460;
static BOOL(* const StartBossLife2)(void) = (BOOL(*)(void))0x47B500;
static void (* const PutBossLife)(void) = (void(*)(void))0x47B540;
// Omega boss
static void (* const ActBossChar_Omega)(void) = (void(*)(void))0x47B6F0;
static void (* const ActBoss01_12)(void) = (void(*)(void))0x47C380;
static void (* const ActBoss01_34)(void) = (void(*)(void))0x47C4E0;
static void (* const ActBoss01_5)(void) = (void(*)(void))0x47C7A0;
// Heavy Press boss
static void (* const ActBossChar_Press)(void) = (void(*)(void))0x47C820;
// The Sisters boss
static void (* const ActBossChar_Twin)(void) = (void(*)(void))0x47D170;
static void (* const ActBossCharT_DragonBody)(NPCHAR* npc) = (void(*)(NPCHAR*))0x47DAA0;
static void (* const ActBossCharT_DragonHead)(NPCHAR* npc) = (void(*)(NPCHAR*))0x47DF10;
// Monster X boss
static void (* const ActBossChar_MonstX)(void) = (void(*)(void))0x47E6F0;
static void (* const ActBossChar_03_01)(NPCHAR* npc) = (void(*)(NPCHAR*))0x47F710;
static void (* const ActBossChar_03_02)(NPCHAR* npc) = (void(*)(NPCHAR*))0x480090;
static void (* const ActBossChar_03_03)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4802A0;
static void (* const ActBossChar_03_04)(NPCHAR* npc) = (void(*)(NPCHAR*))0x480550;
static void (* const ActBossChar_03_face)(NPCHAR* npc) = (void(*)(NPCHAR*))0x4808C0;