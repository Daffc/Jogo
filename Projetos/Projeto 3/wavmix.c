#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "audio-open.h"

int main (int argc, char *argv[])
{     
    Music_header        *cabecalho,
                        saida;
        
    char                *pnts_origem[50],
                        *destino = NULL;

    int                 i,
                        j,
                        entradas = 0,
                        comprimento_max = 0,
                        amplitude_max = 0,
                        soma = 0;
    
    short               par_normalizacao = 32767;

    double              indice_correcao;



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
        
        // Separa o maior comprimento de audio, que será o comprimento do audio mixado.
        if((*(cabecalho + i)).data_size > comprimento_max)
        {
            comprimento_max = (*(cabecalho + i)).data_size;
        }
    }

    // Laço que ira procurar por maior soma samples entre os audios, 
    // sendo "i" o indicador de quais samples devem ser somadas.
    for(i = 0; i < comprimento_max / sizeof(short); i++)
    {
        soma = 0;

        // Laço de repetição para alternar entre os audios de entrada, pegando a samples "i" 
        // indicada de cara um deles e somando seus valores na variavel "soma".
        for(j = 0; j < entradas; j++)
        {
            // Verifica-se caso o audio "j" analisado contem a semple de posição "i", caso contenha seu valr é somado as 
            // demais semplas de mesma posição dos outros arquivos de audio, caso não contenha, seu valor não é acrecentado.
            if(i < (*(cabecalho + j)).samples_channel * (*(cabecalho + j)).num_channels)
            {
                soma += *(((short *)((*(cabecalho + j)).DATA)) + i);
            }
        }

        // Caondiconal para selecionar e armazenar a maior soma entre samples encontrada 
        // na variável "amplitude_max".
        if(abs(soma) > amplitude_max)
        {
            amplitude_max = abs(soma);
        }
    }

    // Variável que calculará o valor a multiplicar a soma das semples de forma a evitar clipping.
    indice_correcao =  (1.0 * par_normalizacao) / amplitude_max;


    // Copia informações do cabecalho do primeiro arquivo que foi dado como entrada.
    memcpy(&saida, cabecalho, 44);
    
    // Modifica informações de acordo com os dados que serão comportados 
    // das várias entradas.
    saida.data_size = comprimento_max;    
    saida.riff_size = saida.data_size + 36;
    saida.DATA = malloc(comprimento_max);
    saida.samples_channel = saida.data_size / saida.block_align;


    // Laço de repetiçã que percorrerá todas as semples a serem construidas no audio de saida.
    for(i = 0; i < saida.samples_channel * saida.num_channels; i ++)
    {  
        soma = 0;

        // Laço de repetição para alternar entre os audios de entrada, pegando a samples "i" 
        // indicada de cara um deles e somando seus valores na variavel "soma".
        for(j = 0; j < entradas; j++)
        {
            // Verifica-se caso o audio "j" analisado contem a semple de posição "i", caso contenha seu valr é somado as 
            // demais semplas de mesma posição dos outros arquivos de audio, caso não contenha, seu valor não é acrecentado.
            if(i < (*(cabecalho + j)).samples_channel * (*(cabecalho + j)).num_channels)
            {
                soma += *(((short *)((*(cabecalho + j)).DATA)) + i);
            }
        }
    
        // Atribui-se ao audio de saida soma de samples multiplicada pelo indice de correção, de forma a evitar distorções.
        *(((short *)saida.DATA )+ i) = trunc(soma * indice_correcao);
    }
    // Envia informações para emprimir em arquivo selecionado 
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