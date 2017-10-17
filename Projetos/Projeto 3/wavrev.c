// DOUGLAS AFFONSO CLEMENTINO
// GRR20175877

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "audio-open.h"
#include "arg-treat.h"

int main (int argc, char *argv[])
{     
    Music_header        cabecalho;
        
    char                *origem = NULL,
                        *destino = NULL;

    int                 i,
                        transitorio;

    tratamento_simples(&argc, argv, "io" , 2, &origem, &destino, NULL, NULL);

    // Carrega informações do audio de entrada na structure "cabecalho". 
    audio_load(origem, &cabecalho);

    // Laçoira repetir ("samples_channel" / 2 arredondado para baixo) veses e 
    // trocarão o primeiro valor com o ultimo, o segundo com o penultimo e assim sucessivamente.
    for(i = 0; i <= ((cabecalho.samples_channel / 2) - 1); i++)
    {
        transitorio = *(((int32_t *)(cabecalho.DATA)) + i);

        *(((int32_t *)(cabecalho.DATA)) + i) = *(((int32_t *)(cabecalho.DATA)) + cabecalho.samples_channel - (i + 1));
        *(((int32_t *)(cabecalho.DATA)) + cabecalho.samples_channel - (i + 1)) = transitorio;
    }
    
    // Envia informações para imprimir em arquivo selecionado 
    // ou saida padrão o arquivo wave configurado.
    audio_set(destino, &cabecalho);
    
    // Libera memoria alocada por todos os mallocs feitos pelo programa.
    free(cabecalho.DATA);

    return(0);
}