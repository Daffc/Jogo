// DOUGLAS AFFONSO CLEMENTINO
// GRR20175877

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "audio-open.h"
#include "arg-treat.h"

int main (int argc, char *argv[])
{     
    Music_header        cabecalho;
        
    char                *origem = NULL,
                        *destino = NULL;

    int32_t             i,
                        transitorio;
    
    int16_t             clipping = 32767;

    float               volume = 1;


    tratamento_simples(&argc, argv, "ilo" , 3, &origem, &destino, NULL, &volume);

    if ((volume >= 0) && (volume <= 10))
    {
        // Carrega informações do audio de entrada na structure "cabecalho".
        audio_load(origem, &cabecalho);
    
        // Percorrem-se todas as semples multiplicando-as por valor de ampliação 
        // indicado pelo usuário ou por 1.0, como padrão.
        for(i = 0; i < (cabecalho.samples_channel * cabecalho.num_channels); i++)
        {
            transitorio = *((int16_t *)(cabecalho.DATA) + i) * volume;
            

            //  Pocesso para detectar overflow das samples e adaptalos a clippings.
            if(abs(transitorio) > clipping)
            {
                if(transitorio > 0)
                {
                    *(((int16_t *)(cabecalho.DATA)) + i) = clipping;
                }
                else
                {
                    *(((int16_t *)(cabecalho.DATA)) + i) = -clipping;
                }
                
            }
            else
            {
                *(((int16_t *)(cabecalho.DATA)) + i) = transitorio;
            }           
            
        }
        
        // Envia informações para imprimir em arquivo selecionado 
        // ou saida padrão o arquivo wave configurado.
        audio_set(destino, &cabecalho);
    
        // Libera memoria alocada por todos os mallocs feitos pelo programa.
        free(cabecalho.DATA);
    }
    else
    {
        fprintf(stderr, "o volume precisa estar entre 0.0 e 10.0\n");
        exit(-1);
    }


    return(0);
}