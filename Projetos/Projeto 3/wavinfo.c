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
                        palavra[4][5];

    // Le argumentos de linha de comando e trata-os conforme estipulado.
    tratamento_simples(&argc, argv, "i" , 1, &origem, NULL, NULL, NULL);
    
    // Carrega informações do audio de entrada na structure "cabecalho". 
    audio_load(origem, &cabecalho);
    
    // Alocando strings competentes ao arquivo de audio em uma string ( com adição do '\0').
    memcpy(palavra[0], cabecalho.riff_tag, 4);
    memcpy(palavra[1], cabecalho.wave_tag, 4);
    memcpy(palavra[2], cabecalho.form_tag, 4);
    memcpy(palavra[3], cabecalho.data_tag, 4);

    palavra[0][4] = palavra[1][4] = palavra[2][4] = palavra[3][4] = 0;
    

    printf("riff tag        : \"%s\" \n", palavra[0]);
    printf("riff size       : %u \n", cabecalho.riff_size );
    printf("wave tag        : \"%s\" \n", palavra[1]);
    printf("form tag        : \"%s\" \n", palavra[2]);
    printf("fmt_size        : %u \n", cabecalho.fmt_size);
    printf("audio_format    : %d \n", cabecalho.audio_format);
    printf("num_channels    : %d \n", cabecalho.num_channels);
    printf("sample_rate     : %u \n", cabecalho.sample_rate);
    printf("byte_rate       : %u \n", cabecalho.byte_rate);
    printf("block_align     : %d \n", cabecalho.block_align);
    printf("bits_per_sample : %d \n", cabecalho.bits_per_sample);
    printf("data tag        : \"%s\" \n", palavra[3]); 
    printf("data size       : %u \n", cabecalho.data_size);
    printf("samples/channel : %u \n", cabecalho.samples_channel);

    // Libera memoria alocada por todos os mallocs feitos pelo programa.
    free(cabecalho.DATA);
    return(0);
}