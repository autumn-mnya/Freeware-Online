// Mod loader for Freeware Cave Story
// Public domain

#include <ddraw.h>
#include <dinput.h>
#include <windows.h>

#define BULLET_MAX 0x40
#define CARET_MAX 0x40

// Variables
#define CS_window_upscale (*(int*)0x48F914) // mag
#define CS_clip_rect_common (*(RECT*)0x48F91C) // grcGame
#define CS_down_key_mapping (*(int*)0x49363C)
#define CS_background_tile_width (*(int*)0x499C78)
#define CS_background_tile_height (*(int*)0x499C7C)
#define CS_dword_499C8C (*(int*)0x499C8C)
#define CS_window_padding_h (*(int*)0x49CDA8)
#define CS_window_padding_w (*(int*)0x49CDAC)
#define CS_window_surface_width (*(int*)0x49D374)
#define CS_window_surface_height (*(int*)0x49D378)
#define CS_directdraw (*(IDirectDraw7**)0x49D37C)
#define CS_screen_primary_surface (*(IDirectDrawSurface7** const)0x49D380)
#define CS_screen_surface (*(IDirectDrawSurface7** const)0x49D384)
#define CS_surfaces (*(IDirectDrawSurface7*(*)[40])0x49D388)
#define CS_fade_counter (*(int*)0x49DB38)
#define CS_camera_x_pos (*(signed int*)0x49E1C8)
#define CS_camera_y_pos (*(signed int*)0x49E1CC)
#define CS_camera_x_destination (*(signed int*)0x49E1D0)
#define CS_camera_y_destination (*(signed int*)0x49E1D4)
#define CS_gamemode_flags (*(unsigned int*)0x49E1E8)
#define CS_input_bitfield_held (*(int*)0x49E210)
#define CS_input_bitfield_newly_pressed (*(int*)0x49E214)
#define CS_tsc_buffer (*(char**)0x4A5AD8)
#define CS_tsc_offset (*(unsigned int*)0x4A5AE0)
#define CS_pxm_buffer (*(unsigned char**)0x49E480)
#define CS_pxa_buffer ((unsigned char*)0x49E484)
#define CS_hWnd (*(HWND* const)0x49E458)
#define CS_gamepad_enabled (*(int*)0x49E45C)
#define CS_level_width (*(unsigned short*)0x49E586)
#define CS_level_height (*(unsigned short*)0x49E588)
#define CS_quote_display_flags (*(char*)0x49E638)
#define CS_quote_facing_right (*(BOOL*)0x49E640)
#define CS_quote_x_pos (*(int*)0x49E654) // gMC.x
#define CS_quote_y_pos (*(int*)0x49E658) // gMC.y
#define CS_quote_frame_id (*(int*)0x49E678) // gMC.ani_no
#define CS_quote_sprite_half_width (*(int*)0x49E68C)
#define CS_quote_sprite_half_height (*(int*)0x49E690)
#define CS_quote_weapon_selected (*(int*)0x499C68)
#define CS_music_fade_flag (*(int*)0x4A4E10)
#define CS_current_room (*(int*)0x4A57F0) // gStageNo
#define CS_current_music (*(int*)0x4A57F4) // gMusicNo
#define CS_previous_song_last_position (*(int*)0x4A57F8)
#define CS_previous_music (*(int*)0x4A57FC)

// String array
#define CS_org_playlist (*(char*(*)[42])0x4981E8)

struct OTHER_RECT	// The original name for this struct is unknown
{
	int front;
	int top;
	int back;
	int bottom;
};

// Enums
typedef enum CS_SurfaceID
{
	CS_SURFACE_ID_TITLE,
	CS_SURFACE_ID_PIXEL,
	CS_SURFACE_ID_LEVEL_TILESET,
	CS_SURFACE_ID_UNKNOWN_3,
	CS_SURFACE_ID_UNKNOWN_4,
	CS_SURFACE_ID_UNKNOWN_5,
	CS_SURFACE_ID_FADE,
	CS_SURFACE_ID_UNKNOWN_7,
	CS_SURFACE_ID_ITEM_IMAGE,
	CS_SURFACE_ID_MAP,
	CS_SURFACE_ID_SCREEN_GRAB,
	CS_SURFACE_ID_ARMS,
	CS_SURFACE_ID_ARMS_IMAGE,
	CS_SURFACE_ID_ROOM_NAME,
	CS_SURFACE_ID_STAGE_ITEM,
	CS_SURFACE_ID_LOADING,
	CS_SURFACE_ID_MY_CHAR,
	CS_SURFACE_ID_BULLET,
	CS_SURFACE_ID_UNKNOWN_12,
	CS_SURFACE_ID_CARET,
	CS_SURFACE_ID_NPC_SYM,
	CS_SURFACE_ID_LEVEL_SPRITESET_1,
	CS_SURFACE_ID_LEVEL_SPRITESET_2,
	CS_SURFACE_ID_NPC_REGU,
	CS_SURFACE_ID_UNKNOWN_18,
	CS_SURFACE_ID_UNKNOWN_19,
	CS_SURFACE_ID_TEXT_BOX,
	CS_SURFACE_ID_FACE,
	CS_SURFACE_ID_LEVEL_BACKGROUND,
	CS_SURFACE_ID_UNKNOWN_1D,
	CS_SURFACE_ID_UNKNOWN_1E,
	CS_SURFACE_ID_UNKNOWN_1F,
	CS_SURFACE_ID_UNKNOWN_20,
	CS_SURFACE_ID_UNKNOWN_21,
	CS_SURFACE_ID_UNKNOWN_22,
	CS_SURFACE_ID_UNKNOWN_23,
	CS_SURFACE_ID_CREDITS_IMAGE,
	CS_SURFACE_ID_CASTS,
	CS_SURFACE_ID_UNKNOWN_26,
	CS_SURFACE_ID_UNKNOWN_27
} CS_SurfaceID;

// Structs

// inventory
typedef struct CS_ARMS
{
	int code;

	int level;

	int exp;

	int max_num;

	int num;
} CS_ARMS;

typedef struct CS_ITEM
{
	int code;
} CS_ITEM;

// background

typedef struct CS_BACK
{
	BOOL flag;	// Unused - purpose unknown
	int partsW;
	int partsH;
	int numX;
	int numY;
	int type;
	int fx;
} CS_BACK;

// Boss

typedef struct CS_BOSSLIFE	// Not the original struct name
{
	BOOL flag;
	int* pLife;
	int max;
	int br;
	int count;
} CS_BOSSLIFE;

// Config
typedef struct CS_ConfigData
{
	char magic_string[0x20];
	char font_name[0x40];
	unsigned long directional_keys;
	unsigned long jump_shoot_keys;
	unsigned long jump_shoot_keys_2;
	unsigned long window_size;
	unsigned long gamepad_enabled;
	unsigned long gamepad_buttons[8];
} CS_ConfigData;

// Bullet
typedef struct CS_BULLET
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
} CS_BULLET;

// Bullet Table
typedef struct CS_BULLET_TABLE
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
} CS_BULLET_TABLE;

// Caret
struct CS_CARET
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

struct CS_CARET_TABLE
{
	int view_left;
	int view_top;
};

// Ending

enum CS_CREDIT_MODE
{
	CREDIT_MODE_STOP,
	CREDIT_MODE_SCROLL_READ,
	CREDIT_MODE_SCROLL_WAIT
};

enum CS_ILLUSTRATION_ACTION
{
	ILLUSTRATION_ACTION_IDLE,
	ILLUSTRATION_ACTION_SLIDE_IN,
	ILLUSTRATION_ACTION_SLIDE_OUT
};

struct CS_CREDIT
{
	long size;
	char* pData;
	int offset;
	int wait;
	CS_CREDIT_MODE mode;
	int start_x;
};

struct CS_STRIP
{
	int flag;
	int x;
	int y;
	int cast;
	char str[0x40];
};

struct CS_ILLUSTRATION
{
	CS_ILLUSTRATION_ACTION act_no;
	int x;
};

struct CS_ISLAND_SPRITE
{
	int x;
	int y;
};

// Fade

#define CS_WINDOW_WIDTH 320
#define CS_WINDOW_HEIGHT 240

#define FADE_WIDTH	(((CS_WINDOW_WIDTH - 1) / 16) + 1)
#define FADE_HEIGHT	(((CS_WINDOW_HEIGHT - 1) / 16) + 1)

struct CS_FADE
{
	int mode;
	BOOL bMask;
	int count;
	signed char ani_no[FADE_HEIGHT][FADE_WIDTH];
	signed char flag[FADE_HEIGHT][FADE_WIDTH];	// Not a BOOLEAN (those are unsigned)
	signed char dir;
};

// Flash

enum CS_FlashMode
{
	FLASH_MODE_EXPLOSION = 1,
	FLASH_MODE_FLASH = 2
};

static struct
{
	CS_FlashMode mode;
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

struct CS_DIRECTINPUTSTATUS
{
	BOOL bLeft;
	BOOL bRight;
	BOOL bUp;
	BOOL bDown;
	BOOL bButton[32]; // 32 is the number of buttons in DirectInput's `DIJOYSTATE` struct
};

// Mapping

typedef struct CS_MAP_DATA
{
	unsigned char* data;
	unsigned char atrb[0x100];
	short width;
	short length;
} CS_MAP_DATA;

// Map Name

typedef struct CS_MAP_NAME
{
	BOOL flag;
	int wait;
	char name[0x20];
} CS_MAP_NAME;

// MyChar

typedef struct CS_MYCHAR
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
} CS_MYCHAR;

// MycParam

typedef struct CS_ARMS_LEVEL
{
	int exp[3];
} CS_ARMS_LEVEL;

typedef struct CS_REC
{
	long counter[4];
	unsigned char random[4];
} CS_REC;

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
typedef struct CS_NPCHAR
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
	CS_SurfaceID surf;
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
	struct CS_NPCHAR* pNpc;
} CS_NPCHAR;

// NpChar Event

struct CS_EVENT
{
	short x;
	short y;
	short code_flag;
	short code_event;
	short code_char;
	unsigned short bits;
};

// Npc Table

struct CS_NPC_TBL_RECT
{
	unsigned char front;
	unsigned char top;
	unsigned char back;
	unsigned char bottom;
};

struct CS_NPC_TABLE
{
	unsigned short bits;
	unsigned short life;
	unsigned char surf;
	unsigned char hit_voice;
	unsigned char destroy_voice;
	unsigned char size;
	long exp;
	long damage;
	CS_NPC_TBL_RECT hit;
	CS_NPC_TBL_RECT view;
};

// PixTone

typedef struct CS_PIXTONEPARAMETER2
{
	int model;
	double num;
	int top;
	int offset;
} CS_PIXTONEPARAMETER2;

typedef struct CS_PIXTONEPARAMETER
{
	int use;
	int size;
	CS_PIXTONEPARAMETER2 oMain;
	CS_PIXTONEPARAMETER2 oPitch;
	CS_PIXTONEPARAMETER2 oVolume;
	int initial;
	int pointAx;
	int pointAy;
	int pointBx;
	int pointBy;
	int pointCx;
	int pointCy;
} CS_PIXTONEPARAMETER;

// Permit Stage

typedef struct CS_PERMIT_STAGE
{
	int index;
	int event;
} CS_PERMIT_STAGE;

// Stage Table

typedef struct CS_STAGE_TABLE
{
	char parts[0x20];
	char map[0x20];
	int bkType;
	char back[0x20];
	char npc[0x20];
	char boss[0x20];
	signed char boss_no;
	char name[0x20];
} CS_STAGE_TABLE;

// MusicID
typedef enum CS_MusicID
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
} CS_MusicID;

// Profile

typedef struct PROFILEDATA
{
	char code[8];
	int stage;
	CS_MusicID music;
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
	CS_ARMS arms[8];
	CS_ITEM items[32];
	CS_PERMIT_STAGE permitstage[8];
	signed char permit_mapping[0x80];
	char FLAG[4];
	unsigned char flags[1000];
} PROFILEDATA;

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
} cs_star[3];

// TextScript

typedef struct CS_TEXT_SCRIPT
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
} CS_TEXT_SCRIPT;

// ValueView

typedef struct CS_VALUEVIEW
{
	BOOL flag;
	int* px;
	int* py;
	int offset_y;
	int value;
	int count;
	RECT rect;
} CS_VALUEVIEW;

///////////////
// Functions //
///////////////



// ClearArmsData - 0x401000
static void (* const CS_ClearArmsData)(void) = (void(*)(void))0x401000;
// ClearItemData - 0x401030
static void (* const CS_ClearItemData)(void) = (void(*)(void))0x401030;
// AddArmsData - 0x401050
static BOOL(* const CS_AddArmsData)(long code, long max_num) = (BOOL(*)(long, long))0x401050;
// SubArmsData - 0x401160
static BOOL(* const CS_SubArmsData)(long code) = (BOOL(*)(long))0x401160;
// TradeArms - 0x401220
static BOOL(* const CS_TradeArms)(long code, long code2, long max_num) = (BOOL(*)(long, long, long))0x401220;
// AddItemData - 0x4012D0
static BOOL(* const CS_AddItemData)(long code) = (BOOL(*)(long))0x4012D0;
// SubItemData - 0x401330
static BOOL(* const CS_SubItemData)(long code) = (BOOL(*)(long))0x401330;
// MoveCampCursor - 0x4013C0
static void (* const CS_MoveCampCursor)(void) = (void(*)(void))0x4013C0;
// PutCampObject - 0x4016F0
static void (* const CS_PutCampObject)(void) = (void(*)(void))0x4016F0;
// CampLoop - 0x401D10
static void (* const CS_CampLoop)(void) = (void(*)(void))0x401D10;
// CheckItem - 0x401F20
static BOOL(* const CS_CheckItem)(long a) = (BOOL(*)(long))0x401F20;
// CheckArms - 0x401F60
static BOOL(* const CS_CheckArms)(long a) = (BOOL(*)(long))0x401F60;
// UseArmsEnergy - 0x401FA0
static BOOL(* const CS_UseArmsEnergy)(long num) = (BOOL(*)(long))0x401FA0;
// ChangeArmsEnergy - 0x402020
static BOOL(* const CS_ChangeArmsEnergy)(long num) = (BOOL(*)(long))0x402020;
// FullArmsEnergy - 0x402090
static void (* const CS_FullArmsEnergy)(void) = (void(*)(void))0x402090;
// RotationArms - 0x4020E0
static int (* const CS_RotationArms)(void) = (int(*)(void))0x4020E0;
// RotationArmsRev - 0x402190
static int (* const CS_RotationArmsRev)(void) = (int(*)(void))0x402190;
// ChangeToFirstArms - 0x402240
static void (* const CS_ChangeToFirstArms)(void) = (void(*)(void))0x402240;
// InitBack - 0x402270
static void (* const CS_InitBack)(const char* background_filename, int background_type) = (void(*)(const char*, int))0x402270;
// ActBack - 0x402370
static void (* const CS_ActBack)(void) = (void (*)(void))0x402370;
// PutBack - 0x4023D0
static void (* const CS_PutBack)(int camera_x_pos, int camera_y_pos) = (void(*)(int, int))0x4023D0;
// PutFront - 0x402830
static void (* const CS_PutFront)(int x_pos, int y_pos) = (void(*)(int, int))0x402830;
// JudgeHitBulletBlock - 0x4029B0
static int (* const CS_JudgeHitBulletBlock)(int x, int y, CS_BULLET *bul) = (int(*)(int, int, CS_BULLET*))0x4029B0;
// JudgeHitBulletBlock2 - 0x402B30
static int (* const CS_JudgeHitBulletBlock2)(int x, int y, unsigned char *atrb, CS_BULLET* bul) = (int(*)(int, int, unsigned char*, CS_BULLET*))0x402B30;
// JudgeHitBulletTriangleA - 0x402FC0
static int (* const CS_JudgeHitBulletTriangleA)(int x, int y, CS_BULLET* bul) = (int(*)(int, int, CS_BULLET*))0x402FC0;
// JudgeHitBulletTriangleB - 0x4030B0
static int (* const CS_JudgeHitBulletTriangleB)(int x, int y, CS_BULLET* bul) = (int(*)(int, int, CS_BULLET*))0x4030B0;
// JudgeHitBulletTriangleC - 0x4031A0
static int (* const CS_JudgeHitBulletTriangleC)(int x, int y, CS_BULLET* bul) = (int(*)(int, int, CS_BULLET*))0x4031A0;
// JudgeHitBulletTriangleD - 0x403290
static int (* const CS_JudgeHitBulletTriangleD)(int x, int y, CS_BULLET* bul) = (int(*)(int, int, CS_BULLET*))0x403290;
// JudgeHitBulletTriangleE - 0x403380
static int (* const CS_JudgeHitBulletTriangleE)(int x, int y, CS_BULLET* bul) = (int(*)(int, int, CS_BULLET*))0x403380;
// JudgeHitBulletTriangleF - 0x403470
static int (* const CS_JudgeHitBulletTriangleF)(int x, int y, CS_BULLET* bul) = (int(*)(int, int, CS_BULLET*))0x403470;
// JudgeHitBulletTriangleG - 0x403560
static int (* const CS_JudgeHitBulletTriangleG)(int x, int y, CS_BULLET* bul) = (int(*)(int, int, CS_BULLET*))0x403560;
// JudgeHitBulletTriangleH - 0x403650
static int (* const CS_JudgeHitBulletTriangleH)(int x, int y, CS_BULLET* bul) = (int(*)(int, int, CS_BULLET*))0x403650;
// HitBulletMap - 0x403740
static void (* const CS_HitBulletMap)(void) = (void(*)(void))0x403740;
// InitBullet - 0x403C00
static void (* const CS_InitBullet)(void) = (void(*)(void))0x403C00;
// CountArmsBullet - 0x403C40
static int (* const CS_CountArmsBullet)(int arms_code) = (int(*)(int))0x403C40;
// CountBulletNum - 0x403CB0
static int (* const CS_CountBulletNum)(int bullet_code) = (int(*)(int))0x403CB0;
// DeleteBullet - 0x403D10
static void (* const CS_DeleteBullet)(int code) = (void(*)(int))0x403D10;
// ClearBullet - 0x403D80
static void (* const CS_ClearBullet)(void) = (void(*)(void))0x403D80;
// PutBullet - 0x403DC0
static void (* const CS_PutBullet)(int fx, int fy) = (void(*)(int, int))0x403DC0;
// SetBullet - 0x403F80
static void (* const CS_SetBullet)(int no, int x, int y, int dir) = (void(*)(int, int, int, int))0x403F80;
// ActBullet_Frontia1 - 0x404160
static void (* const CS_ActBullet_Frontia1)(CS_BULLET *bul) = (void(*)(CS_BULLET*))0x404160;
// ActBullet_Frontia2 - 0x4043F0
static void (* const CS_ActBullet_Frontia2)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x4043F0;
// ActBullet_PoleStar - 0x4047B0
static void (* const CS_ActBullet_PoleStar)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x4047B0;
// ActBullet_FireBall - 0x404B30
static void (* const CS_ActBullet_FireBall)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x404B30;
// ActBullet_MachineGun - 0x405120
static void (* const CS_ActBullet_MachineGun)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x405120;
// ActBullet_Missile - 0x4055A0
static void (* const CS_ActBullet_Missile)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x4055A0;
// ActBullet_Bom - 0x405D80
static void (* const CS_ActBullet_Bom)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x405D80;
// ActBullet_Bubblin1 - 0x405F30
static void (* const CS_ActBullet_Bubblin1)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x405F30;
// ActBullet_Bubblin2 - 0x406190
static void (* const CS_ActBullet_Bubblin2)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x406190;
// ActBullet_Bubblin3 - 0x4064D0
static void (* const CS_ActBullet_Bubblin3)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x4064D0;
// ActBullet_Spine - 0x4068B0
static void (* const CS_ActBullet_Spine)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x4068B0;
// ActBullet_Sword1 - 0x406BB0
static void (* const CS_ActBullet_Sword1)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x406BB0;
// ActBullet_Sword2 - 0x406E60
static void (* const CS_ActBullet_Sword2)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x406E60;
// ActBullet_Sword3 - 0x407110
static void (* const CS_ActBullet_Sword3)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x407110;
// ActBullet_Edge - 0x4075E0
static void (* const CS_ActBullet_Edge)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x4075E0;
// ActBullet_Drop - 0x4078A0
static void (* const CS_ActBullet_Drop)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x4078A0;
// ActBullet_SuperMissile - 0x407910
static void (* const CS_ActBullet_SuperMissile)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x407910;
// ActBullet_SuperBom - 0x408080
static void (* const CS_ActBullet_SuperBom)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x408080;
// ActBullet_Nemesis - 0x408230
static void (* const CS_ActBullet_Nemesis)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x408230;
// ActBullet_Spur - 0x408710
static void (* const CS_ActBullet_Spur)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x408710;
// ActBullet_SpurTail - 0x408AE0
static void (* const CS_ActBullet_SpurTail)(CS_BULLET* bul, int level) = (void(*)(CS_BULLET*, int))0x408AE0;
// ActBullet_EnemyClear - 0x408F40
static void (* const CS_ActBullet_EnemyClear)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x408F40;
// ActBullet_Star - 0x408F90
static void (* const CS_ActBullet_Star)(CS_BULLET* bul) = (void(*)(CS_BULLET*))0x408F90;
// ActBullet - 0x408FC0
static void (* const CS_ActBullet)(void) = (void(*)(void))0x408FC0;
// IsSomeActiveBullet - 0x4095C0
static BOOL (* const CS_IsSomeActiveBullet)(void) = (BOOL(*)(void))0x4095C0;
// InitCaret - 0x409650
static void (* const CS_InitCaret)(void) = (void(*)(void))0x409650;
// ActCaret00 - 0x409670
static void (* const CS_ActCaret00)(CS_CARET *crt) = (void(*)(CS_CARET*))0x409670;
// ActCaret01 - 0x409680
static void (* const CS_ActCaret01)(CS_CARET* crt) = (void(*)(CS_CARET*))0x409680;
// ActCaret02 - 0x409880
static void (* const CS_ActCaret02)(CS_CARET* crt) = (void(*)(CS_CARET*))0x409880;
// ActCaret03 - 0x409B80
static void (* const CS_ActCaret03)(CS_CARET* crt) = (void(*)(CS_CARET*))0x409B80;
// ActCaret04 - 0x409C70
static void (* const CS_ActCaret04)(CS_CARET* crt) = (void(*)(CS_CARET*))0x409C70;
// ActCaret05 - 0x409E00
static void (* const CS_ActCaret05)(CS_CARET* crt) = (void(*)(CS_CARET*))0x409E00;
// ActCaret07 - 0x409F60
static void (* const CS_ActCaret07)(CS_CARET* crt) = (void(*)(CS_CARET*))0x409F60;
// ActCaret08 - 0x40A120
static void (* const CS_ActCaret08)(CS_CARET* crt) = (void(*)(CS_CARET*))0x40A120;
// ActCaret09 - 0x40A1B0
static void (* const CS_ActCaret09)(CS_CARET* crt) = (void(*)(CS_CARET*))0x40A1B0;
// ActCaret10 - 0x40A280
static void (* const CS_ActCaret10)(CS_CARET* crt) = (void(*)(CS_CARET*))0x40A280;
// ActCaret11 - 0x40A3F0
static void (* const CS_ActCaret11)(CS_CARET* crt) = (void(*)(CS_CARET*))0x40A3F0;
// ActCaret12 - 0x40A5A0
static void (* const CS_ActCaret12)(CS_CARET* crt) = (void(*)(CS_CARET*))0x40A5A0;
// ActCaret13 - 0x40A650
static void (* const CS_ActCaret13)(CS_CARET* crt) = (void(*)(CS_CARET*))0x40A650;
// ActCaret14 - 0x40A7E0
static void (* const CS_ActCaret14)(CS_CARET* crt) = (void(*)(CS_CARET*))0x40A7E0;
// ActCaret15 - 0x40A8F0
static void (* const CS_ActCaret15)(CS_CARET* crt) = (void(*)(CS_CARET*))0x40A8F0;
// ActCaret16 - 0x40A9E0
static void (* const CS_ActCaret16)(CS_CARET* crt) = (void(*)(CS_CARET*))0x40A9E0;
// ActCaret17 - 0x40AAA0
static void (* const CS_ActCaret17)(CS_CARET* crt) = (void(*)(CS_CARET*))0x40AAA0;
// ActCaret - 0x40AB50
static void (* const CS_ActCaret)(void) = (void(*)(void))0x40AB50;
// PutCaret - 0x40ABC0
static void (* const CS_PutCaret)(int fx, int fy) = (void(*)(int, int))0x40ABC0;
// SetCaret - 0x40AC90
static void (* const CS_SetCaret)(int x, int y, int code, int dir) = (void(*)(int, int, int, int))0x40AC90;
// LoadConfigData - 0x40AD60
static BOOL (* const CS_LoadConfigData)(CS_ConfigData* config_memory) = (BOOL(*)(CS_ConfigData*))0x40AD60;
// DefaultConfigData - 0x40AE30
static void(* const CS_DefaultConfigData)(CS_ConfigData* config_memory) = (void(*)(CS_ConfigData*))0x40AE30;
// VersionDialog - 0x40AEC0

// DebugMuteDialog - 0x40AFC0

// DebugSaveDialog - 0x40B1D0

// QuitDialog - 0x40B290

// SetClientOffset - 0x40B320
static void(* const CS_SetClientOffset)(int width, int height) = (void(*)(int, int))0x40B320;
// Flip_SystemTask - 0x40B340
static BOOL (* const CS_Flip_SystemTask)(HWND hWnd) = (BOOL(*)(HWND))0x40B340;
// StartDirectDraw - 0x40B340
static BOOL (* const CS_StartDirectDraw)(HWND hWnd, int lMagnification, int lColourDepth) = (BOOL(*)(HWND hWnd, int, int))0x40B340;
// EndDirectDraw - 0x40B6C0
static BOOL(* const CS_EndDirectDraw)(HWND hWnd) = (BOOL(*)(HWND))0x40B6C0;
// ReleaseSurface - 0x40B7A0
static void (* const CS_ReleaseSurface)(int s) = (void(*)(int))0x40B7A0;
// MakeSurface_Resource - 0x40B800
static BOOL(* const CS_MakeSurface_Resource)(const char *name, CS_SurfaceID surf_no) = (BOOL(*)(const char*, CS_SurfaceID))0x40B800;
// MakeSurface_File - 0x40BAC0
static BOOL(* const CS_MakeSurface_File)(const char* name, int surf_no) = (BOOL(*)(const char*, int))0x40BAC0;
// ReloadBitmap_Resource - 0x40BE10
static BOOL(* const CS_ReloadBitmap_Resource)(const char* name, CS_SurfaceID surf_no) = (BOOL(*)(const char*, CS_SurfaceID))0x40BE10;
// ReloadBitmap_File - 0x40BFD0
static BOOL(* const CS_ReloadBitmap_File)(const char* name, int surf_no) = (BOOL(*)(const char*, int))0x40BFD0;
// MakeSurface_Generic - 0x40C1D0
static BOOL(* const CS_MakeSurface_Generic)(int bxsize, int bysize, int surf_no) = (BOOL(*)(int, int, int))0x40C1D0;
// BackupSurface - 0x40C320
static void (* const CS_BackupSurface)(CS_SurfaceID surf_no, const RECT *rect) = (void(*)(CS_SurfaceID, const RECT*))0x40C320;
// PutBitmap3 - 0x40C3C0
static void (* const CS_PutBitmap3)(const RECT*, int, int, const RECT*, CS_SurfaceID) = (void(*)(const RECT*, int, int, const RECT*, CS_SurfaceID))0x40C3C0;
// PutBitmap4 - 0x40C5B0
static void (* const CS_PutBitmap4)(const RECT*, int, int, const RECT*, CS_SurfaceID) = (void(*)(const RECT*, int, int, const RECT*, CS_SurfaceID))0x40C5B0;
// Surface2Surface - 0x40C7A0
static void (* const CS_Surface2Surface)(int x, int y, const RECT *rect, CS_SurfaceID to, CS_SurfaceID from) = (void(*)(int, int, const RECT*, CS_SurfaceID, CS_SurfaceID))0x40C7A0;
// GetCortBoxColor - 0x40C8B0
static unsigned long (* const CS_GetCortBoxColor)(COLORREF col) = (unsigned long(*)(COLORREF))0x40C8B0;
// CortBox - 0x40C9E0
static void (* const CS_CortBox)(RECT* dst_rect, int colour) = (void(*)(RECT*, int))0x40C9E0;
// CortBox2 - 0x40CA80
static void (* const CS_CortBox2)(RECT* dst_rect, int colour, CS_SurfaceID surf_no) = (void(*)(RECT*, int, CS_SurfaceID))0x40CA80;
// out - 0x40CB30
static BOOL(* const CS_out)(char surface_identifier) = (BOOL(*)(char))0x40CB30;
// RestoreSurfaces - 0x40CB60
static int (* const CS_RestoreSurfaces)(void) = (int(*)(void))0x40CB60;
// InitTextObject - 0x40CD50
static void(* const CS_InitTextObject)(const char *name) = (void(*)(const char*))0x40CD50;
// PutText - 0x40CE00
static void (* const CS_PutText)(int x, int y, const char* text, unsigned int colour) = (void(*)(int, int, const char*, unsigned int))0x40CE00;
// PutText2 - 0x40CEB0
static void (* const CS_PutText2)(int x, int y, const char* text, unsigned int colour, CS_SurfaceID) = (void(*)(int, int, const char*, unsigned int, CS_SurfaceID))0x40CEB0;
// EndTextObject - 0x40CF70
static void (* const CS_EndTextObject)(void) = (void(*)(void))0x40CF70;
// ActionStripper - 0x40CF90
static void (* const CS_ActionStripper)(void) = (void(*)(void))0x40CF90;
// PutStripper - 0x40D010
static void (* const CS_PutStripper)(void) = (void(*)(void))0x40D010;
// SetStripper - 0x40D150
static void (* const CS_SetStripper)(int x, int y, const char *text, int cast) = (void(*)(int, int, const char*, int))0x40D150;
// RestoreStripper - 0x40D240
static void (* const CS_RestoreStripper)(void) = (void(*)(void))0x40D240;
// ActionIllust - 0x40D2D0
static void (* const CS_ActionIllust)(void) = (void(*)(void))0x40D2D0;
// PutIllust - 0x40D350
static void (* const CS_PutIllust)(void) = (void(*)(void))0x40D350;
// ReloadIllust - 0x40D3A0
static void (* const CS_ReloadIllust)(int a) = (void(*)(int))0x40D3A0;
// InitCreditScript - 0x40D3E0
static void (* const CS_InitCreditScript)(void) = (void(*)(void))0x40D3E0;
// ReleaseCreditScript - 0x40D410
static void (* const CS_ReleaseCreditScript)(void) = (void(*)(void))0x40D410;
// StartCreditScript - 0x40D440
static BOOL(* const CS_StartCreditScript)(void) = (BOOL(*)(void))0x40D440;
// ActionCredit - 0x40D5C0
static void (* const CS_ActionCredit)(void) = (void(*)(void))0x40D5C0;
// ActionCredit_Read - 0x40D620
static void (* const CS_ActionCredit_Read)(void) = (void(*)(void))0x40D620;
// GetScriptNumber - 0x40DB00
static int (* const CS_GetScriptNumber)(const char *text) = (int(*)(const char*))0x40DB00;
// SetCreditIllust - 0x40DB40
static void (* const CS_SetCreditIllust)(int a) = (void(*)(int))0x40DB40;
// CutCreditIllust - 0x40DB60
static void (* const CS_CutCreditIllust)(void) = (void(*)(void))0x40DB60;
// Scene_DownIsland - 0x40DB70
static int (* const CS_Scene_DownIsland)(HWND hWnd, int mode) = (int(*)(HWND, int))0x40DB70;
// Call_Escape - 0x40DD70
static int (* const CS_Call_Escape)(HWND hWnd) = (int(*)(HWND))0x40DD70;
// InitFade - 0x40DE60
static void (* const CS_InitFade)(void) = (void(*)(void))0x40DE60;
// SetFadeMask - 0x40DE90
static void (* const CS_SetFadeMask)(void) = (void(*)(void))0x40DE90;
// ClearFade - 0x40DEA0
static void (* const CS_ClearFade)(void) = (void(*)(void))0x40DEA0;
// StartFadeOut - 0x40DEC0
static void (* const CS_StartFadeOut)(signed char dir) = (void(*)(signed char))0x40DEC0;
// StartFadeIn - 0x40DF50
static void (* const CS_StartFadeIn)(signed char dir) = (void(*)(signed char))0x40DF50;
// ProcFade - 0x40DFE0
static void (* const CS_ProcFade)(void) = (void(*)(void))0x40DFE0;
// PutFade - 0x40E770
static void (* const CS_PutFade)(void) = (void(*)(void))0x40E770;
// GetFadeActive - 0x40E830
static BOOL(* const CS_GetFadeActive)(void) = (BOOL(*)(void))0x40E830;
// InitFlags - 0x40E850
static void (* const CS_InitFlags)(void) = (void(*)(void))0x40E850;
// InitSkipFlags - 0x40E870
static void (* const CS_InitSkipFlags)(void) = (void(*)(void))0x40E870;
// SetNPCFlag - 0x40E890
static void (* const CS_SetNPCFlag)(long a) = (void(*)(long))0x40E890;
// CutNPCFlag - 0x40E8E0
static void (* const CS_CutNPCFlag)(long a) = (void(*)(long))0x40E8E0;
// GetNPCFlag - 0x40E930
static BOOL(* const CS_GetNPCFlag)(long a) = (BOOL(*)(long))0x40E930;
// SetSkipFlag - 0x40E970
static void (* const CS_SetSkipFlag)(long a) = (void(*)(long))0x40E970;
// CutSkipFlag - 0x40E9C0
static void (* const CS_CutSkipFlag)(long a) = (void(*)(long))0x40E9C0;
// GetSkipFlag - 0x40EA10
static BOOL(* const CS_GetSkipFlag)(long a) = (BOOL(*)(long))0x40EA10;
// InitFlash - 0x40EA50
static void (* const CS_InitFlash)(void) = (void(*)(void))0x40EA50;
// SetFlash - 0x40EA70
static void (* const CS_SetFlash)(int x, int y, CS_FlashMode mode) = (void(*)(int, int, CS_FlashMode))0x40EA70;
// ActFlash_Explosion - 0x40EAC0
static void (* const CS_ActFlash_Explosion)(int flx, int fly) = (void(*)(int, int))0x40EAC0;
// ActFlash_Flash - 0x40ED20
static void (* const CS_ActFlash_Flash)(void) = (void(*)(void))0x40ED20;
// ActFlash - 0x40EDE0
static void (* const CS_ActFlash)(int flx, int fly) = (void(*)(int, int))0x40EDE0;
// PutFlash - 0x40EE20
static void (* const CS_PutFlash)(void) = (void(*)(void))0x40EE20;
// ResetFlash - 0x40EE60
static void (* const CS_ResetFlash)(void) = (void(*)(void))0x40EE60;
// MoveFrame3 - 0x40EE70
static void (* const CS_MoveFrame3)(void) = (void(*)(void))0x40EE70;
// GetFramePosition - 0x40F020
static void (* const CS_GetFramePosition)(int* fx, int* fy) = (void(*)(int*, int*))0x40F020;
// SetFramePosition - 0x40F040
static void (* const CS_SetFramePosition)(int fx, int fy) = (void(*)(int, int))0x40F040;
// SetFrameMyChar - 0x40F130
static void (* const CS_SetFrameMyChar)(void) = (void(*)(void))0x40F130;
// SetFrameTargetMyChar - 0x40F220
static void (* const CS_SetFrameTargetMyChar)(int wait) = (void(*)(int))0x40F220;
// SetFrameTargetNpChar - 0x40F250
static void (* const CS_SetFrameTargetNpChar)(int event, int wait) = (void(*)(int, int))0x40F250;
// SetFrameTargetBoss - 0x40F2D0
static void (* const CS_SetFrameTargetBoss)(int no, int wait) = (void(*)(int, int))0x40F2D0;
// SetQuake - 0x40F310
static void (* const CS_SetQuake)(int time) = (void(*)(int))0x40F310;
// SetQuake2 - 0x40F320
static void (* const CS_SetQuake2)(int time) = (void(*)(int))0x40F320;
// ResetQuake - 0x40F330
static void (* const CS_ResetQuake)(void) = (void(*)(void))0x40F330;
// Random - 0x40F350
static int (* const CS_Random)(int min, int max) = (int(*)(int, int))0x40F350;
// PutNumber4 - 0x40F380
static void (* const CS_PutNumber4)(int x, int y, int, int) = (void(*)(int, int, int, int))0x40F380;
// Game - 0x40F5F0
static BOOL(* const CS_Game)(HWND hWnd) = (BOOL(*)(HWND))0x40F5F0;
// ModeOpening - 0x40F730
static int (* const CS_ModeOpening)(HWND hWnd) = (int(*)(HWND))0x40F730;
// ModeTitle - 0x40F9B0
static int (* const CS_ModeTitle)(HWND hWnd) = (int(*)(HWND))0x40F9B0;
// ModeAction - 0x410400
static int (* const CS_ModeAction)(HWND hWnd) = (int(*)(HWND))0x410400;
// GetCompileDate - 0x4108B0
static void (* const CS_GetCompileDate)(int *year, int *month, int *day) = (void(*)(int*, int*, int*))0x4108B0;
// GetCompileVersion - 0x410990
static BOOL(* const CS_GetCompileVersion)(int* v1, int* v2, int* v3, int* v4) = (BOOL(*)(int*, int*, int*, int*))0x410990;
// OpenSoundVolume - 0x410AB0
static BOOL(* const CS_OpenSoundVolume)(HWND hWnd) = (BOOL(*)(HWND))0x410AB0;
// DeleteLog - 0x410BC0
static void (* const CS_DeleteLog)(void) = (void(*)(void))0x410BC0;
// WriteLog - 0x410C10
static BOOL(* const CS_WriteLog)(const char *string, int value1, int value2, int value3) = (BOOL(*)(const char*, int, int, int))0x410C10;
// GetDateLimit - 0x410CA0
static int (* const CS_GetDateLimit)(SYSTEMTIME* system_time_low, SYSTEMTIME* system_time_high) = (int(*)(SYSTEMTIME*, SYSTEMTIME*))0x410CA0;
// IsKeyFile - 0x410D10
static BOOL(* const CS_IsKeyFile)(const char *name) = (BOOL(*)(const char*))0x410D10;
// GetFileSizeLong - 0x410D80
static long(* const CS_GetFileSizeLong)(const char *path) = (long(*)(const char*))0x410D80;
// ErrorLog - 0x410DE0
static BOOL(* const CS_ErrorLog)(const char *string, int value) = (BOOL(*)(const char*, int))0x410DE0;
// IsShiftJIS - 0x410E90
static BOOL(* const CS_IsShiftJIS)(unsigned char c) = (BOOL(*)(unsigned char))0x410E90;
// CenteringWindowByParent - 0x410EE0
static BOOL(* const CS_CenteringWindowByParent)(HWND hWnd) = (BOOL(*)(HWND))0x410EE0;
// LoadWindowRect - 0x410FE0
static BOOL(* const CS_LoadWindowRect)(HWND hWnd, const char *filename, BOOL unknown) = (BOOL(*)(HWND, const char*, BOOL))0x410FE0;
// SaveWindowRect - 0x4111F0
static BOOL(* const CS_SaveWindowRect)(HWND hWnd, const char *filename) = (BOOL(*)(HWND, const char*))0x4111F0;
// IsEnableBitmap - 0x4112E0
static BOOL(* const CS_IsEnableBitmap)(const char *path) = (BOOL(*)(const char*))0x4112E0;
// LoadGenericData - 0x411390
static BOOL(* const CS_LoadGenericData)(void) = (BOOL(*)(void))0x411390;
// ReleaseDirectInput - 0x411E10
static void(* const CS_ReleaseDirectInput)(void) = (void(*)(void))0x411E10;
// ActivateDirectInput - 0x411E60
static BOOL(* const CS_ActivateDirectInput)(BOOL aquire) = (BOOL(*)(BOOL))0x411E60;
// InitDirectInput - 0x411EB0
static BOOL(* const CS_InitDirectInput)(HINSTANCE hinst, HWND hWnd) = (BOOL(*)(HINSTANCE, HWND))0x411EB0;
// HookAllDirectInputDevices - 0x411EF0
static BOOL(* const CS_FindAndOpenDirectInputDevice)(HWND hWnd) = (BOOL(*)(HWND))0x411EF0;
// EnumDevices_Callback - 0x411FC0
static BOOL(* const CS_EnumDevices_Callback)(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef) = (BOOL(*)(LPCDIDEVICEINSTANCE, LPVOID))0x411FC0;
// GetJoystickStatus - 0x4120F0
static BOOL(* const CS_GetJoystickStatus)(CS_DIRECTINPUTSTATUS *status) = (BOOL(*)(CS_DIRECTINPUTSTATUS*))0x4120F0;
// ResetJoystickStatus - 0x412250
static BOOL(* const CS_ResetJoystickStatus)(void) = (BOOL(*)(void))0x412250;
// GetTrg - 0x4122E0
static void (* const CS_GetTrg)(void) = (void(*)(void))0x4122E0;
// SetWindowName - 0x412320
static void (* const CS_SetWindowName)(HWND hWnd) = (void(*)(HWND))0x412320;
// PutFramePerSecound - 0x412370
static void (* const CS_PutFramePerSecound)(void) = (void(*)(void))0x412370;
// CountFramePerSecound - 0x4123A0
static unsigned long (* const CS_CountFramePerSecound)(void) = (unsigned long(*)(void))0x4123A0;
// WinMain - 0x412420
static int (* const CS_WinMain)(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) = (int(*)(HINSTANCE, HINSTANCE, LPSTR, int))0x412420;
// InactiveWindow - 0x412BC0
static void (* const CS_InactiveWindow)(void) = (void(*)(void))0x412BC0;
// ActiveWindow - 0x412BF0
static void (* const CS_ActiveWindow)(void) = (void(*)(void))0x412BF0;
// DragAndDropHandler - 0x412C30
static BOOL(* const CS_DragAndDropHandler)(HWND hWnd, WPARAM wParam) = (BOOL(*)(HWND, WPARAM))0x412C30;
// WindowProcedure - 0x412CA0
static LRESULT (* const CS_WindowProcedure)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) = (LRESULT(*)(HWND, UINT, WPARAM, LPARAM))0x412CA0;
// SystemTask - 0x413570
static BOOL (* const CS_SystemTask)(void) = (BOOL(*)(void))0x413570;
// JoystickProc - 0x4135E0
static void (* const CS_JoystickProc)(void) = (void(*)(void))0x4135E0;
// InitMapData2 - 0x413750
static BOOL(* const CS_InitMapData2)(void) = (BOOL(*)(void))0x413750;
// LoadMapData2 - 0x413770
static BOOL(* const CS_LoadMapData2)(const char *path_map) = (BOOL(*)(const char*))0x413770;
// LoadAttributeData - 0x4138A0
static BOOL(* const CS_LoadAttributeData)(const char *path_atrb) = (BOOL(*)(const char*))0x4138A0;
// EndMapData - 0x413930
static void (* const CS_EndMapData)(void) = (void(*)(void))0x413930;
// ReleasePartsImage - 0x413950
static void (* const CS_ReleasePartsImage)(void) = (void(*)(void))0x413950;
// GetMapData - 0x413960
static void (* const CS_GetMapData)(unsigned char** data, short* mw, short* ml) = (void(*)(unsigned char**, short*, short*))0x413960;
// GetAttribute - 0x4139A0
static unsigned char (* const CS_GetAttribute)(int x, int y) = (unsigned char(*)(int, int))0x4139A0;
// DeleteMapParts - 0x413A00
static void (* const CS_DeleteMapParts)(int x, int y) = (void(*)(int, int))0x413A00;
// ShiftMapParts - 0x413A20
static void (* const CS_ShiftMapParts)(int x, int y) = (void(*)(int, int))0x413A20;
// ChangeMapParts - 0x413A60
static BOOL(* const CS_ChangeMapParts)(int x, int y, unsigned char no) = (BOOL(*)(int, int, unsigned char))0x413A60;
// PutStage_Back - 0x413AF0
static void (* const CS_PutStage_Back)(int fx, int fy) = (void(*)(int, int))0x413AF0;
// PutStage_Front - 0x413C60
static void (* const CS_PutStage_Front)(int fx, int fy) = (void(*)(int, int))0x413C60;
// PutMapDataVector - 0x413E40
static void (* const CS_PutMapDataVector)(int fx, int fy) = (void(*)(int, int))0x413E40;
// ReadyMapName - 0x4140F0
static void (* const CS_ReadyMapName)(const char *str) = (void(*)(const char*))0x4140F0;
// PutMapName - 0x414250
static void (* const CS_PutMapName)(BOOL bMini) = (void(*)(BOOL))0x414250;
// StartMapName - 0x414310
static void (* const CS_StartMapName)(void) = (void(*)(void))0x414310;
// RestoreMapName - 0x414330
static void (* const CS_RestoreMapName)(void) = (void(*)(void))0x414330;
// WriteMiniMapLine - 0x4143C0
static void (* const CS_WriteMiniMapLine)(int line) = (void(*)(int))0x4143C0;
// MiniMapLoop - 0x414640
static int (* const CS_MiniMapLoop)(void) = (int(*)(void))0x414640;
// IsMapping - 0x414B00
static BOOL(* const CS_IsMapping)(void) = (BOOL(*)(void))0x414B00;
// StartMapping - 0x414B20
static void (* const CS_StartMapping)(void) = (void(*)(void))0x414B20;
// SetMapping - 0x414B40
static void (* const CS_SetMapping)(int a) = (void(*)(int))0x414B40;
// InitMyChar - 0x414B50
static void (* const CS_InitMyChar)(void) = (void(*)(void))0x414B50;
// AnimationMyChar - 0x414BF0
static void (* const CS_AnimationMyChar)(BOOL bKey) = (void(*)(BOOL))0x414BF0;
// ShowMyChar - 0x415220
static void (* const CS_ShowMyChar)(BOOL bShow) = (void(*)(BOOL))0x415220;
// PutMyChar - 0x415250
static void (* const CS_PutMyChar)(int camera_x, int camera_y) = (void(*)(int, int))0x415250;
// ActMyChar_Normal - 0x4156C0
static void (* const CS_ActMyChar_Normal)(BOOL bKey) = (void(*)(BOOL))0x4156C0;
// ActMyChar_Stream - 0x416470
static void (* const CS_ActMyChar_Stream)(BOOL bKey) = (void(*)(BOOL))0x416470;
// ActMyChar - 0x4168C0
static void (* const CS_ActMyChar)(BOOL bKey) = (void(*)(BOOL))0x4168C0;
// AirProcess - 0x416990
static void (* const CS_AirProcess)(void) = (void(*)(void))0x416990;
// GetMyCharPosition - 0x416AA0
static void (* const CS_GetMyCharPosition)(int *x, int *y) = (void(*)(int*, int*))0x416AA0;
// SetMyCharPosition - 0x416AC0
static void (* const CS_SetMyCharPosition)(int x, int y) = (void(*)(int, int))0x416AC0;
// MoveMyChar - 0x416B30
static void (* const CS_MoveMyChar)(int x, int y) = (void(*)(int, int))0x416B30;
// ZeroMyCharXMove - 0x416B50
static void (* const CS_ZeroMyCharXMove)(void) = (void(*)(void))0x416B50;
// GetUnitMyChar - 0x416B60
static int (* const CS_GetUnitMyChar)(void) = (int(*)(void))0x416B60;
// SetMyCharDirect - 0x416B70
static void (* const CS_SetMyCharDirect)(unsigned char dir) = (void(*)(unsigned char))0x416B70;
// ChangeMyUnit - 0x416C40
static void (* const CS_ChangeMyUnit)(unsigned char a) = (void(*)(unsigned char))0x416C40;
// PitMyChar - 0x416C50
static void (* const CS_PitMyChar)(void) = (void(*)(void))0x416C50;
// EquipItem - 0x416C70
static void (* const CS_EquipItem)(int flag, BOOL b) = (void(*)(int, BOOL))0x416C70;
// ResetCheck - 0x416CA0
static void (* const CS_ResetCheck)(void) = (void(*)(void))0x416CA0;
// SetNoise - 0x416CC0
static void (* const CS_SetNoise)(int no, int freq) = (void(*)(int, int))0x416CC0;
// CutNoise - 0x416D40
static void (* const CS_CutNoise)(void) = (void(*)(void))0x416D40;
// ResetNoise - 0x416D80
static void (* const CS_ResetNoise)(void) = (void(*)(void))0x416D80;
// SleepNoise - 0x416DF0
static void (* const CS_SleepNoise)(void) = (void(*)(void))0x416DF0;
// ResetMyCharFlag - 0x416E20

// JudgeHitMyCharBlock - 0x416E30

// PutlittleStar - 0x417160

// JudgeHitMyCharTriangleA - 0x4171D0

// JudgeHitMyCharTriangleB - 0x4172E0

// JudgeHitMyCharTriangleC - 0x4173F0

// JudgeHitMyCharTriangleD - 0x417500

// JudgeHitMyCharTriangleE - 0x417610

// JudgeHitMyCharTriangleF - 0x417720

// JudgeHitMyCharTriangleG - 0x417830

// JudgeHitMyCharTriangleH - 0x417940

// JudgeHitMyCharWater - 0x417A50

// JudgeHitMyCharDamage - 0x417AE0

// JudgeHitMyCharDamageW - 0x417B70

// JudgeHitMyCharVectLeft - 0x417C00

// JudgeHitMyCharVectUp - 0x417C90

// JudgeHitMyCharVectRight - 0x417D20

// JudgeHitMyCharVectDown - 0x417DB0

// HitMyCharMap - 0x417E40

// JudgeHitMyCharNPC - 0x4187F0

// JudgeHitMyCharNPC3 - 0x418B10

// JudgeHitMyCharNPC4 - 0x418C20

// HitMyCharNpChar - 0x419030

// HitMyCharBoss - 0x419450

// AddExpMyChar - 0x4196F0

// ZeroExpMyChar - 0x419890

// IsMaxExpMyChar - 0x4198C0

// DamageMyChar - 0x419910

// ZeroArmsEnergy_All - 0x419B50

// AddBulletMyChar - 0x419BA0

// AddLifeMyChar - 0x419C60

// AddMaxLifeMyChar - 0x419CB0

// PutArmsEnergy - 0x419D10

// PutActiveArmsList - 0x41A0B0

// PutMyLife - 0x41A1D0

// PutMyAir - 0x41A350
static void (* const CS_PutMyAir)(int x, int y) = (void(*)(int, int))0x41A350;
// PutTimeCounter - 0x41A430

// SaveTimeCounter - 0x41A5D0

// LoadTimeCounter - 0x41A7C0

// MakeSoundObject8 - 0x41A8F0

// ChangeOrganFrequency - 0x41ABA0

// ChangeOrganPan - 0x41AC70

// ChangeOrganVolume - 0x41AD20

// PlayOrganObject - 0x41ADC0

// ReleaseOrganyaObject - 0x41B2A0

// InitWaveData100 - 0x41B380

// MakeOrganyaWave - 0x41B3F0

// ChangeDramFrequency - 0x41B440

// ChangeDramPan - 0x41B480

// ChangeDramVolume - 0x41B4D0

// PlayDramObject - 0x41B510

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

// StartOrganya - 0x41C6C0

// LoadOrganya - 0x41C6F0
static void (* const CS_LoadOrganya)(const char*) = (void(*)(const char*))0x41C6F0;
// SetOrganyaPosition - 0x41C730
static void (* const CS_SetOrganyaPosition)(int) = (void(*)(int))0x41C730;
// GetOrganyaPosition - 0x41C770
static int (* const CS_GetOrganyaPosition)(void) = (int(*)(void))0x41C770;
// PlayOrganyaMusic - 0x41C790
static void (* const CS_PlayOrganyaMusic)(void) = (void(*)(void))0x41C790;
// ChangeOrganyaVolume - 0x41C7C0
static void (* const CS_ChangeOrganyaVolume)(int) = (void(*)(int))0x41C7C0;
// StopOrganyaMusic - 0x41C7F0
static void (* const CS_StopOrganyaMusic)(void) = (void(*)(void))0x41C7F0;
// SetOrganyaFadeout - 0x41C880
static void (* const CS_SetOrganyaFadeout)(void) = (void(*)(void))0x41C880;
// EndOrganya - 0x41C890

// MakeWaveTables - 0x41C8F0

// MakePixelWaveData - 0x41CB10

// IsProfile - 0x41CFC0

// SaveProfile - 0x41D040

// LoadProfile - 0x41D260

// InitializeGame - 0x41D550

// ClearPermitStage - 0x41D610

// AddPermitStage - 0x41D630

// SubPermitStage - 0x41D6A0

// MoveStageSelectCursor - 0x41D740

// PutStageSelectObject - 0x41D840

// StageSelectLoop - 0x41DA00

// ShootBullet_Frontial - 0x41DBD0
static void (* const CS_ShootBullet_Frontia1)(int level) = (void(*)(int))0x41DBD0;
// ShootBullet_PoleStar - 0x41DE60
static void (* const CS_ShootBullet_PoleStar)(int level) = (void(*)(int))0x41DE60;
// ShootBullet_FireBall - 0x41E110
static void (* const CS_ShootBullet_FireBall)(int level) = (void(*)(int))0x41E110;
// ShootBullet_Machinegun1 - 0x41E3D0
static void (* const CS_ShootBullet_Machinegun1)(int level) = (void(*)(int))0x41E3D0;
// ShootBullet_Missile - 0x41E7B0
static void (* const CS_ShootBullet_Missile)(int level, BOOL bSuper) = (void(*)(int, BOOL))0x41E7B0;
// ShootBullet_Bubblin1 - 0x41EFD0
static void (* const CS_ShootBullet_Bubblin1)(void) = (void(*)(void))0x41EFD0;
// ShootBullet_Bubblin2 - 0x41F280
static void (* const CS_ShootBullet_Bubblin2)(int level) = (void(*)(int))0x41F280;
// ShootBullet_Sword - 0x41F580
static void (* const CS_ShootBullet_Sword)(int level) = (void(*)(int))0x41F580;
// ShootBullet_Nemesis - 0x41F710
static void (* const CS_ShootBullet_Nemesis)(int level) = (void(*)(int))0x41F710;
// ShootBullet_ResetSpurCharge - 0x41F9E0
static void (* const CS_ResetSpurCharge)(void) = (void(*)(void))0x41F9E0;
// ShootBullet_Spur - 0x41FA10
static void (* const CS_ShootBullet_Spur)(int level) = (void(*)(int))0x41FA10;
// ShootBullet - 0x41FE70
static void (* const CS_ShootBullet)(void) = (void(*)(void))0x41FE70;
// InitDirectSound - 0x4200C0

// EndDirectSound - 0x4201A0

// InitSoundObject - 0x420240

// LoadSoundObject - 0x420390

// PlaySoundObject - 0x420640

// ChangeSoundFrequency - 0x420720

// ChangeSoundVolume - 0x420760

// ChangeSoundPan - 0x4207A0

// MakePixToneObject - 0x4207E0

// TransferStage - 0x420BE0

// ChangeMusic - 0x420EE0
static void (* const CS_ChangeMusic)(int music_id) = (void(*)(int))0x420EE0;
// ReCallMusic - 0x420F50
static void (* const CS_ReCallMusic)(void) = (void(*)(void))0x420F50;
// InitStar - 0x420FA0

// ActStar - 0x421040

// PutStar - 0x4213B0

// InitTextScript2 - 0x4214E0

// EndTextScript - 0x421570

// EncryptionBinaryData2 - 0x4215C0

// LoadTextScript2 - 0x421660

// LoadTextScript_Stage - 0x421750

// GetTextScriptPath - 0x4218E0

// GetTextScriptNo - 0x421900

// StartTextScript - 0x421990

// JumpTextScript - 0x421AF0

// StopTextScript - 0x421C50

// CheckNewLine - 0x421C80

// SetNumberTextScript - 0x421D10

// ClearTextLine - 0x421E90

// PutTextScript - 0x421F10

// TextScriptProc - 0x422510
static void (* const CS_TextScriptProc)(void) = (void(*)(void))0x422510;
// RestoreTextScript - 0x425790

// InitTriangleTable - 0x4257F0

// GetSin - 0x4258B0

// GetCos - 0x4258C0

// GetArktan - 0x4258E0

// ClearValueView - 0x425BC0

// SetValueView - 0x425BF0

// ActValueView - 0x426360

// PutValueView - 0x426430

// ActNpc000 - 0x426530

// ActNpc001 - 0x4265B0

// ActNpc002 - 0x426AF0

// ActNpc003 - 0x426FD0

// ActNpc004 - 0x427040

// ActNpc005 - 0x427480

// ActNpc006 - 0x427820

// ActNpc007 - 0x427C60

// ActNpc008 - 0x427F00

// ActNpc009 - 0x428260

// ActNpc010 - 0x428540

// ActNpc011 - 0x4289B0

// ActNpc012 - 0x428B10

// ActNpc013 - 0x429940

// ActNpc014 - 0x429A30

// ActNpc015 - 0x429BF0

// ActNpc016 - 0x429E00

// ActNpc017 - 0x42A0B0

// ActNpc018 - 0x42A360

// ActNpc019 - 0x42A490

// ActNpc020 - 0x42A830

// ActNpc021 - 0x42A940

// ActNpc022 - 0x42A9C0

// ActNpc023 - 0x42AA70

// ActNpc024 - 0x42ABD0

// ActNpc025 - 0x42B280

// ActNpc026 - 0x42B5E0

// ActNpc027 - 0x42BA90

// ActNpc028 - 0x42BAE0

// ActNpc029 - 0x42C1A0

// ActNpc030 - 0x42C320

// ActNpc031 - 0x42C4C0

// ActNpc032 - 0x42CA10

// ActNpc033 - 0x42CAC0

// ActNpc034 - 0x42CC20

// ActNpc035 - 0x42CCB0

// ActNpc036 - 0x42D010

// ActNpc037 - 0x42D760

// ActNpc038 - 0x42D810

// ActNpc039 - 0x42D960

// ActNpc040 - 0x42D9F0

// ActNpc041 - 0x42DE00

// ActNpc042 - 0x42DE70

// ActNpc043 - 0x42E9F0

// ActNpc044 - 0x42EAB0

// ActNpc045 - 0x42F060

// ActNpc046 - 0x42F320

// ActNpc047 - 0x42F3F0

// ActNpc048 - 0x42F780

// ActNpc049 - 0x42F9E0

// ActNpc050 - 0x42FEC0

// ActNpc051 - 0x4301B0

// ActNpc052 - 0x430780

// ActNpc053 - 0x4307D0

// ActNpc054 - 0x430B00

// ActNpc055 - 0x430EB0

// ActNpc056 - 0x4311D0

// ActNpc057 - 0x4315E0

// ActNpc058 - 0x431C20

// ActNpc059 - 0x4321F0

// ActNpc060 - 0x432460

// ActNpc061 - 0x432B50

// ActNpc062 - 0x4334C0

// ActNpc063 - 0x4336C0

// ActNpc064 - 0x433C00

// ActNpc065 - 0x433FC0

// ActNpc066 - 0x4342B0

// ActNpc067 - 0x4345E0

// ActNpc068 - 0x434D10

// ActNpc069 - 0x4355F0

// ActNpc070 - 0x435AB0

// ActNpc071 - 0x435BA0

// ActNpc072 - 0x435DE0

// ActNpc073 - 0x435FC0

// ActNpc074 - 0x436180

// ActNpc075 - 0x436540

// ActNpc076 - 0x436650

// ActNpc077 - 0x436690

// ActNpc078 - 0x4367E0

// ActNpc079 - 0x436870

// ActNpc080 - 0x436AE0

// ActNpc081 - 0x4370F0

// ActNpc082 - 0x4375E0

// ActNpc083 - 0x437D90

// ActNpc084 - 0x438250

// ActNpc085 - 0x4383D0

// ActNpc086 - 0x438590

// ActNpc087 - 0x438850

// ActNpc088 - 0x438B10

// ActNpc089 - 0x439580

// ActNpc090 - 0x439B00

// ActNpc091 - 0x439B50

// ActNpc092 - 0x439BC0

// ActNpc093 - 0x439DC0

// ActNpc094 - 0x43A220

// ActNpc095 - 0x43A680

// ActNpc096 - 0x43AAF0

// ActNpc097 - 0x43AD10

// ActNpc098 - 0x43AF20

// ActNpc099 - 0x43B140

// ActNpc100 - 0x43B350

// ActNpc101 - 0x43B410

// ActNpc102 - 0x43B4E0

// ActNpc103 - 0x43B5F0

// ActNpc104 - 0x43B7F0

// ActNpc105 - 0x43BD00

// ActNpc106 - 0x43BDB0

// ActNpc107 - 0x43BE00

// ActNpc108 - 0x43C4B0

// ActNpc109 - 0x43C610

// ActNpc110 - 0x43C8E0

// ActNpc111 - 0x43CDE0

// ActNpc112 - 0x43D0A0

// ActNpc113 - 0x43D320

// ActNpc114 - 0x43D860

// ActNpc115 - 0x43DAE0

// ActNpc116 - 0x43E190

// ActNpc117 - 0x43E1E0

// ActNpc118 - 0x43E9B0

// ActNpc119 - 0x43F230

// ActNpc120 - 0x43F280

// ActNpc121 - 0x43F310

// ActNpc122 - 0x43F4A0

// ActNpc123 - 0x43FC70

// ActNpc124 - 0x43FEF0

// ActNpc125 - 0x4400D0

// ActNpc126 - 0x4401F0

// ActNpc127 - 0x440760

// ActNpc128 - 0x4408B0

// ActNpc129 - 0x440CF0

// ActNpc130 - 0x441000

// ActNpc131 - 0x441360

// ActNpc132 - 0x441440

// ActNpc133 - 0x4419B0

// ActNpc134 - 0x441B20

// ActNpc135 - 0x441EC0

// ActNpc136 - 0x442340

// ActNpc137 - 0x442540

// ActNpc138 - 0x442590

// ActNpc139 - 0x442790

// ActNpc140 - 0x442BF0

// ActNpc141 - 0x443AC0

// ActNpc142 - 0x443EC0

// ActNpc143 - 0x444190

// ActNpc144 - 0x444230

// ActNpc145 - 0x444620

// ActNpc146 - 0x444780

// ActNpc147 - 0x444930

// ActNpc148 - 0x445050

// ActNpc149 - 0x445170

// ActNpc150 - 0x445660

// ActNpc151 - 0x445E30

// ActNpc152 - 0x445FA0

// ActNpc153 - 0x446020

// ActNpc154 - 0x446500

// ActNpc155 - 0x446710

// ActNpc156 - 0x446B60

// ActNpc157 - 0x446CA0

// ActNpc158 - 0x447180

// ActNpc159 - 0x4474C0

// ActNpc160 - 0x447700

// ActNpc161 - 0x447CB0

// ActNpc162 - 0x447E90

// ActNpc163 - 0x4482A0

// ActNpc164 - 0x448410

// ActNpc165 - 0x448580

// ActNpc166 - 0x4486E0

// ActNpc167 - 0x4487F0

// ActNpc168 - 0x448A10

// ActNpc169 - 0x448BE0

// ActNpc170 - 0x4495A0

// ActNpc171 - 0x4498C0

// ActNpc172 - 0x449C10

// ActNpc173 - 0x449D70

// ActNpc174 - 0x44A3C0

// ActNpc175 - 0x44A610

// ActNpc176 - 0x44A7D0

// ActNpc177 - 0x44ABB0

// ActNpc178 - 0x44AEE0

// ActNpc179 - 0x44B080

// ActNpc180 - 0x44B210

// ActNpc181 - 0x44BE10

// ActNpc182 - 0x44C220

// ActNpc183 - 0x44C630

// ActNpc184 - 0x44C7A0

// ActNpc185 - 0x44CA60

// ActNpc186 - 0x44CBE0

// ActNpc187 - 0x44CDB0

// ActNpc188 - 0x44D070

// ActNpc189 - 0x44D3A0

// ActNpc190 - 0x44D5E0

// ActNpc191 - 0x44D740

// ActNpc192 - 0x44DA00

// ActNpc193 - 0x44DE20

// ActNpc194 - 0x44DEA0

// ActNpc195 - 0x44DF10

// ActNpc196 - 0x44DF60

// ActNpc197 - 0x44E020

// ActNpc198 - 0x44E260

// ActNpc199 - 0x44E400

// ActNpc200 - 0x44E5F0

// ActNpc201 - 0x44EC40

// ActNpc202 - 0x44ECE0

// ActNpc203 - 0x44EE40

// ActNpc204 - 0x44F1F0

// ActNpc205 - 0x44F3E0

// ActNpc206 - 0x44F6D0

// ActNpc207 - 0x44FB40

// ActNpc208 - 0x44FCB0

// ActNpc209 - 0x450280

// ActNpc210 - 0x450400

// ActNpc211 - 0x450760

// ActNpc212 - 0x450810

// ActNpc213 - 0x450BF0

// ActNpc214 - 0x4512A0

// ActNpc215 - 0x451430

// ActNpc216 - 0x4517F0

// ActNpc217 - 0x451840

// ActNpc218 - 0x451CA0

// ActNpc219 - 0x451DA0

// ActNpc220 - 0x451E90

// ActNpc221 - 0x452000

// ActNpc222 - 0x452470

// ActNpc223 - 0x4524E0

// ActNpc224 - 0x452700

// ActNpc225 - 0x4528D0

// ActNpc226 - 0x452A50

// ActNpc227 - 0x452D10

// ActNpc228 - 0x452D60

// ActNpc229 - 0x4530D0

// ActNpc230 - 0x453190

// ActNpc231 - 0x453260

// ActNpc232 - 0x4536F0

// ActNpc233 - 0x4539B0

// ActNpc234 - 0x453E60

// ActNpc235 - 0x453F20

// ActNpc236 - 0x454310

// ActNpc237 - 0x4548B0

// ActNpc238 - 0x454A00

// ActNpc239 - 0x454DF0

// ActNpc240 - 0x454F00

// ActNpc241 - 0x455370

// ActNpc242 - 0x455710

// ActNpc243 - 0x455A10

// ActNpc244 - 0x455AB0

// ActNpc245 - 0x455C10

// ActNpc246 - 0x455E00

// ActNpc247 - 0x456110

// ActNpc248 - 0x456F50

// ActNpc249 - 0x4570B0

// ActNpc250 - 0x457180

// ActNpc251 - 0x457470

// ActNpc252 - 0x457570

// ActNpc253 - 0x4579D0

// ActNpc254 - 0x457B00

// ActNpc255 - 0x457D70

// ActNpc256 - 0x458010

// ActNpc257 - 0x458360

// ActNpc258 - 0x4585A0

// ActNpc259 - 0x4585F0

// ActNpc260 - 0x458810

// ActNpc261 - 0x458A70

// ActNpc262 - 0x458C30

// ActNpc263 - 0x458DF0

// ActNpc264 - 0x459950

// ActNpc265 - 0x459B30

// ActNpc266 - 0x459C00

// ActNpc267 - 0x459D80

// ActNpc268 - 0x45B3D0

// ActNpc269 - 0x45BCB0

// ActNpc270 - 0x45BF10

// ActNpc271 - 0x45C230

// ActNpc272 - 0x45C500

// ActNpc273 - 0x45C5A0

// ActNpc274 - 0x45C750

// ActNpc275 - 0x45CC80

// ActNpc276 - 0x45CEA0

// ActNpc277 - 0x45D780

// ActNpc278 - 0x45D930

// ActNpc279 - 0x45DCF0

// ActNpc280 - 0x45E110

// ActNpc281 - 0x45E360

// ActNpc282 - 0x45E4C0

// ActNpc283 - 0x45E950

// ActNpc284 - 0x45F910

// ActNpc285 - 0x460910

// ActNpc286 - 0x460AE0

// ActNpc287 - 0x460BB0

// ActNpc288 - 0x460D70

// ActNpc289 - 0x4610D0

// ActNpc290 - 0x4614A0

// ActNpc291 - 0x461800

// ActNpc292 - 0x4618B0

// ActNpc293 - 0x4618C0

// ActNpc294 - 0x4619E0

// ActNpc295 - 0x461B90

// ActNpc296 - 0x461E40

// ActNpc297 - 0x461FD0

// ActNpc298 - 0x462050

// ActNpc299 - 0x4623D0

// ActNpc300 - 0x4624E0

// ActNpc301 - 0x4625A0

// ActNpc302 - 0x462890

// ActNpc303 - 0x462AF0

// ActNpc304 - 0x462C80

// ActNpc305 - 0x462E00

// ActNpc306 - 0x462F60

// ActNpc307 - 0x4630F0

// ActNpc308 - 0x4632B0

// ActNpc309 - 0x463710

// ActNpc310 - 0x463AC0

// ActNpc311 - 0x464090

// ActNpc312 - 0x464740

// ActNpc313 - 0x464BB0

// ActNpc314 - 0x465CC0

// ActNpc315 - 0x465F60

// ActNpc316 - 0x4664B0

// ActNpc317 - 0x466790

// ActNpc318 - 0x466B80

// ActNpc319 - 0x466E50

// ActNpc320 - 0x4670C0

// ActNpc321 - 0x4673F0

// ActNpc322 - 0x4676D0

// ActNpc323 - 0x467C60

// ActNpc324 - 0x467F40

// ActNpc325 - 0x467FE0

// ActNpc326 - 0x468230

// ActNpc327 - 0x468830

// ActNpc328 - 0x468990

// ActNpc329 - 0x4689E0

// ActNpc330 - 0x468A90

// ActNpc331 - 0x468D70

// ActNpc332 - 0x468F50

// ActNpc333 - 0x469140

// ActNpc334 - 0x469290

// ActNpc335 - 0x469430

// ActNpc336 - 0x469610

// ActNpc337 - 0x4696B0

// ActNpc338 - 0x469800

// ActNpc339 - 0x469AA0

// ActNpc340 - 0x469B40

// ActNpc341 - 0x46B240

// ActNpc342 - 0x46B340

// ActNpc343 - 0x46BD80

// ActNpc344 - 0x46BE10

// ActNpc345 - 0x46BF00

// ActNpc346 - 0x46C1D0

// ActNpc347 - 0x46C710

// ActNpc348 - 0x46C9B0

// ActNpc349 - 0x46CAC0

// ActNpc350 - 0x46CB50

// ActNpc351 - 0x46D340

// ActNpc352 - 0x46D5D0

// ActNpc353 - 0x46DBE0

// ActNpc354 - 0x46E110

// ActNpc355 - 0x46E280

// ActNpc356 - 0x46E480

// ActNpc357 - 0x46E730

// ActNpc358 - 0x46E870

// ActNpc359 - 0x46E9E0

// ActNpc360 - 0x46EA90

// InitNpChar - 0x46EB30

// LoadEvent - 0x46EB50

// SetUniqueParameter - 0x46EE50

// SetNpChar - 0x46EFD0
static void (* const CS_SetNpChar)(int object_ID, int x_pos, int y_pos, int a4, int a5, int facing_right, int a7, int object_RAM_index) = (void(*)(int, int, int, int, int, int, int, int))0x46EFD0;
// SetDestroyNpChar - 0x46F150
static void (* const CS_SetDestroyNpChar)(int x, int y, signed int range, int count) = (void(*)(int, int, int, int))0x46F150;
// SetDestroyNpCharUp - 0x46F200

// SetExpObjects - 0x46F2B0

// SetBulletObject - 0x46F430

// SetLifeObject - 0x46F630

// VanishNpChar - 0x46F760

// PutNpChar - 0x46F810

// ActNpChar - 0x46FA00
static void (* const CS_ActNpChar)(void) = (void(*)(void))0x46FA00;
// ChangeNpCharByEvent - 0x46FAB0

// ChangeCheckableNpCharByEvent - 0x46FD10

// SetNpCharActionNo - 0x46FF90

// MoveNpChar - 0x470060

// BackStepMyChar - 0x470150

// DeleteNpCharEvent - 0x470250
static void (* const CS_DeleteNpCharEvent)(int code) = (void(*)(int))0x470250;
// DeleteNpCharCode - 0x4702D0
static void (* const CS_DeleteNpCharCode)(int code, BOOL bSmoke) = (void(*)(int, BOOL))0x4702D0;
// GetNpCharPosition - 0x470460

// IsNpCharCode - 0x470490

// GetNpCharAlive - 0x4704F0

// CountAliveNpChar - 0x470560

// JadgeHitNpCharBlock - 0x4705C0

// JudgeHitNpCharTriangleA - 0x470870

// JudgeHitNpCharTriangleB - 0x470970

// JudgeHitNpCharTriangleC - 0x470A70

// JudgeHitNpCharTriangleD - 0x470B70

// JudgeHitNpCharTriangleE - 0x470C70

// JudgeHitNpCharTriangleF - 0x470D80

// JudgeHitNpCharTriangleG - 0x470E90

// JudgeHitNpCharTriangleH - 0x470FA0

// JudgeHitNpCharWater - 0x4710B0

// HitNpCharMap - 0x471160

// LoseNpChar - 0x471B80
static void (* const CS_LoseNpChar)(CS_NPCHAR* npc, BOOL bVanish) = (void(*)(CS_NPCHAR*, BOOL))0x471B80;
// HitNpCharBullet - 0x471D50

// LoadNpcTable - 0x472400

// ReleaseNpcTable - 0x472710

// InitBossChar - 0x472740

// PutBossChar - 0x472770

// SetBossCharActNo - 0x472940

// HitBossBullet - 0x472950

// ActBossChar_0 - 0x472FF0

// ActBossChar - 0x473000

// HitBossMap - 0x473080

// ActBossChar_Core_Face - 0x4739B0

// ActBossChar_Core_Tail - 0x473BD0

// ActBossChar_Core_Mini - 0x473DE0

// ActBossChar_Core_Hit - 0x474340

// ActBossChar_Core - 0x474400

// ActBossChar_Undead - 0x4753D0

// ActBossCharA_Head - 0x476790

// ActBossCharA_Tail - 0x4769A0

// ActBossCharA_Face - 0x476B90

// ActBossCharA_Mini - 0x476E50

// ActBossCharA_Hit - 0x477230

// ActBossChar_Ballos - 0x4772F0

// ActBossChar_Eye - 0x478AA0

// ActBossChar_Body - 0x478F20

// ActBossChar_HITAI - 0x478FE0

// ActBossChar_HARA - 0x479010

// ActBossChar_Frog - 0x479030

// ActBossChar02_01 - 0x47A6A0

// ActBossChar02_02 - 0x47A800

// ActBossChar_Ironhead - 0x47A8A0

// InitBossLife - 0x47B450

// StartBossLife - 0x47B460

// StartBossLife2 - 0x47B500

// PutBossLife - 0x47B540

// ActBossChar_Omega - 0x47B6F0

// ActBoss01_12 - 0x47C380

// ActBoss01_34 - 0x47C4E0

// ActBoss01_5 - 0x47C7A0

// ActBossChar_Press - 0x47C820

// ActBossChar_Twin - 0x47D170

// ActBossCharT_DragonBody - 0x47DAA0

// ActBossCharT_DragonHead - 0x47DF10

// ActBossChar_MonstX - 0x47E6F0

// ActBossChar_03_01 - 0x47F710

// ActBossChar_03_02 - 0x480090

// ActBossChar_03_03 - 0x4802A0

// ActBossChar_03_04 - 0x480550

// ActBossChar_03_face - 0x4808C0






// Hookspaces & Hookjumps

// COMPATIBILITY NOTES:
// TSC+'s code starts at 4225CB, but the first 2 instructions are identical to Vanilla.
// On unknown command error, TSC+ jumps to 425244.
// If you're still using NICE-Lua at this point:
// Most people using NICE-Lua asked me (20kdc) to do their work, so this shouldn't be an issue, but it operates at
//  a start of 4225ED, and 6 bytes. (This was incompatible with TSC+, and this mistake is avoided here.)
// Theoretically, either of these could be used, but CSH_tsc_start allows the user to override an existing command,
//  and seems to be close enough to the start that it shouldn't get affected.
#define CSH_tsc_start (void*) 0x4225D5, 12
#define CSH_tsc_end (void*) 0x425244, 12
// Aka 4252A7, or "ParserEnd", but minus some indirection.
#define CSJ_tsc_done 0x4225CB