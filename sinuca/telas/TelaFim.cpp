#include "TelaFim.h"
#include "GerenciadorTelas.h"

TelaFim::TelaFim()
{
}

void TelaFim::iniciar()
{
	this->botaoPressionado = true;
}

void TelaFim::controle(Uint8 *botoes)
{
	if(botoes[SDLK_RETURN] || botoes[SDLK_ESCAPE])
	{
		if(this->botaoPressionado)
			return;

		GerenciadorTelas::mudarTela(GerenciadorTelas::telaCreditos);
	}
	else
		this->botaoPressionado = false;
}

void TelaFim::atualizar()
{
}

void TelaFim::desenhar(SDL_Surface *bufferTela)
{
	Util::aplicarImagem(0, 0, this->fundo, bufferTela);
	Util::aplicarImagem(400 - (this->imgVencedor->w/2), 300 - (this->imgVencedor->h/2), this->imgVencedor, bufferTela);
}

void TelaFim::aoEntrar()
{
	this->fundo = Util::carregarImagem("./recursos/imagens/fundoTelaFim.PNG");
	
	this->fonte = TTF_OpenFont("./recursos/fontes/maiden.ttf", 60);

	SDL_Color cor = {255, 255, 0};
	char txt[10];

	switch(GerenciadorTelas::getVencedor())
	{
		case 1: strcpy(txt, "UM"); break;
		case 2: strcpy(txt, "DOIS"); break;
		case 3: strcpy(txt, "TRES"); break;
		case 4: strcpy(txt, "QUATRO"); break;
		
		default: strcpy(txt, "MENOS UM"); break;
	}
	
	this->imgVencedor = TTF_RenderText_Solid(this->fonte, txt, cor);
	this->botaoPressionado = true;
	ControleSom::tocar(MUSICA_FIM);
}

void TelaFim::aoSair()
{
	SDL_FreeSurface(this->fundo);
}
