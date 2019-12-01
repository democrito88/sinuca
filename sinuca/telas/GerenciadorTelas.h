#ifndef _GERENCIADORTELAS_H_
#define _GERENCIADORTELAS_H_

#include "TelaJogo.h"
#include "TelaMenu.h"
#include "TelaOpcoesJogadores.h"
#include "TelaTutorial.h"
#include "TelaFim.h"
#include "TelaCreditos.h"

class GerenciadorTelas
{// controla as janelas e encaminha as funções pra janela atual

	private:
		static Tela *telaAtual;
		static int qtdJogadores;
		static int vencedor;
		static bool rodando;

	public:
		static TelaMenu *telaMenu;
		static TelaJogo *telaJogo;
		static TelaOpcoesJogadores *telaOpcoesJogadores;
		static TelaTutorial *telaTutorial;
		static TelaFim *telaFim;
		static TelaCreditos *telaCreditos;

		GerenciadorTelas();

		void iniciar();
		void controle(Uint8 *botoes);
		void atualizar();
		void desenhar(SDL_Surface *bufferTela);

		static void mudarTela(Tela *tela);

		static void setQtdJogadores(int qtdJogadores);
		static int getQtdJogadores();
		static void setVencedor(int v);
		static int getVencedor();

		static bool taRodando();
		static void fechar();
};

#endif
