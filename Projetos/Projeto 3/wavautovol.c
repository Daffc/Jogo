// DOUGLAS AFFONSO CLEMENTINO
// GRR20175877

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "audio-open.h"
#include "arg-treat.h"
#include "utilidades.h"

int main (int argc, char *argv[])
{     
    Music_header        cabecalho;
        
    char                *origem = NULL,
                        *destino = NULL;

    int                 i,
                        canal;

                        //Vetor para armazenar int16_t's com os valores de maior amplitude no audio / canal.
    int16_t            *maior,
                        max_amplitude = 32767;

                        // Vetor para guardar coeficiente de normalização de cada canal.
    double              *diferenca;

    tratamento_simples(&argc, argv, "io" , 2, &origem, &destino, NULL, NULL);

    // Carrega informações do audio de entrada na structure "cabecalho".
    audio_load(origem, &cabecalho);

    // Criam-se vetores um para armazenar os maiores valores de cada um dos
    // canais e outro para armazenar o incice de correção de acordo com o número 
    // de canais informados no header do arquivo .wav.
    maior = malloc_seguro(cabecalho.num_channels * sizeof(int16_t));
    diferenca = malloc_seguro(cabecalho.num_channels * sizeof(double));

    // Zeram-se todos os valores relacionados ao número de canais.
    for(i = 0; i < cabecalho.num_channels; i++)
    {
        *(maior + i) = *(diferenca + i) = 0;
    }

    // Laço que irá percorrer todas as samples contidas no audio.
    for(i = 0; i < (cabecalho.samples_channel * cabecalho.num_channels); i++)
    {   
        // Variável "canal" é utilizadas como seletor de canais, indicando 
        // a qual dos canais pertence a sample analisada.
        canal = (i % cabecalho.num_channels);

        // Caso valor "maior" relativo ao canal selecionado seja menor que o da semple atual
        // ele é substiduido.
        if(abs(*(((int16_t *)(cabecalho.DATA)) + i)) > *(maior + canal))
        {
            *(maior + canal) = abs(*(((int16_t *)(cabecalho.DATA)) + i));
        }       
    }

    // Laço que ira repetir "num_channel" vezes e ira calcular o 
    // fator de correção para a normalização de cada um dos canais.
    for( i = 0; i < cabecalho.num_channels; i++)
    {
        *(diferenca + i) = max_amplitude * 1.0 / *(maior + i);
    }
    
    // Loço que ira percorrer todas as semples e multiplica-las pelo 
    // valor de normalização relacionado ao seu canal.
    for(i = 0; i < (cabecalho.samples_channel * cabecalho.num_channels); i++)
    {
        canal = (i % cabecalho.num_channels);
        *(((int16_t *)(cabecalho.DATA)) + i) = trunc(*(((int16_t *)(cabecalho.DATA)) + i) * *(diferenca + canal));
    }
    
    // Envia-se structure com arquivo wav modificado para ser impresso.
    audio_set(destino, &cabecalho);

    // Liberam-se areas de memória reservada.
    free(cabecalho.DATA);
    free(maior);
    free(diferenca);
    return(0);
}