#include "TelaJogo.h"
#include "GerenciadorTelas.h"

TelaJogo::TelaJogo() : Tela()
{
	this->mesaJogo = new MesaDeJogo();
}

void TelaJogo::iniciar()
{
	this->fundo = Util::carregarImagem("./recursos/imagens/fundoTelaJogo.PNG");
}

void TelaJogo::controle(Uint8 *botoes)
{
	this->mesaJogo->gerenciarJogo(botoes);

	if(botoes[SDLK_ESCAPE])
		GerenciadorTelas::mudarTela(GerenciadorTelas::telaMenu);
	else if(botoes[SDLK_f])
		this->mesaJogo->testarFimDeJogo(true);
}

void TelaJogo::atualizar()
{
	this->mesaJogo->atualizar();
}

void TelaJogo::desenhar(SDL_Surface *bufferTela)
{
	Util::aplicarImagem(0, 0, this->fundo, bufferTela);
	this->mesaJogo->imprimirObjetos(bufferTela);
}

void TelaJogo::aoEntrar()
{
	jogoRodando = true;
	this->threadAnimJogador = SDL_CreateThread(threadAtualizarAnimJogador, NULL);
	this->threadAnimNome = SDL_CreateThread(threadAtualizarAnimNome, NULL);
	this->mesaJogo->iniciar();
}

void TelaJogo::aoSair()
{
	jogoRodando = false;
	SDL_KillThread(this->threadAnimJogador);
	SDL_KillThread(this->threadAnimNome);
	this->mesaJogo->finalizar();
}

int threadAtualizarAnimJogador(void *dados)
{
	while(TelaJogo::jogoRodando)
	{
		Jogador::atualizarAnimacao();
	}

	return 0;
}

int threadAtualizarAnimNome(void *dados)		// concorrente
{
	while(TelaJogo::jogoRodando)
	{
		MesaDeJogo::atualizarAnimNome();
	}

	return 0;
}
