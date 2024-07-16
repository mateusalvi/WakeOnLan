#ifndef _MONITORING_
#define _MONITORING_

/*##########################################################
# INF01151 - Sistemas Operacionais II N - Turma A (2024/1) #
#                    Mateus Luiz Salvi                     #
##########################################################*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "constants.h"

typedef struct __packet{
    uint16_t type; //Tipo do pacote (p.ex. DATA | CMD)
    uint16_t seqn; //Número de sequência
    uint16_t length; //Comprimento do payload
    uint16_t timestamp; // Timestamp do dado
    const char* _payload; //Dados da mensagem
} packet;

typedef struct __sleepingPC
{
    char* ip;
    char* mac;
    struct __sleepingPC* next;
} sleepingPC;

void Listen();

void AddSleepingMachine(char* ip, char* mac);

sleepingPC* GetLastMachine(sleepingPC* root);

sleepingPC* FindParentPC(char* ip, char* mac, sleepingPC rootSleepingPC);

void PrintAllMachines();

void PrintLoop(sleepingPC* rootSleepingPC, int counter);

void WakePC(char* ip);

#endif