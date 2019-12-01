#include "TelaCreditos.h"
#include "GerenciadorTelas.h"

TelaCreditos::TelaCreditos()
{
}

void TelaCreditos::iniciar()
{
	this->botaoPressionado = true;
}

void TelaCreditos::controle(Uint8 *botoes)
{
	if(botoes[SDLK_RETURN] || botoes[SDLK_ESCAPE])
	{
		if(this->botaoPressionado)
			return;

		ControleSom::tocar(ControleSom::efeitoBotao);
		GerenciadorTelas::mudarTela(GerenciadorTelas::telaMenu);
		botaoPressionado = true;
	}
	else
		this->botaoPressionado = false;
}

void TelaCreditos::atualizar()
{
}

void TelaCreditos::desenhar(SDL_Surface *bufferTela)
{
	Util::aplicarImagem(0, 0, this->fundo, bufferTela);
}

void TelaCreditos::aoEntrar()
{
	this->fundo = Util::carregarImagem("./recursos/imagens/fundoTelaCreditos.PNG");
	this->botaoPressionado = true;
}

void TelaCreditos::aoSair()
{
	SDL_FreeSurface(this->fundo);
}
