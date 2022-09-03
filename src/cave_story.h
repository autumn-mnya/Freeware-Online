// Mod loader for Freeware Cave Story
// Public domain

#include <ddraw.h>
#include <dinput.h>
#include <windows.h>

extern const char* gameIp;
extern const char* gamePort;
extern int mim_compatibility;
extern int show_player_names;
extern bool hide_me_on_map;

#define ARMS_MAX 8
#define ITEM_MAX 32
#define BULLET_MAX 0x40
#define CARET_MAX 0x40
#define MAX_STRIP ((CS_WINDOW_HEIGHT / 16) + 1)

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


// Variables
#define CS_window_upscale (*(int*)0x48F914) // mag
#define grcGame (*(RECT*)0x48F91C) // grcGame
#define grcFull (*(RECT*)0x48F92C) // grcFull
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
#define gMC_x (*(int*)0x49E654) // gMC.x
#define gMC_y (*(int*)0x49E658) // gMC.y
#define gMC_ani_no (*(int*)0x49E678) // gMC.ani_no
#define CS_quote_sprite_half_width (*(int*)0x49E68C)
#define CS_quote_sprite_half_height (*(int*)0x49E690)
#define gSelectedArms (*(int*)0x499C68)
#define CS_music_fade_flag (*(int*)0x4A4E10)
#define gStageNo (*(int*)0x4A57F0) // gStageNo
#define gMusicNo (*(int*)0x4A57F4) // gMusicNo
#define CS_previous_song_last_position (*(int*)0x4A57F8)
#define CS_previous_music (*(int*)0x4A57FC)
#define g_GameFlags (*(int*)0x49E1E8) // g_GameFlags

// <MIM Compatibility
#define CSM_MIM_unobstructive (*(unsigned int*)0x49E184)
#define CSM_MIM_tsc_plus  (*(int*)0x49E09C)

// String array
#define CS_org_playlist (*(char*(*)[42])0x4981E8)

// Window Width / Window Height

#define CS_WINDOW_WIDTH 320
#define CS_WINDOW_HEIGHT 240

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
	CS_SURFACE_ID_USERNAME, //custom -- username
	CS_SURFACE_ID_SKIN, // custom -- skins
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
	CS_SURFACE_ID_UNKNOWN_27,
	CS_SURFACE_ID_MAX = 40
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

// Sound

enum CS_SoundMode
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
static BOOL(* const CS_MakeSurface_Generic)(int bxsize, int bysize, int surf_no, BOOL bSystem) = (BOOL(*)(int, int, int, BOOL))0x40C1D0;
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
static void (* const CS_ResetMyCharFlag)(void) = (void(*)(void))0x416E20;
// JudgeHitMyCharBlock - 0x416E30
static int (* const CS_JudgeHitMyCharBlock)(int x, int y) = (int(*)(int, int))0x416E30;
// PutlittleStar - 0x417160
static void (* const CS_PutlittleStar)(void) = (void(*)(void))0x417160;
// JudgeHitMyCharTriangleA - 0x4171D0
static int (* const CS_JudgeHitMyCharTriangleA)(int x, int y) = (int(*)(int, int))0x4171D0;
// JudgeHitMyCharTriangleB - 0x4172E0
static int (* const CS_JudgeHitMyCharTriangleB)(int x, int y) = (int(*)(int, int))0x4172E0;
// JudgeHitMyCharTriangleC - 0x4173F0
static int (* const CS_JudgeHitMyCharTriangleC)(int x, int y) = (int(*)(int, int))0x4173F0;
// JudgeHitMyCharTriangleD - 0x417500
static int (* const CS_JudgeHitMyCharTriangleD)(int x, int y) = (int(*)(int, int))0x417500;
// JudgeHitMyCharTriangleE - 0x417610
static int (* const CS_JudgeHitMyCharTriangleE)(int x, int y) = (int(*)(int, int))0x417610;
// JudgeHitMyCharTriangleF - 0x417720
static int (* const CS_JudgeHitMyCharTriangleF)(int x, int y) = (int(*)(int, int))0x417720;
// JudgeHitMyCharTriangleG - 0x417830
static int (* const CS_JudgeHitMyCharTriangleG)(int x, int y) = (int(*)(int, int))0x417830;
// JudgeHitMyCharTriangleH - 0x417940
static int (* const CS_JudgeHitMyCharTriangleH)(int x, int y) = (int(*)(int, int))0x417940;
// JudgeHitMyCharWater - 0x417A50
static int (* const CS_JudgeHitMyCharWater)(int x, int y) = (int(*)(int, int))0x417A50;
// JudgeHitMyCharDamage - 0x417AE0
static int (* const CS_JudgeHitMyCharDamage)(int x, int y) = (int(*)(int, int))0x417AE0;
// JudgeHitMyCharDamageW - 0x417B70
static int (* const CS_JudgeHitMyCharDamageW)(int x, int y) = (int(*)(int, int))0x417B70;
// JudgeHitMyCharVectLeft - 0x417C00
static int (* const CS_JudgeHitMyCharVectLeft)(int x, int y) = (int(*)(int, int))0x417C00;
// JudgeHitMyCharVectUp - 0x417C90
static int (* const CS_JudgeHitMyCharVectUp)(int x, int y) = (int(*)(int, int))0x417C90;
// JudgeHitMyCharVectRight - 0x417D20
static int (* const CS_JudgeHitMyCharVectRight)(int x, int y) = (int(*)(int, int))0x417D20;
// JudgeHitMyCharVectDown - 0x417DB0
static int (* const CS_JudgeHitMyCharVectDown)(int x, int y) = (int(*)(int, int))0x417DB0;
// HitMyCharMap - 0x417E40
static void (* const CS_HitMyCharMap)(void) = (void(*)(void))0x417E40;
// JudgeHitMyCharNPC - 0x4187F0
static int (* const CS_JudgeHitMyCharNPC)(CS_NPCHAR *npc) = (int(*)(CS_NPCHAR*))0x4187F0;
// JudgeHitMyCharNPC3 - 0x418B10
static unsigned char (* const CS_JudgeHitMyCharNPC3)(CS_NPCHAR* npc) = (unsigned char(*)(CS_NPCHAR*))0x418B10;
// JudgeHitMyCharNPC4 - 0x418C20
static int (* const CS_JudgeHitMyCharNPC4)(CS_NPCHAR* npc) = (int(*)(CS_NPCHAR*))0x418C20;
// HitMyCharNpChar - 0x419030
static void (* const CS_HitMyCharNpChar)(void) = (void(*)(void))0x419030;
// HitMyCharBoss - 0x419450
static void (* const CS_HitMyCharBoss)(void) = (void(*)(void))0x419450;
// AddExpMyChar - 0x4196F0
static void (* const CS_AddExpMyChar)(int x) = (void(*)(int))0x4196F0;
// ZeroExpMyChar - 0x419890
static void (* const CS_ZeroExpMyChar)(void) = (void(*)(void))0x419890;
// IsMaxExpMyChar - 0x4198C0
static BOOL(* const CS_IsExpMyChar)(void) = (BOOL(*)(void))0x4198C0;
// DamageMyChar - 0x419910
static void (* const CS_DamageMyChar)(int damage) = (void(*)(int))0x419910;
// ZeroArmsEnergy_All - 0x419B50
static void (* const CS_ZeroArmsEnergy_All)(void) = (void(*)(void))0x419B50;
// AddBulletMyChar - 0x419BA0
static void (* const CS_AddBulletMyChar)(int no, int val) = (void(*)(int, int))0x419BA0;
// AddLifeMyChar - 0x419C60
static void (* const CS_AddLifeMyChar)(int x) = (void(*)(int))0x419C60;
// AddMaxLifeMyChar - 0x419CB0
static void (* const CS_AddMaxLifeMyChar)(int val) = (void(*)(int))0x419CB0;
// PutArmsEnergy - 0x419D10
static void (* const CS_PutArmsEnergy)(BOOL flash) = (void(*)(BOOL))0x419D10;
// PutActiveArmsList - 0x41A0B0
static void (* const CS_PutActiveArmsList)(void) = (void(*)(void))0x41A0B0;
// PutMyLife - 0x41A1D0
static void (* const CS_PutMyLife)(BOOL flash) = (void(*)(BOOL))0x41A1D0;
// PutMyAir - 0x41A350
static void (* const CS_PutMyAir)(int x, int y) = (void(*)(int, int))0x41A350;
// PutTimeCounter - 0x41A430
static void (* const CS_PutTimeCounter)(int x, int y) = (void(*)(int, int))0x41A430;
// SaveTimeCounter - 0x41A5D0
static BOOL(* const CS_SaveTimeCounter)(void) = (BOOL(*)(void))0x41A5D0;
// LoadTimeCounter - 0x41A7C0
static int (* const CS_LoadTimeCounter)(void) = (int(*)(void))0x41A7C0;
// MakeSoundObject8 - 0x41A8F0
static BOOL(* const CS_MakeSoundObject8)(signed char* wavep, signed char track, signed char pipi) = (BOOL(*)(signed char*, signed char, signed char))0x41A8F0;
// ChangeOrganFrequency - 0x41ABA0
static void (* const CS_ChangeOrganFrequency)(unsigned char key, signed char track, long a) = (void(*)(unsigned char, signed char, long))0x41ABA0;
// ChangeOrganPan - 0x41AC70
static void (* const CS_ChangeOrganPan)(unsigned char key, unsigned char pan, signed char track) = (void(*)(unsigned char, unsigned char, signed char))0x41AC70;
// ChangeOrganVolume - 0x41AD20
static void (* const CS_ChangeOrganVolume)(int no, long volume, signed char track) = (void(*)(int, long, signed char))0x41AD20;
// PlayOrganObject - 0x41ADC0
static void (* const CS_PlayOrganObject)(unsigned char key, int mode, signed char track, long freq) = (void(*)(unsigned char, int, signed char, long))0x41ADC03;
// ReleaseOrganyaObject - 0x41B2A0
static void (* const CS_ReleaseOrganyaObject)(signed char track) = (void(*)(signed char))0x41B2A0;
// InitWaveData100 - 0x41B380
static BOOL(* const CS_InitWaveData100)(void) = (BOOL(*)(void))0x41B380;
// MakeOrganyaWave - 0x41B3F0
static BOOL(* const CS_MakeOrganyaWave)(signed char track, signed char wave_no, signed char pipi) = (BOOL(*)(signed char, signed char, signed char))0x41B3F0;
// ChangeDramFrequency - 0x41B440
static void (* const CS_ChangeDramFrequency)(unsigned char key, signed char track) = (void(*)(unsigned char, signed char))0x41B440;
// ChangeDramPan - 0x41B480
static void (* const CS_ChangeDramPan)(unsigned char pan, signed char track) = (void(*)(unsigned char, signed char))0x41B440;
// ChangeDramVolume - 0x41B4D0
static void (* const CS_ChangeDramVolume)(long volume, signed char track) = (void(*)(long, signed char))0x41B4D0;
// PlayDramObject - 0x41B510
static void (* const CS_PlayDramObject)(unsigned char key, int mode, signed char track) = (void(*)(unsigned char, int, signed char))0x41B510;
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
static void (* const CS_EndOrganya)(void) = (void(*)(void))0x41C890;
// MakeWaveTables - 0x41C8F0
static void (* const CS_MakeWaveTables)(void) = (void(*)(void))0x41C8F0;
// MakePixelWaveData - 0x41CB10
static BOOL (* const CS_MakePixelWaveData)(const CS_PIXTONEPARAMETER* ptp, unsigned char* pData) = (BOOL(*)(const CS_PIXTONEPARAMETER*, unsigned char*))0x41CB10;
// IsProfile - 0x41CFC0
static BOOL(* const CS_IsProfile)(void) = (BOOL(*)(void))0x41CFC0;
// SaveProfile - 0x41D040
static BOOL(* const CS_SaveProfile)(const char *name) = (BOOL(*)(const char*))0x41D040;
// LoadProfile - 0x41D260
static BOOL(* const CS_LoadProfile)(const char *name) = (BOOL(*)(const char*))0x41D260;
// InitializeGame - 0x41D550
static BOOL(* const CS_InitializeGame)(HWND hWnd) = (BOOL(*)(HWND))0x41D550;
// ClearPermitStage - 0x41D610
static void (* const CS_ClearPermitStage)(void) = (void(*)(void))0x41D610;
// AddPermitStage - 0x41D630
static BOOL(* const CS_AddPermitStage)(int index, int event) = (BOOL(*)(int, int))0x41D630;
// SubPermitStage - 0x41D6A0
static BOOL(* const CS_SubPermitStage)(int index) = (BOOL(*)(int))0x41D6A0;
// MoveStageSelectCursor - 0x41D740
static void (* const CS_MoveStageSelectCursor)(void) = (void(*)(void))0x41D740;
// PutStageSelectObject - 0x41D840
static void (* const CS_PutStageSelectObject)(void) = (void(*)(void))0x41D840;
// StageSelectLoop - 0x41DA00
static int (* const CS_StageSelectLoop)(int *p_event) = (int(*)(int*))0x41DA00;
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
static BOOL(* const CS_InitDirectSound)(HWND hWnd) = (BOOL(*)(HWND))0x4200C0;
// EndDirectSound - 0x4201A0
static void (* const CS_EndDirectSound)(void) = (void(*)(void))0x4201A0;
// InitSoundObject - 0x420240
static BOOL(* const CS_InitSoundObject)(LPCSTR resname, int no) = (BOOL(*)(LPCSTR, int))0x420240;
// LoadSoundObject - 0x420390
static BOOL(* const CS_LoadSoundObject)(LPCSTR file_name, int no) = (BOOL(*)(LPCSTR, int))0x420390;
// PlaySoundObject - 0x420640
static BOOL(* const CS_PlaySoundObject)(int no, CS_SoundMode mode) = (BOOL(*)(int, CS_SoundMode))0x420640;
// ChangeSoundFrequency - 0x420720
static void (* const CS_ChangeSoundFrequency)(int no, DWORD rate) = (void(*)(int, DWORD))0x420720;
// ChangeSoundVolume - 0x420760
static void (* const CS_ChangeSoundVolume)(int no, long volume) = (void(*)(int, long))0x420760;
// ChangeSoundPan - 0x4207A0
static void (* const CS_ChangeSoundPan)(int no, long pan) = (void(*)(int, long))0x4207A0;
// MakePixToneObject - 0x4207E0
static int (* const CS_MakePixToneObject)(const CS_PIXTONEPARAMETER* ptp, int ptp_num, int no) = (int(*)(const CS_PIXTONEPARAMETER*, int, int))0x4207E0;
// TransferStage - 0x420BE0
static BOOL(* const CS_TransferStage)(int no, int w, int x, int y) = (BOOL(*)(int, int, int, int))0x420BE0;
// ChangeMusic - 0x420EE0
static void (* const CS_ChangeMusic)(int music_id) = (void(*)(int))0x420EE0;
// ReCallMusic - 0x420F50
static void (* const CS_ReCallMusic)(void) = (void(*)(void))0x420F50;
// InitStar - 0x420FA0
static void (* const CS_InitStar)(void) = (void(*)(void))0x420FA0;
// ActStar - 0x421040
static void (* const CS_ActStar)(void) = (void(*)(void))0x421040;
// PutStar - 0x4213B0
static void (* const CS_PutStar)(int fx, int fy) = (void(*)(int, int))0x4213B0;
// InitTextScript2 - 0x4214E0
static BOOL(* const CS_InitTextScript2)(void) = (BOOL(*)(void))0x4214E0;
// EndTextScript - 0x421570
static void (* const CS_EndTextScript)(void) = (void(*)(void))0x421570;
// EncryptionBinaryData2 - 0x4215C0
static void (* const CS_EncryptionBinaryData2)(unsigned char* pData, long size) = (void(*)(unsigned char*, long))0x4215C0;
// LoadTextScript2 - 0x421660
static BOOL(* const CS_LoadTextScript2)(const char *name) = (BOOL(*)(const char*))0x421660;
// LoadTextScript_Stage - 0x421750
static BOOL(* const CS_LoadTextScript_Stage)(const char* name) = (BOOL(*)(const char*))0x421750;
// GetTextScriptPath - 0x4218E0
static void (* const CS_GetTextScriptPath)(char *path) = (void(*)(char*))0x4218E0;
// GetTextScriptNo - 0x421900
static int (* const CS_GetTextScriptNo)(int a) = (int(*)(int))0x421900;
// StartTextScript - 0x421990
static BOOL(* const CS_StartTextScript)(const char* name) = (BOOL(*)(const char*))0x421990;
// JumpTextScript - 0x421AF0
static BOOL(* const CS_JumpTextScript)(int no) = (BOOL(*)(int))0x421AF0;
// StopTextScript - 0x421C50
static void (* const CS_StopTextScript)(void) = (void(*)(void))0x421C50;
// CheckNewLine - 0x421C80
static void (* const CS_CheckNewLine)(void) = (void(*)(void))0x421C80;
// SetNumberTextScript - 0x421D10
static void (* const CS_SeeNumberTextScript)(int index) = (void(*)(int))0x421D10;
// ClearTextLine - 0x421E90
static void (* const CS_ClearTextLine)(void) = (void(*)(void))0x421E90;
// PutTextScript - 0x421F10
static void (* const CS_PutTextScript)(void) = (void(*)(void))0x421F10;
// TextScriptProc - 0x422510
static int (* const CS_TextScriptProc)(void) = (int(*)(void))0x422510;
// RestoreTextScript - 0x425790
static void (* const CS_RestoreTextScript)(void) = (void(*)(void))0x425790;
// InitTriangleTable - 0x4257F0
static void (* const CS_InitTriangleTable)(void) = (void(*)(void))0x4257F0;
// GetSin - 0x4258B0
static int (* const CS_GetSin)(unsigned char deg) = (int(*)(unsigned char))0x4258B0;
// GetCos - 0x4258C0
static int (* const CS_GetCos)(unsigned char deg) = (int(*)(unsigned char))0x4258C0;
// GetArktan - 0x4258E0
static unsigned char (* const CS_GetArktan)(int x, int y) = (unsigned char(*)(int, int))0x4258E0;
// ClearValueView - 0x425BC0
static void (* const CS_ClearValueView)(void) = (void(*)(void))0x425BC0;
// SetValueView - 0x425BF0
static void (* const CS_SetValueView)(int *px, int *py, int value) = (void(*)(int*, int*, int))0x425BF0;
// ActValueView - 0x426360
static void (* const CS_ActValueView)(void) = (void(*)(void))0x426360;
// PutValueView - 0x426430
static void (* const CS_PutValueView)(int flx, int fly) = (void(*)(int, int))0x426430;
// ActNpc function list (000 - 361)
static void (* const ActNpc000)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x426530;
static void (* const ActNpc001)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4265B0;
static void (* const ActNpc002)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x426AF0;
static void (* const ActNpc003)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x426FD0;
static void (* const ActNpc004)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x427040;
static void (* const ActNpc005)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x427480;
static void (* const ActNpc006)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x427820;
static void (* const ActNpc007)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x427C60;
static void (* const ActNpc008)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x427F00;
static void (* const ActNpc009)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x428260;
static void (* const ActNpc010)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x428540;
static void (* const ActNpc011)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4289B0;
static void (* const ActNpc012)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x428B10;
static void (* const ActNpc013)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x429940;
static void (* const ActNpc014)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x429A30;
static void (* const ActNpc015)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x429BF0;
static void (* const ActNpc016)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x429E00;
static void (* const ActNpc017)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42A0B0;
static void (* const ActNpc018)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42A360;
static void (* const ActNpc019)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42A490;
static void (* const ActNpc020)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42A830;
static void (* const ActNpc021)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42A940;
static void (* const ActNpc022)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42A9C0;
static void (* const ActNpc023)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42AA70;
static void (* const ActNpc024)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42ABD0;
static void (* const ActNpc025)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42B280;
static void (* const ActNpc026)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42B5E0;
static void (* const ActNpc027)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42BA90;
static void (* const ActNpc028)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42BAE0;
static void (* const ActNpc029)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42C1A0;
static void (* const ActNpc030)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42C320;
static void (* const ActNpc031)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42C4C0;
static void (* const ActNpc032)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42CA10;
static void (* const ActNpc033)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42CAC0;
static void (* const ActNpc034)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42CC20;
static void (* const ActNpc035)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42CCB0;
static void (* const ActNpc036)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42D010;
static void (* const ActNpc037)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42D760;
static void (* const ActNpc038)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42D810;
static void (* const ActNpc039)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42D960;
static void (* const ActNpc040)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42D9F0;
static void (* const ActNpc041)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42DE00;
static void (* const ActNpc042)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42DE70;
static void (* const ActNpc043)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42E9F0;
static void (* const ActNpc044)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42EAB0;
static void (* const ActNpc045)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42F060;
static void (* const ActNpc046)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42F320;
static void (* const ActNpc047)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42F3F0;
static void (* const ActNpc048)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42F780;
static void (* const ActNpc049)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42F9E0;
static void (* const ActNpc050)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x42FEC0;
static void (* const ActNpc051)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4301B0;
static void (* const ActNpc052)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x430780;
static void (* const ActNpc053)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4307D0;
static void (* const ActNpc054)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x430B00;
static void (* const ActNpc055)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x430EB0;
static void (* const ActNpc056)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4311D0;
static void (* const ActNpc057)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4315E0;
static void (* const ActNpc058)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x431C20;
static void (* const ActNpc059)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4321F0;
static void (* const ActNpc060)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x432460;
static void (* const ActNpc061)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x432B50;
static void (* const ActNpc062)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4334C0;
static void (* const ActNpc063)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4336C0;
static void (* const ActNpc064)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x433C00;
static void (* const ActNpc065)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x433FC0;
static void (* const ActNpc066)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4342B0;
static void (* const ActNpc067)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4345E0;
static void (* const ActNpc068)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x434D10;
static void (* const ActNpc069)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4355F0;
static void (* const ActNpc070)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x435AB0;
static void (* const ActNpc071)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x435BA0;
static void (* const ActNpc072)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x435DE0;
static void (* const ActNpc073)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x435FC0;
static void (* const ActNpc074)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x436180;
static void (* const ActNpc075)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x436540;
static void (* const ActNpc076)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x436650;
static void (* const ActNpc077)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x436690;
static void (* const ActNpc078)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4367E0;
static void (* const ActNpc079)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x436870;
static void (* const ActNpc080)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x436AE0;
static void (* const ActNpc081)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4370F0;
static void (* const ActNpc082)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4375E0;
static void (* const ActNpc083)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x437D90;
static void (* const ActNpc084)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x438250;
static void (* const ActNpc085)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4383D0;
static void (* const ActNpc086)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x438590;
static void (* const ActNpc087)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x438850;
static void (* const ActNpc088)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x438B10;
static void (* const ActNpc089)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x439580;
static void (* const ActNpc090)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x439B00;
static void (* const ActNpc091)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x439B50;
static void (* const ActNpc092)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x439BC0;
static void (* const ActNpc093)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x439DC0;
static void (* const ActNpc094)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43A220;
static void (* const ActNpc095)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43A680;
static void (* const ActNpc096)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43AAF0;
static void (* const ActNpc097)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43AD10;
static void (* const ActNpc098)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43AF20;
static void (* const ActNpc099)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43B140;
static void (* const ActNpc100)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43B350;
static void (* const ActNpc101)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43B410;
static void (* const ActNpc102)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43B4E0;
static void (* const ActNpc103)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43B5F0;
static void (* const ActNpc104)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43B7F0;
static void (* const ActNpc105)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43BD00;
static void (* const ActNpc106)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43BDB0;
static void (* const ActNpc107)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43BE00;
static void (* const ActNpc108)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43C4B0;
static void (* const ActNpc109)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43C610;
static void (* const ActNpc110)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43C8E0;
static void (* const ActNpc111)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43CDE0;
static void (* const ActNpc112)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43D0A0;
static void (* const ActNpc113)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43D320;
static void (* const ActNpc114)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43D860;
static void (* const ActNpc115)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43DAE0;
static void (* const ActNpc116)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43E190;
static void (* const ActNpc117)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43E1E0;
static void (* const ActNpc118)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43E9B0;
static void (* const ActNpc119)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43F230;
static void (* const ActNpc120)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43F280;
static void (* const ActNpc121)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43F310;
static void (* const ActNpc122)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43F4A0;
static void (* const ActNpc123)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43FC70;
static void (* const ActNpc124)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x43FEF0;
static void (* const ActNpc125)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4400D0;
static void (* const ActNpc126)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4401F0;
static void (* const ActNpc127)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x440760;
static void (* const ActNpc128)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4408B0;
static void (* const ActNpc129)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x440CF0;
static void (* const ActNpc130)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x441000;
static void (* const ActNpc131)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x441360;
static void (* const ActNpc132)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x441440;
static void (* const ActNpc133)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4419B0;
static void (* const ActNpc134)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x441B20;
static void (* const ActNpc135)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x441EC0;
static void (* const ActNpc136)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x442340;
static void (* const ActNpc137)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x442540;
static void (* const ActNpc138)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x442590;
static void (* const ActNpc139)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x442790;
static void (* const ActNpc140)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x442BF0;
static void (* const ActNpc141)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x443AC0;
static void (* const ActNpc142)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x443EC0;
static void (* const ActNpc143)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x444190;
static void (* const ActNpc144)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x444230;
static void (* const ActNpc145)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x444620;
static void (* const ActNpc146)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x444780;
static void (* const ActNpc147)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x444930;
static void (* const ActNpc148)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x445050;
static void (* const ActNpc149)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x445170;
static void (* const ActNpc150)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x445660;
static void (* const ActNpc151)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x445E30;
static void (* const ActNpc152)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x445FA0;
static void (* const ActNpc153)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x446020;
static void (* const ActNpc154)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x446500;
static void (* const ActNpc155)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x446710;
static void (* const ActNpc156)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x446B60;
static void (* const ActNpc157)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x446CA0;
static void (* const ActNpc158)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x447180;
static void (* const ActNpc159)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4474C0;
static void (* const ActNpc160)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x447700;
static void (* const ActNpc161)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x447CB0;
static void (* const ActNpc162)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x447E90;
static void (* const ActNpc163)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4482A0;
static void (* const ActNpc164)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x448410;
static void (* const ActNpc165)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x448580;
static void (* const ActNpc166)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4486E0;
static void (* const ActNpc167)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4487F0;
static void (* const ActNpc168)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x448A10;
static void (* const ActNpc169)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x448BE0;
static void (* const ActNpc170)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4495A0;
static void (* const ActNpc171)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4498C0;
static void (* const ActNpc172)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x449C10;
static void (* const ActNpc173)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x449D70;
static void (* const ActNpc174)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44A3C0;
static void (* const ActNpc175)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44A610;
static void (* const ActNpc176)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44A7D0;
static void (* const ActNpc177)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44ABB0;
static void (* const ActNpc178)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44AEE0;
static void (* const ActNpc179)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44B080;
static void (* const ActNpc180)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44B210;
static void (* const ActNpc181)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44BE10;
static void (* const ActNpc182)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44C220;
static void (* const ActNpc183)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44C630;
static void (* const ActNpc184)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44C7A0;
static void (* const ActNpc185)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44CA60;
static void (* const ActNpc186)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44CBE0;
static void (* const ActNpc187)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44CDB0;
static void (* const ActNpc188)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44D070;
static void (* const ActNpc189)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44D3A0;
static void (* const ActNpc190)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44D5E0;
static void (* const ActNpc191)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44D740;
static void (* const ActNpc192)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44DA00;
static void (* const ActNpc193)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44DE20;
static void (* const ActNpc194)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44DEA0;
static void (* const ActNpc195)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44DF10;
static void (* const ActNpc196)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44DF60;
static void (* const ActNpc197)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44E020;
static void (* const ActNpc198)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44E260;
static void (* const ActNpc199)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44E400;
static void (* const ActNpc200)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44E5F0;
static void (* const ActNpc201)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44EC40;
static void (* const ActNpc202)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44ECE0;
static void (* const ActNpc203)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44EE40;
static void (* const ActNpc204)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44F1F0;
static void (* const ActNpc205)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44F3E0;
static void (* const ActNpc206)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44F6D0;
static void (* const ActNpc207)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44FB40;
static void (* const ActNpc208)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x44FCB0;
static void (* const ActNpc209)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x450280;
static void (* const ActNpc210)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x450400;
static void (* const ActNpc211)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x450760;
static void (* const ActNpc212)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x450810;
static void (* const ActNpc213)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x450BF0;
static void (* const ActNpc214)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4512A0;
static void (* const ActNpc215)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x451430;
static void (* const ActNpc216)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4517F0;
static void (* const ActNpc217)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x451840;
static void (* const ActNpc218)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x451CA0;
static void (* const ActNpc219)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x451DA0;
static void (* const ActNpc220)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x451E90;
static void (* const ActNpc221)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x452000;
static void (* const ActNpc222)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x452470;
static void (* const ActNpc223)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4524E0;
static void (* const ActNpc224)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x452700;
static void (* const ActNpc225)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4528D0;
static void (* const ActNpc226)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x452A50;
static void (* const ActNpc227)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x452D10;
static void (* const ActNpc228)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x452D60;
static void (* const ActNpc229)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4530D0;
static void (* const ActNpc230)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x453190;
static void (* const ActNpc231)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x453260;
static void (* const ActNpc232)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4536F0;
static void (* const ActNpc233)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4539B0;
static void (* const ActNpc234)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x453E60;
static void (* const ActNpc235)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x453F20;
static void (* const ActNpc236)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x454310;
static void (* const ActNpc237)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4548B0;
static void (* const ActNpc238)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x454A00;
static void (* const ActNpc239)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x454DF0;
static void (* const ActNpc240)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x454F00;
static void (* const ActNpc241)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x455370;
static void (* const ActNpc242)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x455710;
static void (* const ActNpc243)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x455A10;
static void (* const ActNpc244)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x455AB0;
static void (* const ActNpc245)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x455C10;
static void (* const ActNpc246)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x455E00;
static void (* const ActNpc247)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x456110;
static void (* const ActNpc248)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x456F50;
static void (* const ActNpc249)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4570B0;
static void (* const ActNpc250)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x457180;
static void (* const ActNpc251)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x457470;
static void (* const ActNpc252)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x457570;
static void (* const ActNpc253)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4579D0;
static void (* const ActNpc254)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x457B00;
static void (* const ActNpc255)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x457D70;
static void (* const ActNpc256)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x458010;
static void (* const ActNpc257)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x458360;
static void (* const ActNpc258)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4585A0;
static void (* const ActNpc259)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4585F0;
static void (* const ActNpc260)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x458810;
static void (* const ActNpc261)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x458A70;
static void (* const ActNpc262)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x458C30;
static void (* const ActNpc263)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x458DF0;
static void (* const ActNpc264)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x459950;
static void (* const ActNpc265)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x459B30;
static void (* const ActNpc266)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x459C00;
static void (* const ActNpc267)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x459D80;
static void (* const ActNpc268)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45B3D0;
static void (* const ActNpc269)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45BCB0;
static void (* const ActNpc270)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45BF10;
static void (* const ActNpc271)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45C230;
static void (* const ActNpc272)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45C500;
static void (* const ActNpc273)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45C5A0;
static void (* const ActNpc274)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45C750;
static void (* const ActNpc275)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45CC80;
static void (* const ActNpc276)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45CEA0;
static void (* const ActNpc277)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45D780;
static void (* const ActNpc278)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45D930;
static void (* const ActNpc279)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45DCF0;
static void (* const ActNpc280)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45E110;
static void (* const ActNpc281)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45E360;
static void (* const ActNpc282)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45E4C0;
static void (* const ActNpc283)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45E950;
static void (* const ActNpc284)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x45F910;
static void (* const ActNpc285)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x460910;
static void (* const ActNpc286)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x460AE0;
static void (* const ActNpc287)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x460BB0;
static void (* const ActNpc288)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x460D70;
static void (* const ActNpc289)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4610D0;
static void (* const ActNpc290)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4614A0;
static void (* const ActNpc291)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x461800;
static void (* const ActNpc292)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4618B0;
static void (* const ActNpc293)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4618C0;
static void (* const ActNpc294)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4619E0;
static void (* const ActNpc295)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x461B90;
static void (* const ActNpc296)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x461E40;
static void (* const ActNpc297)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x461FD0;
static void (* const ActNpc298)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x462050;
static void (* const ActNpc299)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4623D0;
static void (* const ActNpc300)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4624E0;
static void (* const ActNpc301)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4625A0;
static void (* const ActNpc302)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x462890;
static void (* const ActNpc303)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x462AF0;
static void (* const ActNpc304)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x462C80;
static void (* const ActNpc305)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x462E00;
static void (* const ActNpc306)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x462F60;
static void (* const ActNpc307)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4630F0;
static void (* const ActNpc308)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4632B0;
static void (* const ActNpc309)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x463710;
static void (* const ActNpc310)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x463AC0;
static void (* const ActNpc311)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x464090;
static void (* const ActNpc312)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x464740;
static void (* const ActNpc313)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x464BB0;
static void (* const ActNpc314)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x465CC0;
static void (* const ActNpc315)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x465F60;
static void (* const ActNpc316)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4664B0;
static void (* const ActNpc317)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x466790;
static void (* const ActNpc318)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x466B80;
static void (* const ActNpc319)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x466E50;
static void (* const ActNpc320)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4670C0;
static void (* const ActNpc321)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4673F0;
static void (* const ActNpc322)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4676D0;
static void (* const ActNpc323)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x467C60;
static void (* const ActNpc324)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x467F40;
static void (* const ActNpc325)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x467FE0;
static void (* const ActNpc326)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x468230;
static void (* const ActNpc327)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x468830;
static void (* const ActNpc328)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x468990;
static void (* const ActNpc329)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4689E0;
static void (* const ActNpc330)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x468A90;
static void (* const ActNpc331)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x468D70;
static void (* const ActNpc332)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x468F50;
static void (* const ActNpc333)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x469140;
static void (* const ActNpc334)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x469290;
static void (* const ActNpc335)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x469430;
static void (* const ActNpc336)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x469610;
static void (* const ActNpc337)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4696B0;
static void (* const ActNpc338)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x469800;
static void (* const ActNpc339)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x469AA0;
static void (* const ActNpc340)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x469B40;
static void (* const ActNpc341)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46B240;
static void (* const ActNpc342)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46B340;
static void (* const ActNpc343)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46BD80;
static void (* const ActNpc344)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46BE10;
static void (* const ActNpc345)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46BF00;
static void (* const ActNpc346)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46C1D0;
static void (* const ActNpc347)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46C710;
static void (* const ActNpc348)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46C9B0;
static void (* const ActNpc349)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46CAC0;
static void (* const ActNpc350)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46CB50;
static void (* const ActNpc351)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46D340;
static void (* const ActNpc352)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46D5D0;
static void (* const ActNpc353)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46DBE0;
static void (* const ActNpc354)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46E110;
static void (* const ActNpc355)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46E280;
static void (* const ActNpc356)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46E480;
static void (* const ActNpc357)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46E730;
static void (* const ActNpc358)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46E870;
static void (* const ActNpc359)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46E9E0;
static void (* const ActNpc360)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46EA90;
// InitNpChar - 0x46EB30
static void (* const CS_InitNpChar)(void) = (void(*)(void))0x46EB30;
// LoadEvent - 0x46EB50
static BOOL (* const CS_LoadEvent)(const char *path_event) = (BOOL(*)(const char*))0x46EB50;
// SetUniqueParameter - 0x46EE50
static void (* const CS_SetUniqueParameter)(CS_NPCHAR *npc) = (void(*)(CS_NPCHAR*))0x46EE50;
// SetNpChar - 0x46EFD0
static void (* const CS_SetNpChar)(int object_ID, int x_pos, int y_pos, int a4, int a5, int facing_right, int a7, int object_RAM_index) = (void(*)(int, int, int, int, int, int, int, int))0x46EFD0;
// SetDestroyNpChar - 0x46F150
static void (* const CS_SetDestroyNpChar)(int x, int y, signed int w, int num) = (void(*)(int, int, int, int))0x46F150;
// SetDestroyNpCharUp - 0x46F200
static void (* const CS_SetDestroyNpCharUp)(int x, int y, signed int w, int num) = (void(*)(int, int, int, int))0x46F200;
// SetExpObjects - 0x46F2B0
static void (* const CS_SetExpObjects)(int x, int y, int exp) = (void(*)(int, int, int))0x46F2B0;
// SetBulletObject - 0x46F430
static BOOL(* const CS_SetBulletObject)(int x, int y, int val) = (BOOL(*)(int, int, int))0x46F430;
// SetLifeObject - 0x46F630
static BOOL(* const CS_SetLifeObject)(int x, int y, int val) = (BOOL(*)(int, int, int))0x46F630;
// VanishNpChar - 0x46F760
static void (* const CS_VanishNpChar)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x46F760;
// PutNpChar - 0x46F810
static void (* const CS_PutNpChar)(int fx, int fy) = (void(*)(int, int))0x46F810;
// ActNpChar - 0x46FA00
static void (* const CS_ActNpChar)(void) = (void(*)(void))0x46FA00;
// ChangeNpCharByEvent - 0x46FAB0
static void (* const CS_ChangeNpCharByEvent)(int code_event, int code_char, int dir) = (void(*)(int, int, int))0x46FAB0;
// ChangeCheckableNpCharByEvent - 0x46FD10
static void (* const CS_ChangeCheckableNpCharByEvent)(int code_event, int code_char, int dir) = (void(*)(int, int, int))0x46FD10;
// SetNpCharActionNo - 0x46FF90
static void (* const CS_SetNpCharActionNo)(int code_event, int code_char, int dir) = (void(*)(int, int, int))0x46FF90;
// MoveNpChar - 0x470060
static void (* const CS_MoveNpChar)(int code_event, int x, int y, int dir) = (void(*)(int, int, int, int))0x470060;
// BackStepMyChar - 0x470150
static void (* const CS_BackStepMyChar)(int code_event) = (void(*)(int))0x470150;
// DeleteNpCharEvent - 0x470250
static void (* const CS_DeleteNpCharEvent)(int code) = (void(*)(int))0x470250;
// DeleteNpCharCode - 0x4702D0
static void (* const CS_DeleteNpCharCode)(int code, BOOL bSmoke) = (void(*)(int, BOOL))0x4702D0;
// GetNpCharPosition - 0x470460
static void (* const CS_GetNpCharPosition)(int *x, int *y, int i) = (void(*)(int*, int*, int))0x470460;
// IsNpCharCode - 0x470490
static BOOL (* const CS_IsNpCharCode)(int code) = (BOOL(*)(int))0x470490;
// GetNpCharAlive - 0x4704F0
static BOOL (* const CS_GetNpCharAlive)(int code_event) = (BOOL(*)(int))0x4704F0;
// CountAliveNpChar - 0x470560
static int (* const CS_CountAliveNpChar)(void) = (int(*)(void))0x470560;
// JadgeHitNpCharBlock - 0x4705C0
static void (* const CS_JadgeHitNpCharBlock)(CS_NPCHAR* npc, int x, int y) = (void(*)(CS_NPCHAR*, int, int))0x4705C0;
// JudgeHitNpCharTriangleA - 0x470870
static void (* const CS_JudgeHitNpCharTriangleA)(CS_NPCHAR* npc, int x, int y) = (void(*)(CS_NPCHAR*, int, int))0x470870;
// JudgeHitNpCharTriangleB - 0x470970
static void (* const CS_JudgeHitNpCharTriangleB)(CS_NPCHAR* npc, int x, int y) = (void(*)(CS_NPCHAR*, int, int))0x470970;
// JudgeHitNpCharTriangleC - 0x470A70
static void (* const CS_JudgeHitNpCharTriangleC)(CS_NPCHAR* npc, int x, int y) = (void(*)(CS_NPCHAR*, int, int))0x470A70;
// JudgeHitNpCharTriangleD - 0x470B70
static void (* const CS_JudgeHitNpCharTriangleD)(CS_NPCHAR* npc, int x, int y) = (void(*)(CS_NPCHAR*, int, int))0x470B70;
// JudgeHitNpCharTriangleE - 0x470C70
static void (* const CS_JudgeHitNpCharTriangleE)(CS_NPCHAR* npc, int x, int y) = (void(*)(CS_NPCHAR*, int, int))0x470C70;
// JudgeHitNpCharTriangleF - 0x470D80
static void (* const CS_JudgeHitNpCharTriangleF)(CS_NPCHAR* npc, int x, int y) = (void(*)(CS_NPCHAR*, int, int))0x470D80;
// JudgeHitNpCharTriangleG - 0x470E90
static void (* const CS_JudgeHitNpCharTriangleG)(CS_NPCHAR* npc, int x, int y) = (void(*)(CS_NPCHAR*, int, int))0x470E90;
// JudgeHitNpCharTriangleH - 0x470FA0
static void (* const CS_JudgeHitNpCharTriangleH)(CS_NPCHAR* npc, int x, int y) = (void(*)(CS_NPCHAR*, int, int))0x470FA0;
// JudgeHitNpCharWater - 0x4710B0
static void (* const CS_JudgeHitNpCharWater)(CS_NPCHAR* npc, int x, int y) = (void(*)(CS_NPCHAR*, int, int))0x4710B0;
// HitNpCharMap - 0x471160
static void (* const CS_HitNpCharMap)(void) = (void(*)(void))0x471160;
// LoseNpChar - 0x471B80
static void (* const CS_LoseNpChar)(CS_NPCHAR* npc, BOOL bVanish) = (void(*)(CS_NPCHAR*, BOOL))0x471B80;
// HitNpCharBullet - 0x471D50
static void (* const CS_JudgeHitNpCharBullet)(void) = (void(*)(void))0x471D50;
// LoadNpcTable - 0x472400
static BOOL (* const CS_LoadNpcTable)(const char *path) = (BOOL(*)(const char*))0x472400;
// ReleaseNpcTable - 0x472710
static void (* const CS_ReleaseNpcTable)(void) = (void(*)(void))0x472710;
// InitBossChar - 0x472740
static void (* const CS_InitBossChar)(int code) = (void(*)(int))0x472740;
// PutBossChar - 0x472770
static void (* const CS_PutBossChar)(int fx, int fy) = (void(*)(int, int))0x472770;
// SetBossCharActNo - 0x472940
static void (* const CS_SetBossCharActNo)(int a) = (void(*)(int))0x472940;
// HitBossBullet - 0x472950
static void (* const CS_HitBossBullet)(void) = (void(*)(void))0x472950;
// ActBossChar_0 - 0x472FF0
static void (* const CS_ActBossChar_0)(void) = (void(*)(void))0x472FF0;
// ActBossChar - 0x473000
static void (* const CS_ActBossChar)(void) = (void(*)(void))0x473000;
// HitBossMap - 0x473080
static void (* const CS_HitBossMap)(void) = (void(*)(void))0x473080;
// Core boss
static void (* const CS_ActBossChar_Core_Face)(CS_NPCHAR *npc) = (void(*)(CS_NPCHAR*))0x4739B0;
static void (* const CS_ActBossChar_Core_Tail)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x473BD0;
static void (* const CS_ActBossChar_Core_Mini)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x473DE0;
static void (* const CS_ActBossChar_Core_Hit)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x474340;
static void (* const CS_ActBossChar_Core)(void) = (void(*)(void))0x474400;
// Undead Core boss
static void (* const CS_ActBossChar_Undead)(void) = (void(*)(void))0x4753D0;
static void (* const CS_ActBossCharA_Head)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x476790;
static void (* const CS_ActBossCharA_Tail)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4769A0;
static void (* const CS_ActBossCharA_Face)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x476B90;
static void (* const CS_ActBossCharA_Mini)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x476E50;
static void (* const CS_ActBossCharA_Hit)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x477230;
// Ballos boss
static void (* const CS_ActBossChar_Ballos)(void) = (void(*)(void))0x4772F0;
static void (* const CS_ActBossCharA_Eye)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x478AA0;
static void (* const CS_ActBossCharA_Body)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x478F20;
static void (* const CS_ActBossCharA_HITAI)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x478FE0;
static void (* const CS_ActBossCharA_HARA)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x479010;
// Balfrog boss
static void (* const CS_ActBossChar_Frog)(void) = (void(*)(void))0x479030;
static void (* const CS_ActBossChar02_01)(void) = (void(*)(void))0x47A6A0;
static void (* const CS_ActBossChar02_02)(void) = (void(*)(void))0x47A800;
// Ironhead boss
static void (* const CS_ActBossChar_Ironhead)(void) = (void(*)(void))0x47A8A0;
// Boss Life functions
static void (* const CS_InitBossLife)(void) = (void(*)(void))0x47B450;
static BOOL (* const CS_StartBossLife)(int code_event) = (BOOL(*)(int))0x47B460;
static BOOL(* const CS_StartBossLife2)(void) = (BOOL(*)(void))0x47B500;
static void (* const CS_PutBossLife)(void) = (void(*)(void))0x47B540;
// Omega boss
static void (* const CS_ActBossChar_Omega)(void) = (void(*)(void))0x47B6F0;
static void (* const CS_ActBoss01_12)(void) = (void(*)(void))0x47C380;
static void (* const CS_ActBoss01_34)(void) = (void(*)(void))0x47C4E0;
static void (* const CS_ActBoss01_5)(void) = (void(*)(void))0x47C7A0;
// Heavy Press boss
static void (* const CS_ActBossChar_Press)(void) = (void(*)(void))0x47C820;
// The Sisters boss
static void (* const CS_ActBossChar_Twin)(void) = (void(*)(void))0x47D170;
static void (* const CS_ActBossCharT_DragonBody)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x47DAA0;
static void (* const CS_ActBossCharT_DragonHead)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x47DF10;
// Monster X boss
static void (* const CS_ActBossChar_MonstX)(void) = (void(*)(void))0x47E6F0;
static void (* const CS_ActBossChar_03_01)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x47F710;
static void (* const CS_ActBossChar_03_02)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x480090;
static void (* const CS_ActBossChar_03_03)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4802A0;
static void (* const CS_ActBossChar_03_04)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x480550;
static void (* const CS_ActBossChar_03_face)(CS_NPCHAR* npc) = (void(*)(CS_NPCHAR*))0x4808C0;

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

// I literally have no idea what i'm doing?? Does this hook into the <MIM function or not??
// TSC part of <MIM
#define MIM_tsc_start (void*) 0x4225ED
#define MIM_tsc_end (void*) 0x422679

// MyChar part of <MIM
#define MIM_mychar_start (void*) 0x4154b8
#define MIM_mychar_end (void*) 0x4154C6