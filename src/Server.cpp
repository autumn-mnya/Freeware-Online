#include <enet/enet.h>
#include <thread>
#include <string>
#include "Server.h"
#include "NetworkDefine.h"
#include "ByteStream.h"

ENetHost *host;
ENetAddress hostAddress;
CLIENT clients[MAX_CLIENTS];

//Functions needed for getting ENetAddress from IP and port
static int ConvertIpToAddress(ENetAddress *address, const char *name)
{
	enet_uint8 vals [4] = {0, 0, 0, 0};
	for (int i = 0; i < 4; i++)
	{
		const char * next = name + 1;
		if (*name != '0')
		{
			long val = strtol(name, (char**)&next, 10);
			if (val < 0 || val > 0xFF || next == name || next - name > 3)
				return -1;
			vals[i] = (enet_uint8)val;
		}

		if (*next != (i < 3 ? '.' : '\0'))
			return -1;
		name = next + 1;
	}
	
	memcpy(&address->host, vals, sizeof(enet_uint32));
	address->host = address->host; //There was an endian swap where needed here
	return 0;
}

static bool VerifyPort(const char *port)
{
	for (int i = 0; port[i]; i++)
	{
		if (port[i] < '0' || port[i] > '9')
			return false;
	}
	
	return true;
}

//Start hosting a server
std::thread* ServerThread;
bool toEndThread = false;

void HandleServerEvent(ENetEvent event)
{
	switch (event.type)
	{
		case ENET_EVENT_TYPE_CONNECT:
			//Add peer to client-list
			for (int i = 0; i < MAX_CLIENTS; i++)
			{
				if (clients[i].peer == NULL)
				{
					//Remove old data
					free(clients[i].skinData);
					memset(&clients[i], 0, sizeof(CLIENT));
					
					//Set peer
					clients[i].peer = (void*)event.peer;
					printf("User successfully connected,\nHost: %d\n", event.peer->address.host);
					
					//Send all player skins
					for (int v = 0; v < MAX_CLIENTS; v++)
					{
						if (v != i && clients[v].peer && clients[v].skinData)
						{
							const int packetSize = 12 + clients[v].skinSize;
							uint8_t *skinPacket = (uint8_t*)malloc(packetSize);
							ByteStream* skinPacketData = new ByteStream(skinPacket, packetSize);
							skinPacketData->WriteLE32(NET_VERSION);
							skinPacketData->WriteLE32(PACKETCODE_SKIN);
							skinPacketData->WriteLE32(v);
							skinPacketData->Write(clients[v].skinData, 1, clients[v].skinSize);
							delete skinPacketData;
							
							//Send packet
							ENetPacket *definePacket = enet_packet_create(skinPacket, packetSize, ENET_PACKET_FLAG_RELIABLE);
							enet_peer_send((ENetPeer*)event.peer, 0, definePacket);
							free(skinPacket);
						}
					}
					break;
				}
				else if (i == MAX_CLIENTS - 1)
				{
					//Failed to connect
					printf("User attempted to connect,\nbut the server is full...\n(Host: %d)\n", event.peer->address.host);
					enet_peer_disconnect_now(event.peer, DISCONNECT_FORCE);
					break;
				}
			}
			
			break;
			
		case ENET_EVENT_TYPE_DISCONNECT:
			//Remove peer from client-list
			for (int i = 0; i < MAX_CLIENTS; i++)
			{
				if (clients[i].peer == event.peer)
				{
					//Quit message if has a name
					if (strlen(clients[i].name) >= NAME_MIN)
					{
						char quitMsg[PACKET_DATA];
						sprintf(quitMsg, "%s has left", clients[i].name);
						BroadcastChatMessage(quitMsg);
					}
					
					//Remove data
					free(clients[i].skinData);
					memset(&clients[i], 0, sizeof(CLIENT));
					break;
				}
			}
			
			//Disconnected
			printf("User disconnected,\nHost: %d\n", event.peer->address.host);
			break;
			
		case ENET_EVENT_TYPE_RECEIVE:
			for (int i = 0; i < MAX_CLIENTS; i++)
			{
				if (clients[i].peer == event.peer)
				{
					//Handle packet data
					ByteStream* packetData = new ByteStream(event.packet->data, event.packet->dataLength);
					ByteStream* repPacketData;
					
					char* wounceMsg = new char[event.packet->dataLength - 8];
					int netver;
					
					if ((netver = packetData->ReadLE32()) == NET_VERSION)
					{
						switch (packetData->ReadLE32())
						{
							case PACKETCODE_DEFINE_PLAYER:
								//Load name
								packetData->Read(clients[i].name, 1, MAX_NAME);
								
								//Broadcast join message
								char joinMsg[PACKET_DATA];
								sprintf(joinMsg, "%s has joined", clients[i].name);
								BroadcastChatMessage(joinMsg);
								break;
							case PACKETCODE_CHAT_MESSAGE:
								packetData->Read(wounceMsg, 1, event.packet->dataLength - 8);
								BroadcastChatMessage(wounceMsg);
								break;
							case PACKETCODE_REPLICATE_PLAYER:
								//Bounce to other clients
								uint8_t packet[0x100];
								memset(packet, 0, 0x100);
								
								repPacketData = new ByteStream(packet, 0x100);
								
								repPacketData->WriteLE32(NET_VERSION);
								repPacketData->WriteLE32(PACKETCODE_REPLICATE_PLAYER);
								
								//Set attributes
								repPacketData->WriteLE32(i);
								repPacketData->WriteLE32(packetData->ReadLE32());		//cond
								repPacketData->WriteLE32(packetData->ReadLE32());		//unit
								repPacketData->WriteLE32(packetData->ReadLE32());		//flag
								//TODO
								//if(HIDE_AND_SEEK)
								//   do something to overwrite the client name with 0's?
								repPacketData->Write(clients[i].name, 1, MAX_NAME);	//name
								repPacketData->WriteLE32(packetData->ReadLE32());		//x
								repPacketData->WriteLE32(packetData->ReadLE32());		//y
								repPacketData->WriteLE32(packetData->ReadLE32());		//up
								repPacketData->WriteLE32(packetData->ReadLE32());		//down
								repPacketData->WriteLE32(packetData->ReadLE32());		//arms
								repPacketData->WriteLE32(packetData->ReadLE32());		//equip
								repPacketData->WriteLE32(packetData->ReadLE32());		//ani_no
								repPacketData->WriteLE32(packetData->ReadLE32());		//direct
								repPacketData->WriteLE32(packetData->ReadLE32());		//shock
								repPacketData->WriteLE32(packetData->ReadLE32());		//life
								repPacketData->WriteLE32(packetData->ReadLE32());		//max life
								repPacketData->WriteLE32(packetData->ReadLE32());		//stage
								repPacketData->WriteLE32(packetData->ReadLE32());		//mim
								delete repPacketData;
								
								for (int v = 0; v < MAX_CLIENTS; v++)
								{
									if (v != i && clients[v].peer)
									{
										//Send packet
										ENetPacket *definePacket = enet_packet_create(packet, 0x100, 0);
										enet_peer_send((ENetPeer*)clients[v].peer, 0, definePacket);
									}
								}
								break;
								
							case PACKETCODE_SKIN:
								//Set player's skin
								const int skinDataSize = event.packet->dataLength - 8;
								free(clients[i].skinData);
								clients[i].skinData = (uint8_t*)malloc(skinDataSize);
								clients[i].skinSize = skinDataSize;
								packetData->Read(clients[i].skinData, 1, skinDataSize);
								
								printf("Received skin for %s\n", clients[i].name);
								
								//Send all players skin
								const unsigned int packetSize = 12 + skinDataSize;
								uint8_t* skinPacket = (uint8_t*)malloc(packetSize);
								ByteStream* skinPacketData = new ByteStream(skinPacket, packetSize);
								skinPacketData->WriteLE32(NET_VERSION);
								skinPacketData->WriteLE32(PACKETCODE_SKIN);
								skinPacketData->WriteLE32(i);
								skinPacketData->Write(clients[i].skinData, 1, skinDataSize);
								delete skinPacketData;
								
								for (int v = 0; v < MAX_CLIENTS; v++)
								{
									if (v != i && clients[v].peer)
									{
										//Send packet
										ENetPacket *definePacket = enet_packet_create(skinPacket, packetSize, ENET_PACKET_FLAG_RELIABLE);
										enet_peer_send((ENetPeer*)clients[v].peer, 0, definePacket);
										printf("Sent their skin to %s\n", clients[v].name);
									}
								}
								
								free(skinPacket);
								break;
						}
					}
					else
					{
						printf("User disconnected,\nReason: Invalid NET_VERSION (%d)\nHost: %d\n", netver, event.peer->address.host);
						enet_peer_disconnect_now(event.peer, DISCONNECT_FORCE);
					}
					
					// We have to delete it, since we used new -Brayconn
					delete[] wounceMsg;
					delete packetData;
					break;
				}
			}
			
			//Finished with the packet
			enet_packet_destroy(event.packet);
			break;
	}
}

int HandleServerSynchronous(void* ptr)
{
	ENetEvent event;
	
	while (IsHosting() && !toEndThread)
	{
		int ret = enet_host_service(host, &event, 2000);
		
		if (ret < 0)
		{
			KillServer();
			return -1;
		}
		
		if (ret == 0)
			continue;
		
		HandleServerEvent(event);
	}
	
	return 0;
}

bool StartServer(const char* ip, const char *port)
{
	//Set IP address
	if (enet_address_set_host(&hostAddress, ip) < 0)
		return false;
	
	//Set port
	if (!VerifyPort(port))
		return false;
	hostAddress.port = std::stoi(std::string(port), nullptr, 10);
	
	//Create host
	if ((host = enet_host_create(&hostAddress, MAX_CLIENTS, 1, 0, 0)) == NULL)
		return false;
	
	//Start thread
	toEndThread = false;
	ServerThread = new std::thread(HandleServerSynchronous, nullptr);
	return true;
}

//Kill server
void KillServer()
{
	//End thread
	toEndThread = true;
	ServerThread->join();
	
	//Disconnect all clients
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		if (clients[i].peer != NULL)
		{
			enet_peer_disconnect_now((ENetPeer*)clients[i].peer, DISCONNECT_FORCE);
			clients[i].peer = NULL;
		}
	}
	//Kill host
	if (host)
		enet_host_destroy(host);
	host = NULL;
}

//Check if host still exists
bool IsHosting()
{
	return (host != NULL);
}

//Chat
void BroadcastChatMessage(const char *text)
{
	//Write packet data
	auto packetSize = 8 + (strlen(text) + 1);
	uint8_t* packet = new uint8_t[packetSize];
	
	ByteStream* packetData = new ByteStream(packet, packetSize);
	packetData->WriteLE32(NET_VERSION);
	packetData->WriteLE32(PACKETCODE_CHAT_MESSAGE);
	packetData->Write(text, 1, strlen(text) + 1);
	delete packetData;

	//Send packet
	ENetPacket *definePacket = enet_packet_create(packet, packetSize, ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(host, 0, definePacket);
	delete[] packet;
} 

//Command-line program
#ifdef SERVERONLY
#include <stdio.h>
#include <iostream>
#undef main

int main(int argc, char *argv[])
{
	if (argc <= 2)
	{
		std::cout << "Freeware Online Command-line server\nHow to use:\nserver 'ip' 'port'\n";
		return -1;
	}
	else
	{
		//Init enet
		if (enet_initialize() < 0)
		{
			std::cout << "Failed to initialize ENet\n";
			return -1;
		}

		// port "
		//Start server
		std::cout << "Trying to run server at " << argv[1] << ":" << argv[2] << std::endl;
		
		if (!StartServer(argv[1],argv[2]))
		{
			std::cout << "Failed to start server\n";
			return -1;
		}
		
		std::cout << "Success, type 'quit' to shutdown...\n";
		
		//Wait for q to be pressed
		while (true)
		{
			std::string command;
			std::cin >> command;

			if (command == "quit")
				break;
		}
		
		KillServer();
		std::cout << "Shutdown server!\n";
	}
	
	enet_deinitialize();
	return 0;
}
#endif
