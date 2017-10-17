// DOUGLAS AFFONSO CLEMENTINO
// GRR20175877

#include <stdlib.h>
#include <stdio.h>
#include "utilidades.h"

// Função apra efetuar malloc de forma segura.
void* malloc_seguro( int comprimento)
{
    void            *ponteiro;

    ponteiro = malloc(comprimento);

    if(ponteiro == NULL)
    {
        fprintf(stderr, "Não foi possivel efetuar a alocação de memória.");
        exit(-1);
    }
    return ponteiro;
}