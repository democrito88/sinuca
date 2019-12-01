#ifndef _TELAJOGO_H_
#define _TELAJOGO_H_

#include "Tela.h"
#include "../mesa/MesaDeJogo.h"

int threadAtualizarAnimJogador(void *dados);	// concorrente
int threadAtualizarAnimNome(void *dados);		// concorrente

class TelaJogo : public Tela
{//	tela principal do jogo

	private:
		MesaDeJogo *mesaJogo;
		SDL_Thread *threadAnimJogador;
        SDL_Thread *threadAnimNome;

	public:
		static bool jogoRodando;

		TelaJogo();

		void iniciar();
		void controle(Uint8 *botoes);
		void atualizar();
		void desenhar(SDL_Surface *bufferTela);
		void aoEntrar();
		void aoSair();
};

#endif
