#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "audio-open.h"

int main (int argc, char *argv[])
{     
    Music_header        *cabecalho,
                        saida;
        
    char                *pnts_origem[50],
                        *destino = NULL;

    int                 i,
                        j,
                        k,  
                        entradas = 0,
                        comprimento_max = 0;

    if(argc > 1)
    {
        i = 1;

        while(i < argc)
        {
            if(argv[i][0] == '-')
            {
                switch(argv[i][1])
                {                    
                    case'o':
                        i++;

                        if(i < argc)
                        {
                            destino = malloc(sizeof(argv[i]));
                            strcpy(destino,argv[i]);
                        }
                        else
                        {
                            fprintf(stderr, "Destino não informado.\n");
                            exit(1);
                        }
                         i++;
                        break;
                    default:
                        fprintf(stderr, "Destino não informado.\n");
                        exit(1);       
                }
            }
        
            // Caso argumento naão esteja precedido de string "-o" armazenar o 
            // endereço desta string no vetor pnts_origem para serem tratados 
            // como entradas posteriormente
            if(i < argc)
            {
                entradas ++;
                pnts_origem[entradas - 1] = argv[i];
                
                i++;
            }
        }
    }

    // reserva espaço para alocar todos os arquivos de audio informados.
    cabecalho = malloc(sizeof(Music_header) * entradas);

    // Laço organiza cada arquivo de entrada a uma structure 
    // armazenada no vetor cabecalho.
    for(i = 0; i < entradas; i++)
    {
        audio_load(pnts_origem[i], (cabecalho + i));
        comprimento_max += (*(cabecalho + i)).data_size;
    }


    // Copia informações do cabecalho do primeiro 
    // arquivo que foi dado como entrada.
    memcpy(&saida, cabecalho, 44);
    
    // Modifica informações de acordo com os dados que serão comportados 
    // das várias entradas.
    saida.data_size = comprimento_max;    
    saida.riff_size = saida.data_size + 36;
    saida.DATA = malloc(comprimento_max);
    saida.samples_channel = saida.data_size / saida.block_align;


    i = 0;
    k = 0;
    
    // Laço para controlar quantidade de entradas a serem concatenadas em saida.DATA 
    // onde "i" indica  qual dos elementos de origem sera analisado, "j" indica qual 
    // bloco de simple deve ser copiado e "k" onde esse bloco deve ser copiado em saida.DATA.
    while(i < entradas)
    {
        // Laço para carregar blodos de simples e alocalos 
        // em saida.DATA de acordeo com a ordem de entrada dos rquivos.
        for(j = 0; j < (*(cabecalho + i)).samples_channel ; j++)
        {
            *((int *)saida.DATA + k) = *(((int *)((*(cabecalho + i)).DATA)) + j);
            k++;
        }
        i++;
    }

    // Envia informações para imprimir em arquivo selecionado 
    // ou saida padrão o arquivo wave configurado.
    audio_set(destino, &saida);

    // Libera memoria alocada por todos os mallocs feitos pelo programa.
    for(i = 0; i < entradas; i++)
    {
        free((*(cabecalho + i)).DATA);
    }
    
    free(saida.DATA);
    free(cabecalho);
    free(destino);
    return(0);
}