#ifndef _TELA_H_
#define _TELA_H_

#include "../util/Util.h"

class Tela
{// classe base das telas

	protected:
        SDL_Surface *fundo;			// cada tela tem seu fundo


	public:
		Tela();
		virtual ~Tela();

		virtual void iniciar() =0;
		virtual void controle(Uint8 *botoes) =0;
		virtual void atualizar() =0;
		virtual void desenhar(SDL_Surface *bufferTela) =0;

		// métodos opcionais
		virtual void aoEntrar();
		virtual void aoSair();
};

#endif

