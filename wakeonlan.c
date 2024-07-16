/*##########################################################
# INF01151 - Sistemas Operacionais II N - Turma A (2024/1) #
#                    Mateus Luiz Salvi                     #
##########################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h> 
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <regex.h>
#include "monitoring.h"
#include "discovery.h"
#include "management.h"
#include "interface.h"
#include "constants.h"

pthread_t threads[MAXTHREADS];
int sendMessageLock = 0;

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
            printf("Caught signal %d\n", (int)sig);
            break;
    }
} 

void* ClientCatchSignal(void* arg)
{
    bool shouldRun = true;

    while (shouldRun) 
    { 
        signal(SIGINT, *HandleSystemSignals);
        signal(SIGSEGV, *HandleSystemSignals);
        signal(SIGILL, *HandleSystemSignals);
        signal(SIGFPE, *HandleSystemSignals);
        signal(SIGTERM, *HandleSystemSignals);
    } 

    pthread_exit(&arg);
}

void* ClientInputSubprocess()
{
    char userInput[4];

    system("clear");

    while(1)
    {
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
        }
        else if(strcmp(userInput, "LOCAL") == 0)
        {
            printf("Broadcasting SLEEP MODE to localHost 127.0.0.1\n");
            BroadcastSleep("127.0.0.1");
        }
    }
}

void* ClientListenForWakeup()
{
    ListenForSleepBroadcasts(threads);
}

void* ServerSignalWake()
{
    SendMessage("HELLO IM THE SERVER","127.0.0.1", 1);
}

void ServerSignalWakeSubprocess()
{
    int shouldRun = 1;
    while (shouldRun > 0)
    {
        if(sendMessageLock > 0)
            continue;
        else
        {
            pthread_create(&threads[THREAD_SERVER_WAKE_SIGNAL], NULL, ServerSignalWake, NULL);
            pthread_join(threads[THREAD_SERVER_WAKE_SIGNAL], NULL);
            shouldRun = 0;
        }
    }
    
}

void* ServerInputSubprocess()
{
    char userInput[20];
    regex_t reegex;

    int regexBool = regcomp(&reegex, "WAKE^([0-9]|[1-9][0-9]|1([0-9][0-9])|2([0-4][0-9]|5[0-5]))."
             "([0-9]|[1-9][0-9]|1([0-9][0-9])|2([0-4][0-9]|5[0-5]))."
             "([0-9]|[1-9][0-9]|1([0-9][0-9])|2([0-4][0-9]|5[0-5]))."
             "([0-9]|[1-9][0-9]|1([0-9][0-9])|2([0-4][0-9]|5[0-5]))$", REG_EXTENDED);

    if(regexBool)
    {
        printf("Could not compile regex\n");
    } 
    
    while(1)
    {
        printf("Use \"WAKE 255.255.255.255\"\n");
        scanf("%19[^\n]", userInput); 

        // regexBool = regexec(&reegex, userInput, 0, NULL, 0);
        // if (!regexBool)
        // {
            system("clear");
            //printf("Waking machine: %s\n", userInput);
            printf("Sending packet to localhost");
            ServerSignalWakeSubprocess();
        // }

    }

    regfree(&reegex);
}


void* ServerListenForSleepSubprocess()
{
    while(1)
    {
        ListenForSleepBroadcasts(threads);

        printf("Should add to table\n");
    }
}

void ClientSubprocess()
{
    int signalArg, inputArg;  
    
    //Start Signal Catcher and Input Reader threads
    pthread_create(&threads[THREAD_CLIENT_INPUT], NULL, ClientCatchSignal, &signalArg);
    pthread_create(&threads[THREAD_CLIENT_SIGNAL_CATCHER], NULL, ClientInputSubprocess, &inputArg);
    pthread_create(&threads[THREAD_CLIENT_WAKEUP_CATCHER], NULL, ClientInputSubprocess, &inputArg);

    //Wait for Signal Catcher and Input Reader threads
    pthread_join(threads[THREAD_CLIENT_INPUT], NULL);
    pthread_join(threads[THREAD_CLIENT_SIGNAL_CATCHER], NULL);
    pthread_join(threads[THREAD_CLIENT_WAKEUP_CATCHER], NULL);
}

void ServerSubprocess()
{
    int monitoringArg = 0;  
    pthread_create(&threads[THREAD_SERVER_MONITORING], NULL, ServerListenForSleepSubprocess, &monitoringArg);
    pthread_create(&threads[THREAD_SERVER_INPUT], NULL, ServerInputSubprocess, &monitoringArg);

    pthread_join(threads[THREAD_SERVER_MONITORING], NULL);
    pthread_join(threads[THREAD_SERVER_INPUT], NULL);
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