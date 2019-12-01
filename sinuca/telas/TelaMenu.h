#ifndef _TELAMENU_H_
#define _TELAMENU_H_

#include "TelaJogo.h"

#define POS_X_MENU 272
#define POS_Y_MENU 230 //200
#define MAX_BOTOES 2

#define INICIAR 0
#define CREDITOS -1 //#define CREDITOS 1
#define SAIR 1

#define MAX_TEMPO 10

class TelaMenu : public Tela
{
	private:
			SDL_Surface *imgIniciar;
			SDL_Surface *imgSair;
			SDL_Surface *imgCreditos;

			SDL_Surface *imgBotoes[MAX_BOTOES];

			int botaoSelecionado;

			int tempoBotao;

	public:
		TelaMenu();

		void iniciar();
		void controle(Uint8 *botoes);
		void atualizar();
		void desenhar(SDL_Surface *bufferTela);

		void aoEntrar();
		void aoSair();
};

#endif
