#pragma once
#include <stdint.h>
#include "NetworkDefine.h"

extern VIRTUAL_PLAYER gVirtualPlayers[MAX_CLIENTS];

extern unsigned int gLastChatMessage;

bool InitNetworking();
void QuitNetworking();
bool JoinServer(const char *ip, const char *port, const char *name);
void KillClient();
void HandleClient();
void PutVirtualPlayers(int fx, int fy);
bool IsHosting();
bool InServer();
bool ConnectedServer();
void SendChatMessage(const char *name, const char *text);
void ClearChat();
void PrintChat(const char *text);
void PutServer();
char *GetProfileName();
void LoadMySkin();
