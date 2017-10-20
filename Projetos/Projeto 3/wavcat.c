// DOUGLAS AFFONSO CLEMENTINO
// GRR20175877

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
                        k,  
                        l,
                        entradas = 0,
                        comprimento_max = 0,
                        canais = 0;

    tratamento_multiplo( &argc, argv, "o" , 1, pnts_origem, &entradas, &destino);

    if(entradas >= 1)
    {
        // reserva espaço para alocar todos os arquivos de audio informados.
        cabecalho = malloc_seguro(sizeof(Music_header) * entradas);
    
        // Laço organiza cada arquivo de entrada a uma structure 
        // armazenada no vetor cabecalho.
        for(i = 0; i < entradas; i++)
        {
            // Carrega cada arquivo de audio indicado como entrada em uma structure própria
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
            // Soma o comprimento dos  audios dados como entrada na variável "comprimento_max" 
            // considerando a quantidade de canais do audio original e a do audio destino.
            comprimento_max += ((cabecalho + i)->data_size * (canais / (cabecalho +i)->num_channels));
        }
    
    
        // Copia informações do cabecalho do primeiro 
        // arquivo que foi dado como entrada.
        memcpy(&saida, cabecalho, 44);
        
        // Modifica informações de acordo com os dados que serão comportados 
        // das várias entradas.
        saida.num_channels = canais;
        saida.data_size = comprimento_max;    
        saida.riff_size = saida.data_size + 36;
        saida.byte_rate = saida.sample_rate * canais * sizeof(int16_t);
        saida.DATA = malloc_seguro(comprimento_max);
        saida.samples_channel = saida.data_size / saida.block_align;
    
    
        i = 0;
        k = 0;
        
        // Laço para controlar quantidade de entradas a serem concatenadas em saida.DATA 
        // onde "i" indica  qual dos elementos de origem sera analisado, "j" indica qual 
        // sample deve ser copiada e "k" onde esse bloco deve ser copiado em saida.DATA.
        while(i < entradas)
        {
            // Laço para carregar blocos de samples e aloca-los 
            // em saida.DATA de acordo com a ordem de entrada dos arquivos.
            for(j = 0; j < (((cabecalho + i)->data_size ) / sizeof(int16_t)) ; j++)
            {
                // Laço que repetira o numero de vezes necessário para a correta conersão entre os audios de diferentes canais.
                // (Ex: para canal de entrada mono e saida stereo, sera copiada duas vezes a mesma sample do canal de entrada, 
                // uma vez para cada canal  de saida).
                for(l= 0; l < canais / (cabecalho +i)->num_channels ; l++)
                {
                    *((int16_t *)saida.DATA + k) = *((int16_t *)(cabecalho + i)->DATA + j);
                    k++;
                }             
                
            }
            i++;
        }
    
        // Envia informações para imprimir em arquivo selecionado 
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