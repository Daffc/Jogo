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

    int                 i,
                        transitorio;

    /*
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
                    default:
                        printf("Parâmetro \"%s\" não identificado.\n", argv[i]);
                        exit(1);       
                }
            }
            i++;
        }
    }
    */

    tratamento_simples(argc, argv, "io" , 2, &origem, &destino, NULL, NULL);

    // Carrega informações do audio de entrada na structure "cabecalho". 
    audio_load(origem, &cabecalho);

    // Laçoira repetir "samples_channel" / 2 arredondado para baxo, veses e 
    // trocaraos o primeiro valor cm o ultimo, o segundo com o penultimo e assim sucessivamente.
    for(i = 0; i <= ((cabecalho.samples_channel / 2) - 1); i++)
    {
        transitorio = *(((int *)(cabecalho.DATA)) + i);

        *(((int *)(cabecalho.DATA)) + i) = *(((int *)(cabecalho.DATA)) + cabecalho.samples_channel - (i + 1));
        *(((int *)(cabecalho.DATA)) + cabecalho.samples_channel - (i + 1)) = transitorio;
    }
    
    // Envia informações para imprimir em arquivo selecionado 
    // ou saida padrão o arquivo wave configurado.
    audio_set(destino, &cabecalho);
    
    // Libera memoria alocada por todos os mallocs feitos pelo programa.
    free(cabecalho.DATA);

    return(0);
}