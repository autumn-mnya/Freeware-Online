// Mod loader for Freeware Cave Story
// Public domain

#include <ddraw.h>
#include <windows.h>

#define BULLET_MAX 0x40
#define CARET_MAX 0x40

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
// VersionDialog

// DebugMuteDialog

// DebugSaveDialog

// QuitDialog

// SetClientOffset - 0x40B320
static void(* const CS_SetClientOffset)(int width, int height) = (void(*)(int, int))0x40B320;
// Flip_SystemTask - 0x40B340
static BOOL (* const CS_Flip_SystemTask)(HWND hWnd) = (BOOL(*)(HWND))0x40B340;
// StartDirectDraw - 0x40B340
static BOOL (* const CS_StartDirectDraw)(HWND hWnd, int lMagnification, int lColourDepth) = (BOOL(*)(HWND hWnd, int, int))0x40B340;
// EndDirectDraw

// ReleaseSurface - 0x40B7A0
static void (* const CS_ReleaseSurface)(int s) = (void(*)(int))0x40B7A0;
// MakeSurface_Resource

// MakeSurface_File - 0x40BAC0
static BOOL(* const CS_MakeSurface_File)(const char* name, int surf_no) = (BOOL(*)(const char*, int))0x40BAC0;
// ReloadBitmap_Resource

// ReloadBitmap_File - 0x40BFD0
static BOOL(* const CS_ReloadBitmap_File)(const char* name, int surf_no) = (BOOL(*)(const char*, int))0x40BFD0;
// MakeSurface_Generic - 0x40C1D0
static BOOL(* const CS_MakeSurface_Generic)(int bxsize, int bysize, int surf_no) = (BOOL(*)(int, int, int))0x40C1D0;
// BackupSurface

// PutBitmap3 - 0x40C3C0
static void (* const CS_PutBitmap3)(const RECT*, int, int, const RECT*, CS_SurfaceID) = (void(*)(const RECT*, int, int, const RECT*, CS_SurfaceID))0x40C3C0;
// PutBitmap4 - 0x40C5B0
static void (* const CS_PutBitmap4)(const RECT*, int, int, const RECT*, CS_SurfaceID) = (void(*)(const RECT*, int, int, const RECT*, CS_SurfaceID))0x40C5B0;
// Surface2Surface

// GetCortBoxColor

// CortBox - 0x40C9E0
static void (* const CS_CortBox)(RECT* dst_rect, int colour) = (void(*)(RECT*, int))0x40C9E0;
// CortBox2 - 0x40CA80
static void (* const CS_CortBox2)(RECT* dst_rect, int colour, CS_SurfaceID surf_no) = (void(*)(RECT*, int, CS_SurfaceID))0x40CA80;
// out

// RestoreSurfaces - 0x40CB60
static int (* const CS_RestoreSurfaces)(void) = (int(*)(void))0x40CB60;
// InitTextObject

// PutText - 0x40CE00
static void (* const CS_PutText)(int x, int y, const char* text, unsigned int colour) = (void(*)(int, int, const char*, unsigned int))0x40CE00;
// PutText2 - 0x40CEB0
static void (* const CS_PutText2)(int x, int y, const char* text, unsigned int colour, CS_SurfaceID) = (void(*)(int, int, const char*, unsigned int, CS_SurfaceID))0x40CEB0;
// EndTextObject

// ActionStripper

// PutStripper

// SetStripper

// RestoreStripper

// ActionIllust

// PutIllust

// ReloadIllust

// InitCreditScript

// ReleaseCreditScript

// StartCreditScript - 0x40D440
static BOOL(* const CS_StartCreditScript)(void) = (BOOL(*)(void))0x40D440;
// ActionCredit

// ActionCredit_Read

// GetScriptNumber

// SetCreditIllust

// CutCreditIllust

// Scene_DownIsland

// Call_Escape

// InitFade

// SetFadeMask

// ClearFade

// StartFadeOut

// StartFadeIn

// ProcFade

// PutFade

// GetFadeActive

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
// InitFlash

// SetFlash

// ActFlash_Explosion

// ActFlash_Flash

// ActFlash

// PutFlash

// ResetFlash

// MoveFrame3

// GetFramePosition - 0x40F020
static void (* const CS_GetFramePosition)(int* fx, int* fy) = (void(*)(int*, int*))0x40F020;
// SetFramePosition

// SetFrameMyChar

// SetFrameTargetMyChar

// SetFrameTargetNpChar

// SetFrameTargetBoss

// SetQuake

// SetQuake2

// ResetQuake

// Random - 0x40F350
static int (* const CS_Random)(int min, int max) = (int(*)(int, int))0x40F350;
// PutNumber4 - 0x40F380
static void (* const CS_PutNumber4)(int x, int y, int, int) = (void(*)(int, int, int, int))0x40F380;
// Game

// ModeOpening

// ModeTitle

// ModeAction

// GetCompileDate

// GetCompileVersion

// OpenSoundVolume

// DeleteLog

// WriteLog

// GetDateLimit

// IsKeyFile

// GetFileSizeLong

// ErrorLog

// IsShiftJIS

// CenteringWindowByParent

// LoadWindowRect

// SaveWindowRect

// IsEnableBitmap

// LoadGenericData

// ReleaseDirectInput

// ActivateDirectInput

// InitDirectInput

// HookAllDirectInputDevices

// EnumDevices_Callback

// GetJoystickStatus

// ResetJoystickStatus

// GetTrg

// SetWindowName

// PutFramePerSecound

// CountFramePerSecound

// WinMain

// InactiveWindow

// ActiveWindow

// DragAndDropHandler

// WindowProcedure

// SystemTask

// JoystickProc

// InitMapData2

// LoadMapData2

// LoadAttributeData

// EndMapData

// ReleasePartsImage

// GetMapData

// GetAttribute

// DeleteMapParts

// ShiftMapParts

// ChangeMapParts

// PutStage_Back

// PutStage_Front

// PutMapDataVector

// ReadyMapName

// PutMapName

// StartMapName

// RestoreMapName

// WriteMinimMapLine

// MiniMapLoop

// IsMapping

// StartMapping

// SetMapping

// InitMyChar

// AnimationMyChar

// ShowMyChar

// PutMyChar - 0x415250
static void (* const CS_PutMyChar)(int camera_x, int camera_y) = (void(*)(int, int))0x415250;
// ActMyChar_Normal

// ActMyChar_Stream

// ActMyChar

// AirProcess

// GetMyCharPosition

// SetMyCharPosition

// MoveMyChar

// ZeroMyCharXMove

// GetUnitMyChar

// SetMyCharDirect

// ChangeMyUnit

// PitMyChar

// EquipItem

// ResetCheck

// SetNoise

// CutNoise

// ResetNoise

// SleepNoise

// ResetMyCharFlag

// JudgeHitMyCharBlock

// PutlittleStar

// JudgeHitMyCharTriangleA

// JudgeHitMyCharTriangleB

// JudgeHitMyCharTriangleC

// JudgeHitMyCharTriangleD

// JudgeHitMyCharTriangleE

// JudgeHitMyCharTriangleF

// JudgeHitMyCharTriangleG

// JudgeHitMyCharTriangleH

// JudgeHitMyCharWater

// JudgeHitMyCharDamage

// JudgeHitMyCharDamageW

// JudgeHitMyCharVectLeft

// JudgeHitMyCharVectUp

// JudgeHitMyCharVectRight

// JudgeHitMyCharVectDown

// HitMyCharMap

// JudgeHitMyCharNPC

// JudgeHitMyCharNPC3

// JudgeHitMyCharNPC4

// HitMyCharNpChar

// HitMyCharBoss

// AddExpMyChar

// ZeroExpMyChar

// IsMaxExpMyChar

// DamageMyChar

// ZeroArmsEnergy_All

// AddBulletMyChar

// AddLifeMyChar

// AddMaxLifeMyChar

// PutArmsEnergy

// PutActiveArmsList

// PutMyLife

// PutMyAir - 0x41A350
static void (* const CS_PutMyAir)(int x, int y) = (void(*)(int, int))0x41A350;
// PutTimeCounter

// SaveTimeCounter

// LoadTimeCounter

// MakeSoundObject8

// ChangeOrganFrequency

// ChangeOrganPan

// ChangeOrganVolume

// PlayOrganObject

// ReleaseOrganyaObject

// InitWaveData100

// MakeOrganyaWave

// ChangeDramFrequency

// ChangeDramPan

// ChangeDramVolume

// PlayDramObject

// OrgData::OrgData

// OrgData::InitOrgData

// OrgData::SetMusicInfo

// OrgData::NoteAlloc

// OrgData::ReleaseNote

// OrgData::InitMusicData

// OrgData::GetMusicInfo

// InitMMTimer

// StartTimer

// TimerProc

// QuitMMTimer

// OrgData::PlayData

// OrgData::SetPlayerPointer

// StartOrganya

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
// EndOrganya

// MakeWaveTables

// MakePixelWaveData

// IsProfile

// SaveProfile

// LoadProfile

// InitializeGame

// ClearPermitStage

// AddPermitStage

// SubPermitStage

// MoveStageSelectCursor

// PutStageSelectObject

// StageSelectLoop

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
// InitDirectSound

// EndDirectSound

// InitSoundObject

// LoadSoundObject

// PlaySoundObject

// ChangeSoundFrequency

// ChangeSoundVolume

// ChangeSoundPan

// MakePixToneObject

// TransferStage

// ChangeMusic - 0x420EE0
static void (* const CS_ChangeMusic)(int music_id) = (void(*)(int))0x420EE0;
// ReCallMusic - 0x420F50
static void (* const CS_ReCallMusic)(void) = (void(*)(void))0x420F50;
// InitStar

// ActStar

// PutStar

// InitTextScript2

// EndTextScript

// EncryptionBinaryData2

// LoadTextScript2

// LoadTextScript_Stage

// GetTextScriptPath

// GetTextScriptNo

// StartTextScript

// JumpTextScript

// StopTextScript

// CheckNewLine

// SetNumberTextScript

// ClearTextLine

// PutTextScript

// TextScriptProc - 0x422510
static void (* const CS_TextScriptProc)(void) = (void(*)(void))0x422510;
// RestoreTextScript

// InitTriangleTable

// GetSin

// GetCos

// GetArktan

// ClearValueView

// SetValueView

// ActValueView

// PutValueView

// ActNpc000

// ActNpc002

// ActNpc003

// ActNpc004

// ActNpc005

// ActNpc006

// ActNpc007

// ActNpc008

// ActNpc009

// ActNpc010

// ActNpc011

// ActNpc012

// ActNpc013

// ActNpc014

// ActNpc015

// ActNpc016

// ActNpc017

// ActNpc018

// ActNpc019

// ActNpc020

// ActNpc021

// ActNpc022

// ActNpc023

// ActNpc024

// ActNpc025

// ActNpc026

// ActNpc027

// ActNpc028

// ActNpc029

// ActNpc030

// ActNpc031

// ActNpc032

// ActNpc033

// ActNpc034

// ActNpc035

// ActNpc036

// ActNpc037

// ActNpc038

// ActNpc039

// ActNpc040

// ActNpc041

// ActNpc042

// ActNpc043

// ActNpc044

// ActNpc045

// ActNpc046

// ActNpc047

// ActNpc048

// ActNpc049

// ActNpc050

// ActNpc051

// ActNpc052

// ActNpc053

// ActNpc054

// ActNpc055

// ActNpc056

// ActNpc057

// ActNpc058

// ActNpc059

// ActNpc060

// ActNpc061

// ActNpc062

// ActNpc063

// ActNpc064

// ActNpc065

// ActNpc066

// ActNpc067

// ActNpc068

// ActNpc069

// ActNpc070

// ActNpc071

// ActNpc072

// ActNpc073

// ActNpc074

// ActNpc075

// ActNpc076

// ActNpc077

// ActNpc078

// ActNpc079

// ActNpc080

// ActNpc081

// ActNpc082

// ActNpc083

// ActNpc084

// ActNpc085

// ActNpc086

// ActNpc087

// ActNpc088

// ActNpc089

// ActNpc090

// ActNpc091

// ActNpc092

// ActNpc093

// ActNpc094

// ActNpc095

// ActNpc096

// ActNpc097

// ActNpc098

// ActNpc099

// ActNpc100

// ActNpc101

// ActNpc102

// ActNpc103

// ActNpc104

// ActNpc105

// ActNpc106

// ActNpc107

// ActNpc108

// ActNpc109

// ActNpc110

// ActNpc111

// ActNpc112

// ActNpc113

// ActNpc114

// ActNpc115

// ActNpc116

// ActNpc117

// ActNpc118

// ActNpc119

// ActNpc120

// ActNpc121

// ActNpc122

// ActNpc123

// ActNpc124

// ActNpc125

// ActNpc126

// ActNpc127

// ActNpc128

// ActNpc129

// ActNpc130

// ActNpc131

// ActNpc132

// ActNpc133

// ActNpc134

// ActNpc135

// ActNpc136

// ActNpc137

// ActNpc138

// ActNpc139

// ActNpc140

// ActNpc141

// ActNpc142

// ActNpc143

// ActNpc144

// ActNpc145

// ActNpc146

// ActNpc147

// ActNpc148

// ActNpc149

// ActNpc150

// ActNpc151

// ActNpc152

// ActNpc153

// ActNpc154

// ActNpc155

// ActNpc156

// ActNpc157

// ActNpc158

// ActNpc159

// ActNpc160

// ActNpc161

// ActNpc162

// ActNpc163

// ActNpc164

// ActNpc165

// ActNpc166

// ActNpc167

// ActNpc168

// ActNpc169

// ActNpc170

// ActNpc171

// ActNpc172

// ActNpc173

// ActNpc174

// ActNpc175

// ActNpc176

// ActNpc177

// ActNpc178

// ActNpc179

// ActNpc180

// ActNpc181

// ActNpc182

// ActNpc183

// ActNpc184

// ActNpc185

// ActNpc186

// ActNpc187

// ActNpc188

// ActNpc189

// ActNpc190

// ActNpc191

// ActNpc192

// ActNpc193

// ActNpc194

// ActNpc195

// ActNpc196

// ActNpc197

// ActNpc198

// ActNpc199

// ActNpc200

// ActNpc201

// ActNpc202

// ActNpc203

// ActNpc204

// ActNpc205

// ActNpc206

// ActNpc207

// ActNpc208

// ActNpc209

// ActNpc210

// ActNpc211

// ActNpc212

// ActNpc213

// ActNpc214

// ActNpc215

// ActNpc216

// ActNpc217

// ActNpc218

// ActNpc219

// ActNpc220

// ActNpc221

// ActNpc222

// ActNpc223

// ActNpc224

// ActNpc225

// ActNpc226

// ActNpc227

// ActNpc228

// ActNpc229

// ActNpc230

// ActNpc231

// ActNpc232

// ActNpc233

// ActNpc234

// ActNpc235

// ActNpc236

// ActNpc237

// ActNpc238

// ActNpc239

// ActNpc240

// ActNpc241

// ActNpc242

// ActNpc243

// ActNpc244

// ActNpc245

// ActNpc246

// ActNpc247

// ActNpc248

// ActNpc249

// ActNpc250

// ActNpc251

// ActNpc252

// ActNpc253

// ActNpc254

// ActNpc255

// ActNpc256

// ActNpc257

// ActNpc258

// ActNpc259

// ActNpc260

// ActNpc261

// ActNpc262

// ActNpc263

// ActNpc264

// ActNpc265

// ActNpc266

// ActNpc267

// ActNpc268

// ActNpc269

// ActNpc270

// ActNpc271

// ActNpc272

// ActNpc273

// ActNpc274

// ActNpc275

// ActNpc276

// ActNpc277

// ActNpc278

// ActNpc279

// ActNpc280

// ActNpc281

// ActNpc282

// ActNpc283

// ActNpc284

// ActNpc285

// ActNpc286

// ActNpc287

// ActNpc288

// ActNpc289

// ActNpc290

// ActNpc291

// ActNpc292

// ActNpc293

// ActNpc294

// ActNpc295

// ActNpc296

// ActNpc297

// ActNpc298

// ActNpc299

// ActNpc300

// ActNpc301

// ActNpc302

// ActNpc303

// ActNpc304

// ActNpc305

// ActNpc306

// ActNpc307

// ActNpc308

// ActNpc309

// ActNpc310

// ActNpc311

// ActNpc312

// ActNpc313

// ActNpc314

// ActNpc315

// ActNpc316

// ActNpc317

// ActNpc318

// ActNpc319

// ActNpc320

// ActNpc321

// ActNpc322

// ActNpc323

// ActNpc324

// ActNpc325

// ActNpc326

// ActNpc327

// ActNpc328

// ActNpc329

// ActNpc330

// ActNpc331

// ActNpc332

// ActNpc333

// ActNpc334

// ActNpc335

// ActNpc336

// ActNpc337

// ActNpc338

// ActNpc339

// ActNpc340

// ActNpc341

// ActNpc342

// ActNpc343

// ActNpc344

// ActNpc345

// ActNpc346

// ActNpc347

// ActNpc348

// ActNpc349

// ActNpc350

// ActNpc351

// ActNpc352

// ActNpc353

// ActNpc354

// ActNpc355

// ActNpc356

// ActNpc357

// ActNpc358

// ActNpc359

// ActNpc360

// InitNpChar

// LoadEvent

// SetUniqueParameter

// SetNpChar - 0x46EFD0
static void (* const CS_SetNpChar)(int object_ID, int x_pos, int y_pos, int a4, int a5, int facing_right, int a7, int object_RAM_index) = (void(*)(int, int, int, int, int, int, int, int))0x46EFD0;
// SetDestroyNpChar - 0x46F150
static void (* const CS_SetDestroyNpChar)(int x, int y, signed int range, int count) = (void(*)(int, int, int, int))0x46F150;
// SetDestroyNpCharUp

// SetExpObjects

// SetBulletObject

// SetLifeObject

// VanishNpChar

// PutNpChar

// ActNpChar - 0x46FA00
static void (* const CS_ActNpChar)(void) = (void(*)(void))0x46FA00;
// ChangeNpCharByEvent

// ChangeCheckableNpCharByEvent

// SetNpCharActionNo

// MoveNpChar

// BackStepMyChar

// DeleteNpCharEvent - 0x470250
static void (* const CS_DeleteNpCharEvent)(int code) = (void(*)(int))0x470250;
// DeleteNpCharCode - 0x4702D0
static void (* const CS_DeleteNpCharCode)(int code, BOOL bSmoke) = (void(*)(int, BOOL))0x4702D0;
// GetNpCharPosition

// IsNpCharCode

// GetNpCharAlive

// CountAliveNpChar

// JadgeHitNpCharBlock

// JudgeHitNpCharTriangleA

// JudgeHitNpCharTriangleB

// JudgeHitNpCharTriangleC

// JudgeHitNpCharTriangleD

// JudgeHitNpCharTriangleE

// JudgeHitNpCharTriangleF

// JudgeHitNpCharTriangleG

// JudgeHitNpCharTriangleH

// JudgeHitNpCharWater

// HitNpCharMap

// LoseNpChar - 0x471B80
static void (* const CS_LoseNpChar)(CS_NPCHAR* npc, BOOL bVanish) = (void(*)(CS_NPCHAR*, BOOL))0x471B80;
// HitNpCharBullet

// LoadNpcTable

// ReleaseNpcTable

// InitBossChar

// PutBossChar

// SetBossCharActNo

// HitBossBullet

// ActBossChar_0

// ActBossChar

// HitBossMap

// ActBossChar_Core_Face

// ActBossChar_Core_Tail

// ActBossChar_Core_Mini

// ActBossChar_Core_Hit

// ActBossChar_Core

// ActBossChar_Undead

// ActBossCharA_Head

// ActBossCharA_Tail

// ActBossCharA_Face

// ActBossCharA_Mini

// ActBossCharA_Hit

// ActBossChar_Ballos

// ActBossChar_Eye

// ActBossChar_Body

// ActBossChar_HITAI

// ActBossChar_HARA

// ActBossChar_Frog

// ActBossChar02_01

// ActBossChar_Ironhead

// InitBossLife

// StartBossLife

// StartBossLife2

// PutBossLife

// ActBossChar_Omega

// ActBoss01_12

// ActBoss01_34

// ActBoss01_5

// ActBossChar_Press

// ActBossChar_Twin

// ActBossCharT_DragonBody

// ActBossCharT_DragonHead

// ActBossChar_MonstX

// ActBossChar_03_01

// ActBossChar_03_02

// ActBossChar_03_03

// ActBossChar_03_04

// ActBossChar_03_face






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