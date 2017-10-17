// DOUGLAS AFFONSO CLEMENTINO
// GRR20175877

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "audio-open.h"
#include "arg-treat.h"
#include "utilidades.h"

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

            // Soma o comprimento dos  audios dados como entrada na variável "comprimento_max"
            comprimento_max += (cabecalho + i)->data_size;

            // Verifica se todos os arquivos wav dados como entrada possuem o mesmo semple rate, 
            // caso não possuam, o programa é abortado.
            if((i >= 1) && ((cabecalho + i)->sample_rate != (cabecalho + (i - 1))->sample_rate))
            {
                fprintf(stderr, "O programa só pode tratar de arquivos wave com o mesmo sample rate.\n");
                exit(-1);
            }
        }
    
    
        // Copia informações do cabecalho do primeiro 
        // arquivo que foi dado como entrada.
        memcpy(&saida, cabecalho, 44);
        
        // Modifica informações de acordo com os dados que serão comportados 
        // das várias entradas.
        saida.data_size = comprimento_max;    
        saida.riff_size = saida.data_size + 36;
        saida.DATA = malloc_seguro(comprimento_max);
        saida.samples_channel = saida.data_size / saida.block_align;
    
    
        i = 0;
        k = 0;
        
        // Laço para controlar quantidade de entradas a serem concatenadas em saida.DATA 
        // onde "i" indica  qual dos elementos de origem sera analisado, "j" indica qual 
        // bloco de simple deve ser copiado e "k" onde esse bloco deve ser copiado em saida.DATA.
        while(i < entradas)
        {
            // Laço para carregar blodos de simples e alocalos 
            // em saida.DATA de acordeo com a ordem de entrada dos arquivos.
            for(j = 0; j < (*(cabecalho + i)).samples_channel ; j++)
            {
                *((int *)saida.DATA + k) = *((int *)(cabecalho + i)->DATA + j);
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