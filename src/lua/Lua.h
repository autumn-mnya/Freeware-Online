#pragma once

#include <Windows.h>
#include "../cave_story.h"

extern "C"
{
#include <lua.h>
}

extern const char* LuaModName;

typedef enum LuaDataType
{
	TYPE_NUMBER = 1,
	TYPE_STRING = 2,
	TYPE_OTHER_RECT = 3,
	TYPE_RECT = 4,
	TYPE_COLOR = 5,
	TYPE_SURFACE = 6,
	TYPE_NPC = 7,
	TYPE_PIXEL = 8
} LuaDataType;

typedef struct STRUCT_TABLE
{
	const char* name;
	size_t offset;
	LuaDataType type;
} STRUCT_TABLE;

typedef struct FUNCTION_TABLE
{
	const char* name;
	lua_CFunction f;
} FUNCTION_TABLE;

typedef struct METATABLE_TABLE
{
	const char* name;
	lua_CFunction index;
	lua_CFunction newindex;
} METATABLE_TABLE;

void SetNetplayGlobalString();
void PushNetplayMetadata();
void SetNetplayLua();