#ifndef _TELACREDITOS_H_
#define _TELACREDITOS_H_

#include "Tela.h"

class TelaCreditos : public Tela
{
	private:
		bool botaoPressionado;
		
	public:
		TelaCreditos(void);

		void iniciar();
		void controle(Uint8 *botoes);
		void atualizar();
		void desenhar(SDL_Surface *bufferTela);

		void aoEntrar();
		void aoSair();

};

#endif