#include "Tela.h"

Tela::Tela()
{
}

Tela::~Tela()
{
	SDL_FreeSurface(this->fundo);
	delete this->fundo;
}

void Tela::aoEntrar()
{
}

void Tela::aoSair()
{
}
