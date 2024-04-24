#include <Windows.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "Lua.h"


#include "../main.h"
#include "../mod_loader.h"
#include "../cave_story.h"

#include "../AutPI.h"
#include "../Networking.h"
#include "../NetworkDefine.h"

#define FUNCTION_TABLE_NETPLAY_SIZE 2

static int lua_InServer(lua_State* L)
{
	if (InServer())
		lua_pushboolean(L, 1);
	else
		lua_pushboolean(L, 0);

	return 1;
}

static int lua_NetworkingEnabled(lua_State* L)
{
	if (networking)
		lua_pushboolean(L, 1);
	else
		lua_pushboolean(L, 0);

	return 1;
}

FUNCTION_TABLE NetplayFunctionTable[FUNCTION_TABLE_NETPLAY_SIZE] =
{
	{"InServer", lua_InServer},
	{"Enabled", lua_NetworkingEnabled}
};

void SetNetplayGlobalString()
{

}

void PushNetplayMetadata()
{

}

void SetNetplayLua()
{
	PushFunctionTable(gL, "Netplay", NetplayFunctionTable, FUNCTION_TABLE_NETPLAY_SIZE, TRUE);
}