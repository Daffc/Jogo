#ifndef _JOGADOR_
#define _JOGADOR_

typedef struct Jogador
{
    int 		    xPosi, 
                    yPosi,
                    xInic,
                    yInic,
                    vidas;

    long            pontos;

    char		    frentecima,
                    frentebaixo,
                    trascima ,
                    trasbaixo ;
} Jogador;

void remove_jogador (Jogador *jogador, WINDOW *tela);
void reposiciona_jogador(Jogador *jogador, WINDOW *tela);
void iniciar_jogador(Jogador *jogador, WINDOW *tela);
int capi_movimento(Jogador *jogador, WINDOW *tela, int max_larg, int max_comp);
void morte_jogador(Jogador *jogador,WINDOW *tela);

#endif