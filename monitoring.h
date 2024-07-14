#ifndef _MONITORING_
#define _MONITORING_

/*##########################################################
# INF01151 - Sistemas Operacionais II N - Turma A (2024/1) #
#           Mateus Luiz Salvi - Bianca Pelegrini           #
#        Davi Haas Rodrigues - Adilson Enio Pierog         #
##########################################################*/

#include <stdint.h>

typedef struct __packet{
    uint16_t type; //Tipo do pacote (p.ex. DATA | CMD)
    uint16_t seqn; //Número de sequência
    uint16_t length; //Comprimento do payload
    uint16_t timestamp; // Timestamp do dado
    const char* _payload; //Dados da mensagem
} packet;

void Listen();

#endif