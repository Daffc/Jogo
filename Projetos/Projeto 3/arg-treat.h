// DOUGLAS AFFONSO CLEMENTINO
// GRR20175877

#ifndef _LINE_CONTROL_
#define _LINE_CONTROL_

// Função que recebe as entradas da linha de comando e os argumentos utilizados pelo programa 
// principal para  atualizar as informações necessárias, com apenas um argumento por categoria entrada, saida, level e tempo.
void tratamento_simples(int *argc, char *argv[],  char *params , int qnt_params, char **in, char **out,int *time, float *level );

// Função que recebe as entradas da linha de comando e os argumentos utilizados pelo programa 
// principal para  atualizar as informações necessárias, com um ou mais argumentos indicando entradas e apenas um indicando saida.
void tratamento_multiplo(int *argc, char *argv[], char *params , int qnt_params, char *in[], int *qnt_entradas, char **out);
#endif
