#ifndef _CARROS_
#define _CARROS_

#include <ncurses.h>
typedef struct Carro{
	int 		xPosi, 
				yPosi;
	
	char		frentecima,
				frentebaixo,
				trascima ,
				trasbaixo ;
				
} Carro;

void move_carros(Carro *veiculo, WINDOW *tela, int larg);

void iniciar_carros(Carro carros[], int quantidade, WINDOW *tela);

#endif