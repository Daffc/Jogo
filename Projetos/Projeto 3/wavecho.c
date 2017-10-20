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
    Music_header        cabecalho;
        
    char                *origem = NULL,
                        *destino = NULL;

    int                 i,
                        tempo = 1000,
                        maior_sample = 0,
                        soma_echo,
                        *transitorio;
    
    int16_t            max_amplitude = 32767;

    float               atenuacao = 0.5,
                        diferenca;

    tratamento_simples(&argc, argv, "ilot" , 4, &origem, &destino, &tempo, &atenuacao);

    if((tempo >= 0) && (atenuacao >= 0) && (atenuacao <= 1.0))
    {
        // Carrega informações do audio de entrada na structure "cabecalho". 
        audio_load(origem, &cabecalho);

        transitorio = malloc_seguro(cabecalho.data_size * ( sizeof(int)/sizeof(int16_t) ));

        for(i = 0; i < (cabecalho.samples_channel * cabecalho.num_channels); i++)
        {   

            *(transitorio + i) = *(((int16_t *)(cabecalho.DATA)) + i);
        }
    
        // Laço que ira propagar o eco enquanto o tempo para o fim for maior que o tempo de propagação do eco 
        // (caso o número de samples necessária para propagação seja menor que o numero de samples para o fim do arquivo).
        // A soma de 0.5 serve para melhor aprocimação no arredondamento pos cast de floa para int.

        i = 0;

        while(i + (int)((cabecalho.sample_rate * (1.0 * tempo/1000))+ 0.5) <= (cabecalho.samples_channel * cabecalho.num_channels))
        {
            // DESLOCAMENTO NO TEMPO(POSICAO[i + (SAMPLES/SEG * SEG)]) += (POSIÇÃO[i] * atenuação);
            // A soma de 0.5 serve para melhor aprocimação no arredondamento pos cast de floa para int.
            *(transitorio + i + (int)((cabecalho.sample_rate * (1.0 * tempo/1000))+ 0.5)) = *(((int16_t *)(cabecalho.DATA)) + i + (int)((cabecalho.sample_rate * (1.0 * tempo/1000))+ 0.5)) + trunc(*((int16_t *)(cabecalho.DATA) + i) * atenuacao);
            
            soma_echo = abs(*(transitorio + i + (int)((cabecalho.sample_rate * (1.0 * tempo/1000))+ 0.5)));
            
            // Verifica qual o maior valor encontrado na soma entre (estado + eco) 
            // e guarda=o na variável "maior_sample".
            if(soma_echo > maior_sample)
            {
                maior_sample = soma_echo;        
            }                
            
            i++;
        }

        // Calcula o indice para normalização do aldio após  eco ja formado na malloc "transitorio".
        diferenca =  max_amplitude * 1.0 / maior_sample;

        // Laço onde serão realocadas as samples do audio do malloc "transitorio" para 
        // "cabecalho.DATA" de forma a normaliza-las Evitando a depredação do audio final.
        for(i = 0; i < (cabecalho.samples_channel * cabecalho.num_channels); i++)
        {   
            *((int16_t *)(cabecalho.DATA) + i) = trunc(*(transitorio + i) * diferenca);
        }

        // Envia informações para imprimir em arquivo selecionado 
        // ou saida padrão o arquivo wave configurado.
        audio_set(destino, &cabecalho);
    
        // Libera memoria alocada por todos os mallocs feitos pelo programa.
        free(cabecalho.DATA);
        free(transitorio);
        return(0);
    }

    else
    {
        fprintf(stderr, "O tempo precisa ser maior que 0 e a atenuação  entre 0.0 e 1.0\n");
        exit(-1);
    }
   
}