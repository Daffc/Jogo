#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "audio-open.h"

void audio_load(char caminho[], Music_header *wave)
{
    FILE                *arquivo;

    // Caso ponteiro para string caminho seja diferente de NULL, procura por arquivo informado, 
    // caso contrário recebe como entrada stdin.
    if(caminho)
    {
        arquivo = fopen (caminho, "r");

        // Verifica se arquivo foi aberto corretamente.
        if(!arquivo)
        {
            perror("Erro ao abrir arquivo.");
            exit(1);
        }
    }

    else
    {
        arquivo = stdin;
    }
    
    // copia todas as informações do header do arquivo .wav para a structure indicada.
    fread(wave, 44, 1, arquivo);

    // Calcula-se a quantidade de samples/canal do arquivo .wav indicado.
    (*wave).samples_channel = (*wave).data_size / (*wave).block_align;

    // Aloca-se espaço em memória para armazenar as informações relativas ao audio do arquivo .wav.
    (*wave).DATA = malloc((*wave).data_size);

    // Comporta dados de audio no espaço em memória criado anteriormente.
    fread((*wave).DATA, (*wave).data_size, 1, arquivo);

    // Fecha-se stream com arquivo indicado.
    fclose(arquivo);
}

void audio_set(char caminho[], Music_header *wave)
{
    FILE                *arquivo;

    // Caso ponteiro para string caminho seja diferente de NULL, procura por arquivo informado, 
    // caso contrário recebe como entrada stdin.
    if(caminho)
    {
        arquivo = fopen (caminho, "w");

        // Verifica se arquivo foi aberto corretamente.
        if(!arquivo)
        {
            perror("Erro ao abrir arquivo.");
            exit(1);
        }
    }

    else
    {
        arquivo = stdout;
    }

    // Escreve dados do header do structure de saida em stream indicado.
    fwrite(wave, 44, 1,  arquivo);

    // Escreve informaçõesrelativas ao audio contidas no espaço indicado em memoria na stream.
    fwrite((*wave).DATA, (*wave).data_size, 1, arquivo);
    
    // Fecha-se conexão com stream.
    fclose(arquivo);
}
