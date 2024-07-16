/*##########################################################
# INF01151 - Sistemas Operacionais II N - Turma A (2024/1) #
#                    Mateus Luiz Salvi                     #
##########################################################*/

#include "monitoring.h"
#include "discovery.h"

sleepingPC* _rootSleepingPC = NULL;

void AddSleepingMachine(char* ip, char* mac)
{
    sleepingPC* newSleepingPC = malloc(sizeof(sleepingPC));

    newSleepingPC->ip = ip;
    newSleepingPC->mac = mac;

    if(_rootSleepingPC == NULL)
    {
       _rootSleepingPC = newSleepingPC;
    }
    else
    {
        sleepingPC* lastPC = GetLastMachine(_rootSleepingPC);
        lastPC->next = newSleepingPC;
    }
}

void RemoveSleepingMachine(char* ip, char* mac)
{
    sleepingPC* parent = FindParentPC(ip, mac, *_rootSleepingPC);
    if(parent->next->next != NULL)
    {
        sleepingPC* pcToRemove = parent->next;
        parent->next = parent->next->next;
        free(pcToRemove);
    }
    else
    {
        free(parent->next);
        parent->next = NULL;
    }
}

sleepingPC* FindParentPC(char* ip, char* mac, sleepingPC rootSleepingPC)
{
    if(_rootSleepingPC != NULL)
    {
        if(_rootSleepingPC->next != NULL)
            if(strcmp(_rootSleepingPC->next->ip, ip) == 0 && strcmp(_rootSleepingPC->next->mac, mac))
                return _rootSleepingPC;
    }

    return NULL;
}

sleepingPC* GetLastMachine(sleepingPC* root)
{
    if(root->next != NULL)
        return GetLastMachine(root->next);
    else
        return root;
}

void PrintAllMachines()
{
    PrintLoop(_rootSleepingPC, 0);
}

void PrintLoop(sleepingPC* rootSleepingPC, int counter)
{
    if(rootSleepingPC != NULL)
    {
        printf("\n%d IP: %s   STATUS: %s \n", counter, rootSleepingPC->ip, rootSleepingPC->mac);
        if(rootSleepingPC->next != NULL)
            PrintLoop(rootSleepingPC->next, counter++);
    }
}

void WakePC(char* ip)
{
    printf("Sending wakeup signal to localhost");
    SendMessage("RETORNO DO SERVIDOR", "127.0.0.1", 1);
}