/*##########################################################
# INF01151 - Sistemas Operacionais II N - Turma A (2024/1) #
#           Mateus Luiz Salvi - Bianca Pelegrini           #
#        Davi Haas Rodrigues - Adilson Enio Pierog         #
##########################################################*/

#include "interface.h"

void* ClientInputSubprocess()
{
    char userInput[4];

    while(1)
    {
        system("clear");
        printf("Waiting for user input: ");
        scanf("%s", userInput);

        if(strcmp(userInput, "EXIT") == 0)
        {
            
            system("clear");
            printf("SHOULD EXIT NOW\n");
            exit(0);
        }
    }
}