#ifndef _JOGO_H_
#define _JOGO_H_

#include "telas/GerenciadorTelas.h"

class Jogo
{// classe principal tudo parte desta classe

	private:
		GerenciadorTelas *gerenciadorTelas;
		SDL_Surface *bufferTela;

	public:
		Jogo();

		void iniciar(SDL_Surface *bufferTela);
		void controle(Uint8 *botoes);
		void atualizar();
		void desenhar();
};

#endif
