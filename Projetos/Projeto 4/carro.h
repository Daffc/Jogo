#ifndef _CARROS_
#define _CARROS_

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
typedef enum{
	DIREITA,
	ESQUERDA
} Sentido;


typedef struct Carro{
	int 		xPosi, 
				yPosi;

	Sentido 	sentido;
	
	char		frentecima,
				frentebaixo,
				trascima ,
				trasbaixo ;
				
} Carro;

typedef struct Caminhao{
	int 		xPosi, 
				yPosi;
	
	Sentido 	sentido;

	char		frentecima,
				frentebaixo,
				meiofrentecima,
				meiofrentebaixo,
				meiotrascima,
				mriotrasbaixo,
				trascima ,
				trasbaixo ;
				
} Caminhao;

void move_carros(Carro *veiculo, WINDOW *tela, int larg);

void iniciar_carros(Carro carros[], int quantidade, WINDOW *tela);

#endif