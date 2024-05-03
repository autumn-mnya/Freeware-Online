#include <enet/enet.h>
#include "Lua.h"
#include "Lua_ENet.h"
#include <lua.hpp>
#include "../Main.h"
#include "ENet_FunctionDeclare.h"
#include "../ByteStream.h"
#include "../CommonNetplayVariables.h"

ENetAddress hostAddress;

// Function to create an ENet host
static int createHost(lua_State* L) {
    const char* address = luaL_checkstring(L, 1);
    enet_uint16 port = luaL_checkinteger(L, 2);
    size_t peerLimit = luaL_checkinteger(L, 3);
    size_t channelLimit = luaL_checkinteger(L, 4);
    enet_uint32 incomingBandwidth = luaL_checkinteger(L, 5);
    enet_uint32 outgoingBandwidth = luaL_checkinteger(L, 6);

    ENetAddress enetAddress;
    enetAddress.host = ENET_HOST_ANY;
    enetAddress.port = port;

    ENetHost* host = enet_host_create(&hostAddress, peerLimit, channelLimit, incomingBandwidth, outgoingBandwidth);
    if (host) {
        lua_pushlightuserdata(L, host);
        return 1;
    }
    else {
        lua_pushnil(L);
        return 1;
    }
}

// Function to create an ENet address
static int createAddress(lua_State* L) {
    const char* host = luaL_checkstring(L, 1);
    enet_uint16 port = luaL_checkinteger(L, 2);

    ENetAddress enetAddress;
    if (enet_address_set_host(&hostAddress, host) == 0) {
        enetAddress.port = port;
        lua_pushlightuserdata(L, &hostAddress);
        return 1;
    }
    else {
        lua_pushnil(L);
        return 1;
    }
}

// Function to service the host
static int hostService(lua_State* L) {
    ENetHost* host = (ENetHost*)lua_touserdata(L, 1);
    enet_uint32 timeout = luaL_checkinteger(L, 2);

    ENetEvent event;
    if (enet_host_service(host, &event, timeout) > 0) {
        lua_pushinteger(L, event.type);
        return 1;
    }
    else {
        lua_pushnil(L);
        return 1;
    }
}

// Function to send a packet to a peer
static int peerSend(lua_State* L) {
    ENetPeer* peer = (ENetPeer*)lua_touserdata(L, 1);
    enet_uint8 channelID = luaL_checkinteger(L, 2);
    size_t length;
    const char* data = luaL_checklstring(L, 3, &length);
    enet_uint32 flags = luaL_optinteger(L, 4, 0);

    ENetPacket* packet = enet_packet_create(data, length, flags);
    if (packet) {
        enet_peer_send(peer, channelID, packet);
    }
    return 0;
}

// Function to receive a packet from a peer
static int peerReceive(lua_State* L) {
    ENetPeer* peer = (ENetPeer*)lua_touserdata(L, 1);
    ENetPacket* packet = enet_peer_receive(peer, 0);

    if (packet) {
        lua_pushlstring(L, (const char*)packet->data, packet->dataLength);
        enet_packet_destroy(packet);
        return 1;
    }
    else {
        lua_pushnil(L);
        return 1;
    }
}

// Function to disconnect a peer
static int peerDisconnect(lua_State* L) {
    ENetPeer* peer = (ENetPeer*)lua_touserdata(L, 1);
    enet_uint32 data = luaL_optinteger(L, 2, 0);
    enet_peer_disconnect(peer, data);
    return 0;
}

// Function to reset a peer
static int peerReset(lua_State* L) {
    ENetPeer* peer = (ENetPeer*)lua_touserdata(L, 1);
    enet_peer_reset(peer);
    return 0;
}

// Function to create a packet
static int packetCreate(lua_State* L) {
    size_t length;
    const char* data = luaL_checklstring(L, 1, &length);  // Retrieve packet data as string
    enet_uint32 flags = luaL_optinteger(L, 2, 0);

    ENetPacket* packet = enet_packet_create(data, length, flags);
    if (packet) {
        lua_pushlstring(L, data, length);  // Push the packet data to Lua as a string
        return 1;
    }
    else {
        lua_pushnil(L);
        return 1;
    }
}

// Function to destroy a packet
static int packetDestroy(lua_State* L) {
    ENetPacket* packet = (ENetPacket*)lua_touserdata(L, 1);
    enet_packet_destroy(packet);
    return 0;
}

// Function to get the data from a packet
static int packetGetData(lua_State* L) {
    ENetPacket* packet = (ENetPacket*)lua_touserdata(L, 1);
    lua_pushlstring(L, (const char*)packet->data, packet->dataLength);
    return 1;
}

// Function to get the length of a packet
static int packetGetLength(lua_State* L) {
    ENetPacket* packet = (ENetPacket*)lua_touserdata(L, 1);
    lua_pushinteger(L, packet->dataLength);
    return 1;
}

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
    {"createHost", createHost},
    {"createAddress", createAddress},
    {"hostService", hostService},
    {"peerSend", peerSend},
    {"peerReceive", peerReceive},
    {"peerDisconnect", peerDisconnect},
    {"peerReset", peerReset},
    {"packetCreate", packetCreate},
    {"packetDestroy", packetDestroy},
    {"packetGetData", packetGetData},
    {"packetGetLength", packetGetLength},
    {"getServerHost", getServerHost},
    {"sendPacketID", SendPacketID},
    {"sendSpecialPacket", SendPacketCustom}
};
