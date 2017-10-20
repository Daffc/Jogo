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

    int32_t             i,
                        j;

    int16_t             transitorio;

    tratamento_simples(&argc, argv, "io" , 2, &origem, &destino, NULL, NULL);


    // Carrega informações do audio de entrada na structure "cabecalho". 
    audio_load(origem, &cabecalho);

    // Laço ira repetir ("samples_channel" / 2 arredondado para baixo) veses e 
    // trocarão o primeiro bloco de samples com o ultimo, o segundo com o penultimo e assim sucessivamente.
    for(i = 0; i < (cabecalho.samples_channel / 2); i++)
    {

        // Laço que determinará qual dos canais deve ser trocado de acordo com o número de canais definido em "cabecalho.num_channels",
        // trocando o primeiro sample do primeiro bloco com o primeiro sample do ultimo bloco, o sagundo sample do primeiro bloco com o segundo sample do ultimo bloco...
        for(j = 0; j < cabecalho.num_channels; j ++)
        {
            transitorio = *(((int16_t *)(cabecalho.DATA)) + (cabecalho.num_channels * i) + j);
            
            *(((int16_t *)(cabecalho.DATA)) + (cabecalho.num_channels * i) + j) = *(((int16_t *)(cabecalho.DATA)) + ((cabecalho.samples_channel - i)  * cabecalho.num_channels) + j);
            *(((int16_t *)(cabecalho.DATA)) + ((cabecalho.samples_channel - i)  * cabecalho.num_channels) + j) = transitorio;
        }
        
    }
    
    // Envia informações para imprimir em arquivo selecionado 
    // ou saida padrão o arquivo wave configurado.
    audio_set(destino, &cabecalho);
    
    // Libera memoria alocada por todos os mallocs feitos pelo programa.
    free(cabecalho.DATA);

    return(0);
}