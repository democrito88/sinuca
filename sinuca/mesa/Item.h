//by Bob 26/06/09
#ifndef _ITEM_H_
#define _ITEM_H_

#include "Bola.h"
#include <vector>

using namespace std;

#define ITEM_ATRITO_MAIS	0
#define ITEM_ATRITO_MENOS	1
#define ITEM_VALORES_MAX	2
#define ITEM_VALORES_MIN	3

class Item{

      private:
              int tipo;
              int posX;
              int posY;
              Vetor velocidade;
              SDL_Surface *imagem;
              vector<Bola *> *bolas;
              double *coefAtritoMesa;
              bool *miraLouca;
      public:
             Item();
			 ~Item();
             Item(int posX, int posY, vector<Bola *> *bolas, double *cam, bool *ml);
             void efeito();
             void iniciar();								// configuração individual das bolas
		     void atualizar();
		     void desenhar(SDL_Surface *bufferTela);
		     int getPosX();
		     int getPosY();
		     Vetor getVel();
		     void setVel(Vetor vel);
		     void desfazerEfeito();
		     void mover();

		     int getTipo();

      };

#endif
