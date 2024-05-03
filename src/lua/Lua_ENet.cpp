#include <enet/enet.h>
#include "Lua.h"
#include "Lua_ENet.h"
#include <lua.hpp>
#include "../Main.h"
#include "ENet_FunctionDeclare.h"
#include "../ByteStream.h"
#include "../CommonNetplayVariables.h"

static int getServerHost(lua_State* L)
{
    // Get the ENetPeer* toServer from wherever it's stored
    ENetPeer* toserverL = toServer;

    // Create a new userdata and allocate memory for the pointer
    ENetPeer** ud = (ENetPeer**)lua_newuserdata(L, sizeof(ENetPeer*));

    // Assign the pointer value to the userdata
    *ud = toserverL;

    // Set the metatable for the userdata (optional)
    // luaL_setmetatable(L, "ENetPeerMetaTable"); // You need to define the metatable

    return 1; // Return the number of values pushed onto the Lua stack
}

int SendPacketID(lua_State* L)
{
    int packetCode = (int)luaL_checknumber(L, 1);
    uint8_t packet[8];
    ByteStream packetData(packet, 8);


    packetData.WriteLE32(gNetVersion);
    packetData.WriteLE32(packetCode);

    //Send packet
    auto definePacket = enet_packet_create(packet, 8, ENET_PACKET_FLAG_RELIABLE);

    if (enet_peer_send(toServer, 0, definePacket) < 0)
        KillClient();

    return 0;
}

// Function to send a packet with variable-length data
int SendPacketCustom(lua_State* L)
{
    int mainCode = 4;
    int packetCode = (int)luaL_checknumber(L, 1);

    // Create a dynamic buffer to hold the packet data
    size_t dataSize = 0;
    const char* packetData = luaL_checklstring(L, 2, &dataSize);

    // Calculate the total size of the packet (packet code + size + data)
    size_t packetSize = sizeof(gNetVersion) + sizeof(mainCode) + sizeof(packetCode) + sizeof(uint32_t) + dataSize;

    // Allocate memory for the packet
    uint8_t* packet = new uint8_t[packetSize];
    ByteStream packetDataStream(packet, packetSize);

    // Write packet version, packet code, and data size
    packetDataStream.WriteLE32(gNetVersion);
    packetDataStream.WriteLE32(mainCode);
    packetDataStream.WriteLE32(packetCode);
    packetDataStream.WriteLE32(static_cast<uint32_t>(dataSize));

    // Write the actual data
    packetDataStream.Write(packetData, 1, dataSize);

    // Send packet
    auto definePacket = enet_packet_create(packet, packetSize, ENET_PACKET_FLAG_RELIABLE);

    if (enet_peer_send(toServer, 0, definePacket) < 0)
        KillClient();

    // Free memory allocated for the packet
    delete[] packet;

    return 0;
}

// Function table for ENet functions
FUNCTION_TABLE EnetFunctionTable[FUNCTION_TABLE_ENET_SIZE] = {
    {"sendPacketID", SendPacketID},
    {"sendSpecialPacket", SendPacketCustom}
};
