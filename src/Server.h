#pragma once
int HandleServerSynchronous(void *ptr);
bool StartServer(const char* ip, const char *port);
void KillServer();
bool IsHosting();
void BroadcastChatMessage(const char *text);
