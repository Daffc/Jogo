// DOUGLAS AFFONSO CLEMENTINO
// GRR20175877

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "audio-open.h"
#include "arg-treat.h"
#include "utilidades.h"

int main (int argc, char *argv[])
{     
    Music_header        *cabecalho,
                        saida;
        
    char                *pnts_origem[50],
                        *destino = NULL;

    int32_t             i,
                        j,
                        entradas = 0,
                        comprimento_max = 0,
                        amplitude_max = 0,
                        soma = 0,
                        canais = 0,
                        posicao;
    
    int16_t            par_normalizacao = 32767;

    double              indice_correcao;



    tratamento_multiplo( &argc, argv, "o" , 1, pnts_origem, &entradas, &destino);

    if(entradas >= 1)
    {
        // reserva espaço para alocar todos os arquivos de audio informados.
        cabecalho = malloc_seguro(sizeof(Music_header) * entradas);


        
        // Laço organiza cada arquivo de entrada a uma structure 
        // armazenada no vetor cabecalho.
        for(i = 0; i < entradas; i++)
        {
            // Carrega cada arquivo de audio indicado como entrada em uma structure própria.
            audio_load(pnts_origem[i], (cabecalho + i));

            // Verifica se todos os arquivos wav dados como entrada possuem o mesmo semple rate, 
            // caso não possuam, o programa é abortado.
            if((i >= 1) && ((cabecalho + i)->sample_rate != (cabecalho + (i - 1))->sample_rate))
            {
                fprintf(stderr, "O programa só pode tratar de arquivos wave com o mesmo sample rate.\n");
                exit(-1);
            }

            // Verifica qual é o audio com o maior numero da canais e salva esse número na variável canais.
            if((cabecalho + i)->num_channels > canais)
            {
                canais = (cabecalho + i)->num_channels;
            }
        }

        for (i = 0; i < entradas; i++)
        {
            // Separa o maior comprimento de audio, que será o comprimento do audio mixado, 
            // levando em consideração o seu comprimento e a sua quantidade de canais.
            if((cabecalho + i)->data_size / (cabecalho + i)->num_channels > comprimento_max / canais)
            {
                comprimento_max = (cabecalho + i)->data_size * ( canais / ( cabecalho + i )->num_channels);
            }
        }
    
        // Laço que ira procurar por maior soma samples entre os audios, 
        // sendo "i" o indicador de quais samples devem ser somadas.
        for(i = 0; i < comprimento_max / sizeof(int16_t); i++)
        {
            soma = 0;
    
            // Laço de repetição para alternar entre os audios de entrada, pegando a samples "i" 
            // indicada de cara um deles e somando seus valores na variavel "soma".
            for(j = 0; j < entradas; j++)
            {
                // Verifica-se caso o audio "j" analisado contem a semple de posição "i" relativa ao ao maior número de canais e 
                // ao número de canais do audio de entrada, caso contenha seu valor é somado as demais samples de mesma posição 
                // relativisada dos outros arquivos de audio, caso não contenha, seu valor não é acrecentado.
                if(i < (cabecalho + j)->samples_channel * (cabecalho + j)->num_channels)
                {
                    posicao = (int32_t)((((cabecalho + j)->num_channels * 1.0) / canais) * i);
                    soma += *((int16_t *)((cabecalho + j)->DATA) + posicao);
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
        saida.byte_rate = saida.sample_rate * canais * sizeof(int16_t);
        saida.DATA = malloc_seguro(comprimento_max);
        saida.samples_channel = saida.data_size / saida.block_align;
    
    
        // Laço de repetiçã que percorrerá todas as semples a serem construidas no audio de saida.
        for(i = 0; i < saida.samples_channel * saida.num_channels; i ++)
        {  
            soma = 0;
    
            // Laço de repetição para alternar entre os audios de entrada, pegando a samples "i" 
            // indicada de cara um deles e somando seus valores na variavel "soma".
            for(j = 0; j < entradas; j++)
            {
                // Verifica-se caso o audio "j" analisado contem a semple de posição "i", caso contenha seu valor é somado as 
                // demais semplas de mesma posição dos outros arquivos de audio, caso não contenha, seu valor não é acrecentado.
                if(i < (cabecalho + j)->samples_channel * (cabecalho + j)->num_channels * ( canais / ( cabecalho + j )->num_channels))
                {
                    soma += *((int16_t *)((cabecalho + j)->DATA) + i);
                }
            }
        
            // Atribui-se ao audio de saida soma de samples multiplicada pelo indice de correção, de forma a evitar distorções.
            *(((int16_t *)saida.DATA )+ i) = trunc(soma * indice_correcao);
        }
        // Envia informações para emprimir em arquivo selecionado 
        // ou saida padrão o arquivo wave configurado.
        audio_set(destino, &saida);
    
        // Libera memoria alocada por todos os mallocs feitos pelo programa.
        for(i = 0; i < entradas; i++)
        {
            free((cabecalho + i)->DATA);
        }
        
        free(saida.DATA);
        free(cabecalho);
        return(0);
    }
    else
    {
        fprintf(stderr, "É necessário informar ao menos uma entrada de audio formato .wav.\n");
        exit(-1);
    }    
}