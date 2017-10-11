#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int compara(const void *a, const void *b)
{   
   return(*(char *)a - *(char *)b);
}

int main (int argc, char *argv[], /* char *params , int qnt_params, */char *in, char *out,int *time, float *level )
{
    int             i;

    char params[] = "aeiou";
    
    int qnt_params = strlen(params);

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
                                in = argv[i];
                            }
                            else
                            {
                                printf("Arquivo origem não informado.\n");
                            } 
                        }
                        else
                        {
                            fprintf(stderr,"Parametro não identificado.\n");
                            exit(-1);
                        }

                                               
                        break;

                    default:
                        fprintf(stderr,"Parametro não identificado.\n");
                        exit(-1);  
                        break;     
                }
                
                i++;
            }
            else
            {
                printf("Parâmetro \"%s\" não identificado.\n", argv[i]);
                exit(1); 
            }
        }
    }
}