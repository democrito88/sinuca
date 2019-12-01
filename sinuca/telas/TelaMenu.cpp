#include "TelaMenu.h"
#include "GerenciadorTelas.h"

TelaMenu::TelaMenu()
{
}

void TelaMenu::iniciar()
{
	this->tempoBotao = MAX_TEMPO;
}

void TelaMenu::controle(Uint8 *botoes)
{
	if(this->tempoBotao < MAX_TEMPO)
	{
		this->tempoBotao--;

		if(this->tempoBotao < 0)
			this->tempoBotao = MAX_TEMPO;

		return;
	}

	bool botaoPressionado = false;

	if(botoes[SDLK_UP])
	{
		if(this->botaoSelecionado == 0)
			this->botaoSelecionado = MAX_BOTOES - 1;
		else
			this->botaoSelecionado--;

		ControleSom::tocar(ControleSom::efeitoSelecao);
		botaoPressionado = true;
	}
	else if(botoes[SDLK_DOWN])
	{
		if(this->botaoSelecionado == MAX_BOTOES - 1)
			this->botaoSelecionado = 0;
		else
			this->botaoSelecionado++;

		ControleSom::tocar(ControleSom::efeitoSelecao);
		botaoPressionado = true;
	}

	if(botoes[SDLK_RETURN])
	{
		switch(this->botaoSelecionado)
		{
			case INICIAR:	GerenciadorTelas::mudarTela(GerenciadorTelas::telaOpcoesJogadores);
							break;
			case CREDITOS:	GerenciadorTelas::mudarTela(GerenciadorTelas::telaCreditos);
							break;
			case SAIR:		GerenciadorTelas::fechar(); break;

			default:		break;
		}

		ControleSom::tocar(ControleSom::efeitoBotao);
		botaoPressionado = true;
	}

	if(botaoPressionado)
		this->tempoBotao--;
	else
		this->tempoBotao = MAX_TEMPO;
}

void TelaMenu::atualizar()
{
}

void TelaMenu::desenhar(SDL_Surface *bufferTela)
{
	Util::aplicarImagem(0, 0, this->fundo, bufferTela);

	float posY = POS_Y_MENU;
	for(int i=0; i < MAX_BOTOES; i++)
	{
		Util::aplicarImagemAnimada(POS_X_MENU, posY, this->imgBotoes[i], bufferTela, this->botaoSelecionado == i, 256);
		posY += 100;
	}

}

void TelaMenu::aoEntrar()
{
	this->fundo = Util::carregarImagem("./recursos/imagens/fundoTelaMenu.PNG");
	this->imgBotoes[INICIAR] = Util::carregarImagem("./recursos/imagens/btIniciar.PNG");
	this->imgBotoes[CREDITOS] = Util::carregarImagem("./recursos/imagens/btCreditos.PNG");
	this->imgBotoes[SAIR] = Util::carregarImagem("./recursos/imagens/btSair.PNG");

	ControleSom::tocar(MUSICA_MENU);

	this->botaoSelecionado = INICIAR;
}

void TelaMenu::aoSair()
{
	SDL_FreeSurface(this->fundo);

	for(int i=0; i < MAX_BOTOES; i++)
		SDL_FreeSurface(this->imgBotoes[i]);
}
