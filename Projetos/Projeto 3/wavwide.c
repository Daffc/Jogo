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

    int                 i;

    short               diferenca;

    double              fator = 1;

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
                            fator = atof(argv[i]);
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
    
    // Laço percorre a semple de duas em duas ( conjunto L e R ) e efetua operação para gerar efeito desejado.
    for(i = 0; i < (cabecalho.samples_channel * cabecalho.num_channels); i += 2)
    {  
        diferenca = *(((short *)(cabecalho.DATA)) + i + 1) - *(((short *)(cabecalho.DATA)) + i);

        *(((short *)(cabecalho.DATA)) + i) -= trunc(fator * diferenca);
        *(((short *)(cabecalho.DATA)) + i + 1) += trunc(fator * diferenca);
        
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