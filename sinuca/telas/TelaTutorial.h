#ifndef _TELATUTORIAL_H_
#define _TELATUTORIAL_H_

#include "Tela.h"

class TelaTutorial : public Tela
{
	private:
		bool botaoPressionado;

	public:
		TelaTutorial();

		void iniciar();
		void controle(Uint8 *botoes);
		void atualizar();
		void desenhar(SDL_Surface *bufferTela);

		void aoEntrar();
		void aoSair();
};

#endif

