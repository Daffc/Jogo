// DOUGLAS AFFONSO CLEMENTINO
// GRR20175877

#ifndef __UTILIDADES__
#define __UTILIDADES__

    // Função que execulta operação de malloc e verifica a integridade do resultado, 
    // retornando o ponteiro para o alocação de memória ou erro caso não tenha sido possivel efetuar a reserva.
    // Função recebe inteiro indicando o tamanho da alocação que dever ser feita (em bytes).
    void* malloc_seguro(int);

#endif