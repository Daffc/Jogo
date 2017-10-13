#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
                        maior_sample = 0,
                        *transitorio;

    short               desvio,
                        max_amplitude = 32767;

    float               fator = 1.0,
                        diferenca;



    tratamento_simples(&argc, argv, "ilo" , 3, &origem, &destino, NULL, &fator);

    if((fator >=0) && (fator <= 10))
    {
        // Carrega informações do audio de entrada na structure "cabecalho". 
        audio_load(origem, &cabecalho);
        
        if(cabecalho.num_channels == 2)
        {

            transitorio = malloc_seguro(cabecalho.data_size * ( sizeof(int)/sizeof(short) ));
            
            // Laço percorre a semple de duas em duas ( conjunto L e R ) e efetua operação para gerar 
            // efeito desejado e guardando resultado em malloc "transitorio".
            for(i = 0; i < (cabecalho.samples_channel * cabecalho.num_channels); i += 2)
            {  
                desvio = *(((short *)(cabecalho.DATA)) + i + 1) - *(((short *)(cabecalho.DATA)) + i);


                *(transitorio + i) = *(((short *)(cabecalho.DATA)) + i) - trunc(fator * desvio);
                *(transitorio + i + 1) =*(((short *)(cabecalho.DATA)) + i + 1) + trunc(fator * desvio);
                
                if(abs(*(transitorio + i)) > maior_sample)
                {
                    maior_sample = abs(*(transitorio + i));
                }
                
                if(abs(*(transitorio + i + 1)) >maior_sample)
                {
                    maior_sample = abs(*(transitorio + i + 1));
                }

            }

            // Calcula o indice para normalização do aldio após  efeito formado.
            diferenca =  max_amplitude * 1.0 / maior_sample;

            // Tranferem-se informações para o malloc cabecalho.DATA normalizados de 
            // forma a preservar a qualidade do audio.
            for(i = 0; i < (cabecalho.samples_channel * cabecalho.num_channels); i++)
            {   
                *((short *)(cabecalho.DATA) + i) = trunc(*(transitorio + i) * diferenca);
            }
                        
            // Envia informações para imprimir em arquivo selecionado 
            // ou saida padrão o arquivo wave configurado.
            audio_set(destino, &cabecalho);

            // Libera memoria alocada por todos os mallocs feitos pelo programa.
            free(cabecalho.DATA);
            return(0);
        }
        else
        {
            fprintf(stderr, "O efeito só pode ser aplicado a arquivos wave com 2 canais.");
            exit(-1);
        }        
    }
    else
    {
        fprintf(stderr, "O fator de diferença deve estar entre 0.0 e 10.0\n");
        exit(-1);
    }
}