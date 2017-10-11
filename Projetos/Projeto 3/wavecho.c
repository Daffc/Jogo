#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "audio-open.h"

int main (int argc, char *argv[])
{     
    Music_header        cabecalho;
        
    char                *origem = NULL,
                        *destino = NULL;

    int                 i,
                        tempo = 1000;

    float               atenuacao = 0.5;


    if(argc > 1)
    {
        i = 1;

        while(i < argc)
        {
            if(argv[i][0] == '-')
            {
                switch(argv[i][1])
                {
                    case'i':
                        i++;
                        if(i < argc)
                        {
                            origem = malloc(sizeof(argv[i]));
                            strcpy(origem,argv[i]);
                        }
                        else
                        {
                            printf("Arquivo não informado.\n");
                            exit(1);
                        }
                        
                        break;
                    
                    case'o':
                        i++;

                        if(i < argc)
                        {
                            destino = malloc(sizeof(argv[i]));
                            strcpy(destino,argv[i]);
                        }
                        else
                        {
                            printf("Destino não informado.\n");
                            exit(1);
                        }
                        
                        break;

                        case'l':
                        i++;

                        if(i < argc)
                        {
                            atenuacao = atof(argv[i]);
                        }                        
                        break;

                        case't':
                        i++;

                        if(i < argc)
                        {
                            tempo = atoi(argv[i]);
                        }                        
                        break;

                    default:
                        printf("Parâmetro \"%s\" não identificado.\n", argv[i]);
                        exit(1);       
                }
            }
            i++;
        }
    }

    // Carrega informações do audio de entrada na structure "cabecalho". 
    audio_load(origem, &cabecalho);

    // Laço que ira propagar o eco enquanto o tempo para o fim for maior que o tempo de propagação do eco 
    // (caso o número de samples necessária para propagação seja menor que o numero de samples para o fim do arquivo).
    while(i + (int)((cabecalho.sample_rate * (1.0 * tempo/1000))+ 0.5) <= (cabecalho.samples_channel * cabecalho.num_channels))
    {
        // DESLOCAMENTO NO TEMPO(POSICAO[i + (SAMPLES/SEG * SEG)]) += (POSIÇÃO[i] * atenuação);
        *(((short *)(cabecalho.DATA)) + i + (int)((cabecalho.sample_rate * (1.0 * tempo/1000))+ 0.5)) += trunc(*((short *)(cabecalho.DATA) + i) * atenuacao);
        
        i++;
    }
    
    // Envia informações para imprimir em arquivo selecionado 
    // ou saida padrão o arquivo wave configurado.
    audio_set(destino, &cabecalho);

    // Libera memoria alocada por todos os mallocs feitos pelo programa.
    free(origem);
    free(destino);
    free(cabecalho.DATA);
    return(0);
}