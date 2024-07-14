/*##########################################################
# INF01151 - Sistemas Operacionais II N - Turma A (2024/1) #
#           Mateus Luiz Salvi - Bianca Pelegrini           #
#        Davi Haas Rodrigues - Adilson Enio Pierog         #
##########################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h> 
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "monitoring.h"
#include "discovery.h"
#include "management.h"
#include "interface.h"

#define MAXTHREADS 100

enum THREADS
{
    THREAD_CLIENT_INPUT,
    THREAD_CLIENT_SIGNAL_CATCHER,
    THREAD_SERVER_MONITORING
};

pthread_t threads[MAXTHREADS];

void HandleSystemSignals(int sig) 
{ 
    switch (sig)
    {
        case 2: //Code 2 is for OS calling EXIT
            system("clear");
            printf("OS Signal %d recieved. Exiting.\n", sig);
            exit(0);
            break;
        
        default:
            printf("Caught signal %d\n", sig);
            break;
    }
} 

void* ClientInputSubprocess()
{
    char userInput[4];

    while(1)
    {
        system("clear");
        printf("EXIT, SLEEP OR LOCAL (exit, sleep placeholder, localHost test)\nWaiting for user input: ");
        scanf("%s", userInput);
        system("clear");
        if(strcmp(userInput, "EXIT") == 0)
        {
            system("clear");
            printf("SHOULD EXIT NOW\n");
            exit(0);
        }
        else if(strcmp(userInput, "SLEEP") == 0)
        {
            char* broadCastAdress = GetBroadcastAdress();
            printf("Broadcasting SLEEP MODE to ip: %s\n", broadCastAdress);
            BroadcastSleep(broadCastAdress);
            exit(0);
        }
        else if(strcmp(userInput, "LOCAL") == 0)
        {
            printf("Broadcasting SLEEP MODE to localHost 127.0.0.1\n");
            BroadcastSleep("127.0.0.1");
            exit(0);
        }
    }
}

void* ClientCatchSignal(void* arg)
{
    bool shouldRun = true;

    while (shouldRun) 
    { 
        signal(SIGINT, *HandleSystemSignals); 
        signal(SIGTERM, *HandleSystemSignals);
    } 

    pthread_exit(&arg);
}

void ClientSubprocess()
{
    int signalArg, inputArg;  
    
    //Start Signal Catcher and Input Reader threads
    pthread_create(&threads[THREAD_CLIENT_INPUT], NULL, ClientCatchSignal, &signalArg);
    pthread_create(&threads[THREAD_CLIENT_SIGNAL_CATCHER], NULL, ClientInputSubprocess, &inputArg);

    //Wait for Signal Catcher and Input Reader threads
    pthread_join(threads[THREAD_CLIENT_INPUT], NULL);
    pthread_join(threads[THREAD_CLIENT_SIGNAL_CATCHER], NULL);
}

void ServerSubprocess()
{
    int monitoringArg = 0;  
    
    pthread_create(&threads[THREAD_SERVER_MONITORING], NULL, ListenForSleepBroadcasts, &monitoringArg);

    pthread_join(threads[THREAD_SERVER_MONITORING], NULL); 
}

int main(int argc, char *argv[])
{
    bool isManager = false;

    if ((argv[1] != NULL) && (strcmp(argv[1], "$manager"))) //Optimizations must be active in compiler (boolean short-circuit)
        isManager = true;

    if(isManager)
    {
        printf("Running as Manager.\n");
        ServerSubprocess();
    }
    else
    {
        printf("Invalid or no argument passed, running as Client mode.\n");
        ClientSubprocess();
    }

    return 0;
}