#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg-treat.h"



int compara(const void *a, const void *b)
{   
   return(*(char *)a - *(char *)b);
}

void tratamento_simples(int argc, char *argv[], char *params , int qnt_params, char **in, char **out,int *time, float *level )
{
    int             i;

    if(argc > 1)
    {
        i = 1;
        // Laço para ler todos os elementos  do vetor argv[] (exceto o primeiro).
        while(i < argc)
        {
            // Identifica caso o primeiro char da string indicada informe o simbolo '-'.
            if(argv[i][0] == '-')
            {
                // Verifica e separa os parametros passados pela linha de comando, utilizando-os e 
                // armazenando-os ou informando qual parametro não pode ser identificado e terminando execução de aplicação.
                switch(argv[i][1])
                {
                    case'i':
                        
                        // Verifica se o parâmetro em questão esta indicado na string *params, 
                        // que contem os parametros que serão usados na chamada indicada.
                        if( bsearch(&argv[i][1], params, qnt_params, sizeof(char),compara) != NULL)
                        {
                            i++;                        
                            // Verifica se o próximo parâmetro existe, caso exista guarda string contendo o edereço para esse .
                            if(i < argc)
                            {
                                *in  = malloc(sizeof(argv[i]));
                                strcpy(*in ,argv[i]);
                            }
                            else
                            {
                                //Retorna mensagem de erro caso arquivo a ser aberto não tenha sido informado.
                                fprintf(stderr,"Arquivo origem não informado.\n");
                                exit(-1);
                            } 
                        }
                        else
                        {
                            // Retorna mensagem de erro caso o parâmetro seja um dos parametros 
                            // utlizados por algum dos programas mas não no programa em questão.
                            fprintf(stderr,"Parâmetro \"%s\" não identificado.\n", argv[i]);
                            exit(-1); 
                        }
                                               

                        break;
                    case'o':
                        
                        // Verifica se o parâmetro em questão esta indicado na string *params, 
                        // que contem os parametros que serão usados na chamada indicada.
                        if( bsearch(&argv[i][1], params, qnt_params, sizeof(char),compara) != NULL)
                        {
                            i++;                        
                            // Verifica se o próximo parâmetro existe, caso exista guarda string contendo o edereço para esse .
                            if(i < argc)
                            {
                                *out  = argv[i];
                            }
                            else
                            {
                                //Retorna mensagem de erro caso arquivo a ser aberto não tenha sido informado.
                                fprintf(stderr,"Arquivo destino não informado.\n");
                                exit(-1);
                            } 
                        }
                        else
                        {
                            // Retorna mensagem de erro caso o parâmetro seja um dos parametros 
                            // utlizados por algum dos programas mas não no programa em questão.
                            fprintf(stderr,"Parâmetro \"%s\" não identificado.\n", argv[i]);
                            exit(-1); 
                        }
                                               
                        break;
                    case't':
                        
                        // Verifica se o parâmetro em questão esta indicado na string *params, 
                        // que contem os parametros que serão usados na chamada indicada.
                        if( bsearch(&argv[i][1], params, qnt_params, sizeof(char),compara) != NULL)
                        {
                            i++;                        
                            // Verifica se o próximo parâmetro existe, caso exista guarda string contendo o edereço para esse .
                            if(i < argc)
                            {
                                *time  = atoi(argv[i]);
                            }
                            else
                            {
                                //Retorna mensagem de erro caso arquivo a ser aberto não tenha sido informado.
                                fprintf(stderr,"Tempo não informado.\n");
                                exit(-1);
                            } 
                        }
                        else
                        {
                            // Retorna mensagem de erro caso o parâmetro seja um dos parametros 
                            // utlizados por algum dos programas mas não no programa em questão.
                            fprintf(stderr,"Parâmetro \"%s\" não identificado.\n", argv[i]);
                            exit(-1); 
                        }
                                               
                        break;
                    case'l':
                        
                        // Verifica se o parâmetro em questão esta indicado na string *params, 
                        // que contem os parametros que serão usados na chamada indicada.
                        if( bsearch(&argv[i][1], params, qnt_params, sizeof(char),compara) != NULL)
                        {
                            i++;                        
                            // Verifica se o próximo parâmetro existe, caso exista guarda string contendo o edereço para esse .
                            if(i < argc)
                            {
                                *level  = atof(argv[i]);
                            }
                            else
                            {
                                //Retorna mensagem de erro caso arquivo a ser aberto não tenha sido informado.
                                fprintf(stderr,"Level não informado.\n");
                                exit(-1);
                            } 
                        }
                        else
                        {
                            // Retorna mensagem de erro caso o parâmetro seja um dos parametros 
                            // utlizados por algum dos programas mas não no programa em questão.
                            fprintf(stderr,"Parâmetro \"%s\" não identificado.\n", argv[i]);
                            exit(-1); 
                        }
                                               
                        break;
                    default:
                        // Retorna menságem de erro caso comando informado não seja nenhum dos listados.
                        fprintf(stderr,"Parâmetro \"%s\" não identificado.\n", argv[i]);
                        exit(-1);   
                        break;     
                }
                
                i++;
            }
            else
            {   
                // Exibe menságem de erro e finaliza o programa caso o parametro em questão não contenha o seu identificados '-'.
                fprintf(stderr,"Parâmetro \"%s\" não identificado.\n", argv[i]);
                exit(-1); 
            }
        }
    }
}