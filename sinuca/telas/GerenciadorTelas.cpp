#include "GerenciadorTelas.h"

GerenciadorTelas::GerenciadorTelas()
{

	// ...
}

void GerenciadorTelas::iniciar()
{// o iniciar das telas podem ser chamados por aki (uma vez) ou pelo aoEntrar (toda vez q entrar)

	telaMenu->iniciar();
	telaJogo->iniciar();
	telaOpcoesJogadores->iniciar();
	// ...

	telaAtual = telaMenu;

	telaAtual->aoEntrar();
}

void GerenciadorTelas::controle(Uint8 *botoes)
{
	telaAtual->controle(botoes);
}

void GerenciadorTelas::atualizar()
{
	telaAtual->atualizar();
}

void GerenciadorTelas::desenhar(SDL_Surface *bufferTela)
{
	telaAtual->desenhar(bufferTela);
}

void GerenciadorTelas::mudarTela(Tela *tela)
{// aoSair e aoEntrar são métodos opcionais

	telaAtual->aoSair();	// aoSair da tela antiga
	telaAtual = tela;		// substituição da tela
	telaAtual->aoEntrar();	// aoEntrar da nova tela
}

void GerenciadorTelas::setQtdJogadores(int qtd)
{
	qtdJogadores = qtd;
}

int GerenciadorTelas::getQtdJogadores()
{
	return qtdJogadores;
}

void GerenciadorTelas::setVencedor(int v)
{
	vencedor = v;
}

int GerenciadorTelas::getVencedor()
{
	return vencedor;
}

bool GerenciadorTelas::taRodando()
{
	return rodando;
}

void GerenciadorTelas::fechar()
{
	rodando = false;
}