#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "audio-open.h"

int main (int argc, char *argv[])
{     
    Music_header        cabecalho;
        
    char                *origem = NULL,
                        *destino = NULL;

    int                 i;

    float               volume = 1;

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
                            volume = atof(argv[i]);
                        }                        
                        break;

                    default:
                        printf("Parâmetro \"%s\" não identificado.\n", argv[i]);
                        exit(1);       
                }
                
                i++;
            }
        }
    }

    // Carrega informações do audio de entrada na structure "cabecalho".
    audio_load(origem, &cabecalho);

    // Percorrem-se todas as semples multiplicando-as por valor de ampliação 
    // indicado pelo usuário ou por 1.0, como padrão.
    for(i = 0; i < (cabecalho.samples_channel * cabecalho.num_channels); i++)
    {

        *(((short *)(cabecalho.DATA)) + i) = *((short *)(cabecalho.DATA) + i) * volume;
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