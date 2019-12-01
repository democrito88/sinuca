#ifndef _TELAOPCOESJOGADORES_H_
#define _TELAOPCOESJOGADORES_H_

#include "Tela.h"
#include <vector>

using namespace std;

#define POS_X_BOTAO 200
#define POS_Y_BOTAO 300

#define MAX_TEMPO_OJ 10

#define MAX_BOTOES_OJ 4

class TelaOpcoesJogadores : public Tela
{
	private:
		SDL_Surface *imgQtdJogadores;
		int botaoSelecionado;
		int tempoBotao;

	public:
		TelaOpcoesJogadores();

		void iniciar();
		void controle(Uint8 *botoes);
		void atualizar();
		void desenhar(SDL_Surface *bufferTela);

		void aoEntrar();
		void aoSair();
};

#endif
