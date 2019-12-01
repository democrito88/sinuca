#include "TelaOpcoesJogadores.h"
#include "GerenciadorTelas.h"

TelaOpcoesJogadores::TelaOpcoesJogadores()
{
}


void TelaOpcoesJogadores::iniciar()
{
	this->tempoBotao = MAX_TEMPO_OJ - 1;
}

void TelaOpcoesJogadores::controle(Uint8 *botoes)
{
	if(this->tempoBotao < MAX_TEMPO_OJ)
	{
		this->tempoBotao--;

		if(this->tempoBotao < 0)
			this->tempoBotao = MAX_TEMPO_OJ;

		return;
	}

	bool botaoPressionado = false;

	if(botoes[SDLK_LEFT])
	{
		if(this->botaoSelecionado == 0)
			this->botaoSelecionado = MAX_BOTOES_OJ - 1;
		else
			this->botaoSelecionado--;

		ControleSom::tocar(ControleSom::efeitoSelecao);
		botaoPressionado = true;
	}
	else if(botoes[SDLK_RIGHT])
	{
		if(this->botaoSelecionado == MAX_BOTOES_OJ - 1)
			this->botaoSelecionado = 0;
		else
			this->botaoSelecionado++;

		ControleSom::tocar(ControleSom::efeitoSelecao);
		botaoPressionado = true;
	}

	if(botoes[SDLK_RETURN])
	{// MANDAR A QUANTIDADE DE JOGADORES SELECIONADA
	    GerenciadorTelas::setQtdJogadores(this->botaoSelecionado+1);
		ControleSom::tocar(ControleSom::efeitoBotao);
		GerenciadorTelas::mudarTela(GerenciadorTelas::telaTutorial);
		botaoPressionado = true;
	}
	else if(botoes[SDLK_ESCAPE])
	{
		ControleSom::tocar(ControleSom::efeitoBotao);
		GerenciadorTelas::mudarTela(GerenciadorTelas::telaMenu);
		botaoPressionado = true;
	}

	if(botaoPressionado)
		this->tempoBotao--;
	else
		this->tempoBotao = MAX_TEMPO_OJ;
}

void TelaOpcoesJogadores::atualizar()
{
}

void TelaOpcoesJogadores::desenhar(SDL_Surface *bufferTela)
{
	Util::aplicarImagem(0, 0, this->fundo, bufferTela);

	Util::aplicarImagemAnimada(POS_X_BOTAO, POS_Y_BOTAO, this->imgQtdJogadores, bufferTela, this->botaoSelecionado, 400);
}

void TelaOpcoesJogadores::aoEntrar()
{
	this->botaoSelecionado = 0;
	this->fundo = Util::carregarImagem("./recursos/imagens/fundoTelaOpcoesJogadores.PNG");
	this->imgQtdJogadores = Util::carregarImagem("./recursos/imagens/btEscolhaJogadores.PNG");
}

void TelaOpcoesJogadores::aoSair()
{
	SDL_FreeSurface(this->imgQtdJogadores);
	SDL_FreeSurface(this->fundo);
}
