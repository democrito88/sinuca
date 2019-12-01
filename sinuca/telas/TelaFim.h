#ifndef _TELAFIM_H_
#define _TELAFIM_H_

#include "Tela.h"

class TelaFim : public Tela
{
	private:
		bool botaoPressionado;
		SDL_Surface *imgVencedor;
		TTF_Font *fonte;

	public:
		TelaFim();

		void iniciar();
		void controle(Uint8 *botoes);
		void atualizar();
		void desenhar(SDL_Surface *bufferTela);

		void aoEntrar();
		void aoSair();
};

#endif