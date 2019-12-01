#ifndef _CONTROLESOM_H_
#define _CONTROLESOM_H_

#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>

enum Musica
{
	MUSICA_MENU,
	MUSICA_JOGO,
	MUSICA_FIM
};

class ControleSom
{
	private:
		static Mix_Music *musicaAtual;

	public:
		static int canal;
		// EFEITOS DO JOGO
		static Mix_Chunk *efeitoTacada;
		static Mix_Chunk *efeitoColisao;
		static Mix_Chunk *efeitoEncacapada;
		static Mix_Chunk *efeitoMesa;
		static Mix_Chunk *efeitoItem;

		// EFEITOS DOS MENUS
		static Mix_Chunk *efeitoSelecao;
		static Mix_Chunk *efeitoBotao;

		static void carregar();
		static void descarregar();
		static void tocar(Mix_Chunk *efeito);
		static void tocar(Musica musica);
};

#endif
