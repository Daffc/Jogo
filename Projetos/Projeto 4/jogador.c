#include <ncurses.h>
#include "jogador.h"

void imprime_jogador (Jogador *jogador, WINDOW *tela)
{
    mvwaddch(tela,jogador->yPosi, jogador->xPosi, jogador->frentecima); //carro frente cima
    mvwaddch(tela,jogador->yPosi+1, jogador->xPosi, jogador->frentebaixo); // carro frente baixo
    mvwaddch(tela,jogador->yPosi, jogador->xPosi+1, jogador->trascima); //carro tras cima
    mvwaddch(tela,jogador->yPosi+1, jogador->xPosi+1, jogador->trasbaixo); //carro tras baixo
}

void move_cima(Jogador *jogador, WINDOW *tela)
{
    remove_jogador(jogador, tela);
    jogador->yPosi -= 2;

    //Verifica se play ira ultrapassar bordas.
    if(jogador->yPosi < 1)
    {
        jogador->yPosi = 1;
    }
    imprime_jogador(jogador, tela);
    wrefresh(tela);
}
void move_baixo(Jogador *jogador, WINDOW *tela, int max_comp)
{
    remove_jogador(jogador, tela);
    jogador->yPosi += 2;

    //Verifica se play ira ultrapassar bordas.
    if(jogador->yPosi > max_comp)
    {
        jogador->yPosi = max_comp;
    }
    imprime_jogador(jogador, tela);
    wrefresh(tela);
}
void move_esquerda(Jogador *jogador, WINDOW *tela)
{
    remove_jogador(jogador, tela);
    jogador->xPosi -= 2;

    //Verifica se play ira ultrapassar bordas.
    if(jogador->xPosi < 1)
    {
        jogador->xPosi = 1;
    }
    imprime_jogador(jogador, tela);
    wrefresh(tela);
}
void move_direita(Jogador *jogador, WINDOW *tela, int max_larg)
{
    remove_jogador(jogador, tela);
    jogador->xPosi += 2;

    //Verifica se play ira ultrapassar bordas.
    if(jogador->xPosi > max_larg)
    {
        jogador->xPosi = max_larg;
    }
    imprime_jogador(jogador, tela);
    wrefresh(tela);
}

/* ------------------------------ FUNÇÔES EXTERNAS ------------------------------*/

void remove_jogador (Jogador *jogador, WINDOW *tela)
{
    mvwaddch(tela,jogador->yPosi, jogador->xPosi, ' '); //carro frente cima
    mvwaddch(tela,jogador->yPosi+1, jogador->xPosi, ' '); // carro frente baixo
    mvwaddch(tela,jogador->yPosi, jogador->xPosi+1, ' '); //carro tras cima
    mvwaddch(tela,jogador->yPosi+1, jogador->xPosi+1, ' '); //carro tras baixo
}

void reposiciona_jogador(Jogador *jogador, WINDOW *tela)
{
    // Define posição inicial do jogador.
    jogador->xPosi = jogador->xInic = 13;
    jogador->yPosi = jogador->yInic = 25;

    // Envia jogador para  WINDOW de saida.
    imprime_jogador(jogador, tela);
}
void iniciar_jogador(Jogador *jogador, WINDOW *tela)
{
    // Define "aparência" do jogador.
    jogador->frentecima = 'x';
    jogador->frentebaixo = 'x';
    jogador->trascima = 'x';
    jogador->trasbaixo = 'x' ;

    jogador->vidas = 3;
    jogador->pontos = 0;

    // Coloca jogador na posição inicial e atualiza window.
    reposiciona_jogador(jogador, tela);
}

int capi_movimento(Jogador *jogador, WINDOW *tela, int max_larg, int max_comp)
{
    int ch = getch();

    switch (ch)
    {
        case KEY_UP:
            move_cima(jogador, tela);
            break;
        case KEY_DOWN:
            move_baixo(jogador, tela, max_comp);
            break;
        case KEY_LEFT:
            move_esquerda(jogador, tela);
            break;
        case KEY_RIGHT:
            move_direita(jogador, tela, max_larg);
            break;
    }
    return ch;
}
void morte_jogador(Jogador *jogador, WINDOW *tela)
{
    jogador->vidas --;
    remove_jogador (jogador, tela);
    reposiciona_jogador( jogador, tela);
}