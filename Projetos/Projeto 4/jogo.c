#include <ncurses.h>
#include <unistd.h>
#include "carro.h"
#include "jogador.h"

#define MAX_CARROS 10

int main(int argc, char *argv[])
{       
	Carro			carros[MAX_CARROS];

	Jogador			jogador;

	WINDOW 			*janela;  //Janela principal do jogo;
	
	int 			startx, 
					starty, 
					largura, 
					comprimento,
					cont;

	unsigned long i = 0;
	
	
	initscr();                      //Iniciar modo Curses.
	cbreak();                       // Programa receberá e tratra toda e qualquer entrada de usuário.
	keypad(stdscr, TRUE);           // Mapear teclas omo F's, setas, etc...	
	nodelay(stdscr, TRUE);			// Evitar bloqueios quando requisitada entrada de usuário.
	curs_set(0);					// Esconder cursor do terminal.

	comprimento = 28;
	largura = 30;
	starty = (LINES - comprimento) / 2;  	// Calcula-se a posição de centro do terminal em relação a altura.
	startx = (COLS - largura) / 2;    		// Calcula-se a posição de centro do terminal em relação a largura.	
	
	
	printw("Press \'x\' to exit");			//Indicar tecla para finalizar programa.
	refresh();
	
	janela = newwin(comprimento, largura, starty, startx);
	box(janela, 0 , 0);

	iniciar_carros(carros, MAX_CARROS, janela);
	iniciar_jogador(&jogador, janela);

	wrefresh(janela);
	while(capi_movimento(&jogador, janela, largura - 3, comprimento - 3) != 'x')
	{  			
		// Velocidade 1
		if((i % 500000) == 0)
		{	
			move_carros(&carros[0], janela, largura);
			move_carros(&carros[3], janela, largura);
			move_carros(&carros[6], janela, largura);
			move_carros(&carros[9], janela, largura);
		}	
		// Velocidade 2
		if((i % 200000) == 0)
		{	
			move_carros(&carros[1], janela, largura);
			move_carros(&carros[4], janela, largura);
			move_carros(&carros[7], janela, largura);			
		}	

		// Velocidade 3
		if((i % 300000) == 0)
		{	
			move_carros(&carros[2], janela, largura);
			move_carros(&carros[5], janela, largura);
			move_carros(&carros[8], janela, largura);			
		}	


		i++;
		if(i > 1000000000)
		{
			i = 1;
		}
		for(cont = 0; cont < MAX_CARROS; cont ++)
		{	
			/*	---------- APRIMORAR VERIFICAÇÃO COM MATRIZ POSTERIORMENTE !!!! ----------- */
			/**/if((jogador.xPosi == carros[cont].xPosi) && (jogador.yPosi == carros[cont].yPosi))
			/**/{
			/**/	remove_jogador (&jogador, janela);
			/**/	reposiciona_jogador( &jogador, janela);
			/**/};
			/**/if((jogador.xPosi == carros[cont].xPosi + 1) && (jogador.yPosi == carros[cont].yPosi))
			/**/{
			/**/	remove_jogador (&jogador, janela);
			/**/	reposiciona_jogador( &jogador, janela);
			/**/}
			/**/if((jogador.xPosi + 1 == carros[cont].xPosi) && (jogador.yPosi == carros[cont].yPosi))
			/**/{
			/**/	remove_jogador (&jogador, janela);
			/**/	reposiciona_jogador( &jogador, janela);
			/**/}
		}
	}

	endwin();
	return 0;
}