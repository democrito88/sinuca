#include "ControleSom.h"

void ControleSom::carregar()
{
	efeitoTacada = Mix_LoadWAV("recursos/audio/efeitoTacada.wav");
	efeitoColisao = Mix_LoadWAV("recursos/audio/efeitoColisao.wav");
	efeitoEncacapada = Mix_LoadWAV("recursos/audio/efeitoEncacapada.wav");
	efeitoMesa = Mix_LoadWAV("recursos/audio/efeitoMesa.wav");
	efeitoItem = Mix_LoadWAV("recursos/audio/efeitoItem.wav");

	efeitoSelecao = Mix_LoadWAV("recursos/audio/efeitoSelecao.wav");
	efeitoBotao = Mix_LoadWAV("recursos/audio/efeitoBotao.wav");
}

void ControleSom::descarregar()
{
	Mix_FreeChunk(efeitoTacada);
	Mix_FreeChunk(efeitoColisao);
	Mix_FreeChunk(efeitoEncacapada);
	Mix_FreeChunk(efeitoSelecao);
	Mix_FreeChunk(efeitoBotao);
	Mix_FreeChunk(efeitoMesa);
	Mix_FreeChunk(efeitoItem);
}

void ControleSom::tocar(Musica musica)
{
	Mix_HaltMusic();
	Mix_FreeMusic(musicaAtual);

	switch(musica)
	{
		case MUSICA_MENU: musicaAtual = Mix_LoadMUS("recursos/audio/musicaMenu.mp3"); break;
		case MUSICA_JOGO: musicaAtual = Mix_LoadMUS("recursos/audio/musicaJogo.mp3"); break;
		case MUSICA_FIM: musicaAtual = Mix_LoadMUS("recursos/audio/musicaFim.mp3"); break;
		default: break;
	}

	if(musicaAtual == NULL)
		printf("PROBLEMA AO CARREGAR A MUSICA!\n");
	else
		Mix_PlayMusic(musicaAtual, -1);
}

void ControleSom::tocar(Mix_Chunk *efeito)
{
	Mix_PlayChannel(canal, efeito, 0);
	canal++;
	canal = (canal > 7)? 0: canal;
}
