#pragma once

#include <enet/enet.h>

extern ENetPeer* toServer;

ENetPeer* ReturnToServer();
void KillClient();