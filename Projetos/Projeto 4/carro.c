#include "carro.h"

void iniciar_carros(Carro carros[], int quantidade, WINDOW *tela)
{
    int             i;
    // Definindo caracteres de definição do carro e a posição de cada carro.
    for(i = 0; i < quantidade; i++)
    {
        carros[i].frentecima = '/';
        carros[i].frentebaixo = '\\';
        carros[i].trascima = '-';
        carros[i].trasbaixo = '-';

        // Define carros acima da zona intermediária.
        if(i < quantidade /2)
        {
            carros[i].xPosi = 1;
            carros[i].yPosi = (i * 2) + 3;
        }

        // Define carros abiaxo da zoana intermediária.
        else
        {
            carros[i].xPosi = 1;
            carros[i].yPosi = (i * 2) + 5;
        }
        

        mvwaddch(tela,carros[i].yPosi, carros[i].xPosi, carros[i].frentecima); //carro frente cima
        mvwaddch(tela,carros[i].yPosi+1, carros[i].xPosi, carros[i].frentebaixo); // carro frente baixo
        mvwaddch(tela,carros[i].yPosi, 1, carros[i].trascima); //carro tras cima
        mvwaddch(tela,carros[i].yPosi+1, 1, carros[i].trasbaixo); //carro tras baixo
    }
}

void move_carros(Carro *veiculo, WINDOW *tela, int larg)
{
	veiculo->xPosi -= 1;
	
	if(veiculo->xPosi < 1)
	{
		// Remove carro antigo.
		mvwaddch(tela,veiculo->yPosi, veiculo->xPosi + 1, ' '); //carro frente cima
		mvwaddch(tela,veiculo->yPosi+1, veiculo->xPosi + 1, ' '); // carro frente baixo
		mvwaddch(tela,veiculo->yPosi, veiculo->xPosi + 2, ' '); //carro tras cima
		mvwaddch(tela,veiculo->yPosi+1, veiculo->xPosi + 2, ' '); //carro tras baixo
		// Remove carro antigo.
		
		veiculo->xPosi = larg - 2;
		mvwaddch(tela,veiculo->yPosi, veiculo->xPosi, veiculo->frentecima); //carro frente cima
		mvwaddch(tela,veiculo->yPosi+1, veiculo->xPosi, veiculo->frentebaixo); // carro frente baixo
		mvwaddch(tela,veiculo->yPosi, 1, veiculo->trascima); //carro tras cima
		mvwaddch(tela,veiculo->yPosi+1, 1, veiculo->trasbaixo); //carro tras baixo
	}
	else
	{
		if(veiculo->xPosi == larg - 3)
		{
			// Remove carro antigo.
			mvwaddch(tela,veiculo->yPosi, veiculo->xPosi + 1, ' '); //carro frente cima
			mvwaddch(tela,veiculo->yPosi+1, veiculo->xPosi + 1, ' '); // carro frente baixo
			mvwaddch(tela,veiculo->yPosi, 1, ' '); //carro tras cima
			mvwaddch(tela,veiculo->yPosi+1, 1, ' '); //carro tras baixo
			// Remove carro antigo.
		}
		else
		{
			// Remove carro antigo.
			mvwaddch(tela,veiculo->yPosi, veiculo->xPosi + 1, ' '); //carro frente cima
			mvwaddch(tela,veiculo->yPosi+1, veiculo->xPosi + 1, ' '); // carro frente baixo
			mvwaddch(tela,veiculo->yPosi, veiculo->xPosi + 2, ' '); //carro tras cima
			mvwaddch(tela,veiculo->yPosi+1, veiculo->xPosi + 2, ' '); //carro tras baixo
			// Remove carro antigo.
		}


		mvwaddch(tela,veiculo->yPosi, veiculo->xPosi, veiculo->frentecima); //carro frente cima
		mvwaddch(tela,veiculo->yPosi+1, veiculo->xPosi, veiculo->frentebaixo); // carro frente baixo
		mvwaddch(tela,veiculo->yPosi, veiculo->xPosi + 1, veiculo->trascima); //carro tras cima
		mvwaddch(tela,veiculo->yPosi+1, veiculo->xPosi + 1, veiculo->trasbaixo); //carro tras baixo
		
	}
	wrefresh(tela);
}