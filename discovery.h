#ifndef _DISCOVERY_
#define _DISCOVERY_

/*##########################################################
# INF01151 - Sistemas Operacionais II N - Turma A (2024/1) #
#           Mateus Luiz Salvi - Bianca Pelegrini           #
#        Davi Haas Rodrigues - Adilson Enio Pierog         #
##########################################################*/

#include <sys/socket.h>

#define BROADCAST_PORT 20000
#define MAXLEN 100 

char* GetBroadcastAdress();

void* BroadcastSleep(char* broadcastAdress);

static void Broadcast(const char *message);

int ListenForSleepBroadcast();

void* ListenForSleepBroadcasts();

#endif