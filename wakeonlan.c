
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
    THREAD_CLIENT_SIGNAL_CATCHER
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
    int signalArg, inputArg, status;  
    
    //Start Signal Catcher and Input Reader threads
    pthread_create(&threads[THREAD_CLIENT_INPUT], NULL, ClientCatchSignal, &signalArg);
    pthread_create(&threads[THREAD_CLIENT_SIGNAL_CATCHER], NULL, ClientInputSubprocess, &inputArg);

    //Wait for Signal Catcher and Input Reader threads
    pthread_join(threads[THREAD_CLIENT_INPUT], NULL); 
    pthread_join(threads[THREAD_CLIENT_SIGNAL_CATCHER], NULL);

}

void ServerSubprocess()
{
    //Create INPUT and MONITORING THREAD
}

int main(int argc, char *argv[])
{
    bool isManager = false;

    if ((argv[1] != NULL) && (strcmp(argv[1], "$manager")  == 0)) //Optimizations must be active in compiler (boolean short-circuit)
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