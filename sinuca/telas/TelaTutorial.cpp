#include "TelaTutorial.h"
#include "GerenciadorTelas.h"

TelaTutorial::TelaTutorial()
{
}

void TelaTutorial::iniciar()
{
	this->botaoPressionado = true;
}

void TelaTutorial::controle(Uint8 *botoes)
{
	if(botoes[SDLK_RETURN])
	{
		if(this->botaoPressionado)
			return;

		ControleSom::tocar(ControleSom::efeitoBotao);
		GerenciadorTelas::mudarTela(GerenciadorTelas::telaJogo);
		botaoPressionado = true;
	}
	else if(botoes[SDLK_ESCAPE])
	{
		ControleSom::tocar(ControleSom::efeitoBotao);
		GerenciadorTelas::mudarTela(GerenciadorTelas::telaOpcoesJogadores);
	}
	else
		this->botaoPressionado = false;
}

void TelaTutorial::atualizar()
{
}

void TelaTutorial::desenhar(SDL_Surface *bufferTela)
{
	Util::aplicarImagem(0, 0, this->fundo, bufferTela);
}

void TelaTutorial::aoEntrar()
{
	this->fundo = Util::carregarImagem("./recursos/imagens/tutorial.PNG");
	this->botaoPressionado = true;
}

void TelaTutorial::aoSair()
{
	SDL_FreeSurface(this->fundo);
}
