#include "Lua_ENet.h"
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
#include "../CommonNetplayVariables.h"

#define FUNCTION_TABLE_NETPLAY_SIZE 7

static int lua_GetNetVersion(lua_State* L)
{
	lua_pushnumber(L, gNetVersion);
	return 1;
}

static int lua_SetNetVersion(lua_State* L)
{
	int ver = (int)luaL_checknumber(L, 1);
	gNetVersion = ver;
	return 0;
}

static int lua_GetPacketCode(lua_State* L)
{
	// Get the event type from Lua stack
	lua_pushnumber(L, packetcode);
	return 1;
}

static int lua_GetSpecialPacketCode(lua_State* L)
{
	// Get the event type from Lua stack
	lua_pushnumber(L, specialPacketCode);
	return 1;
}

static int lua_GetSpecialPacketData(lua_State* L) {
	if (specialData == nullptr)
		lua_pushstring(L, "No data");
	else
		lua_pushstring(L, specialData);

	return 1;
}

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
	{"Enabled", lua_NetworkingEnabled},
	{"SetNetVersion", lua_SetNetVersion},
	{"GetNetVersion", lua_GetNetVersion},
	{"eventCode", lua_GetPacketCode},
	{"specialEventCode", lua_GetSpecialPacketCode},
	{"GetSpecialPacketData", lua_GetSpecialPacketData}
};

void SetNetplayGlobalString()
{

}

void PushNetplayMetadata()
{
	
}

void SetNetplayLua()
{
	PushFunctionTable(gL, "ENet", EnetFunctionTable, FUNCTION_TABLE_ENET_SIZE, TRUE);
	PushFunctionTable(gL, "Netplay", NetplayFunctionTable, FUNCTION_TABLE_NETPLAY_SIZE, TRUE);
}