#include <stdio.h>
#include <stdlib.h>
#include "monitoring.h"
#include "discovery.h"
#include "management.h"
#include "interface.h"

int main(int argc, char *argv[])
{
    char *argument = argv[1];

    if(*argument == 's' || *argument == 'S') 
    {
        while(1)
        {

        }
    }
    else
    {
        printf("Invalid or no argument passed, running as Client mode. (Launch with s or S arguments to force Server mode)\n");
        while(1)
        {

        }
    }

    return 0;
}