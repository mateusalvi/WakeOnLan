#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h> 
#include <unistd.h>
#include <string.h>
#include "monitoring.h"
#include "discovery.h"
#include "management.h"
#include "interface.h"

void HandleSystemSignals(int sig) 
{ 
    switch (sig)
    {
    case 2: //Code 2 is for OS calling EXIT
        printf("\nOS Signal %d recieved. Exiting.\n", sig);
        exit(0);
        break;
    
    default:
        printf("Caught signal %d\n", sig);
        break;
    }
} 

void ClientSubprocess()
{
    //create thread
    //start WAIT FOR SLEEP MESSAGE loop
    //  

    while (1) 
    { 
        signal(SIGINT, *HandleSystemSignals); 
    } 

}

void ServerSubprocess()
{
    //Create INPUT and MONITORING THREAD
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