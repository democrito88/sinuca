#include "Util.h"

SDL_Surface *Util::carregarImagem(std::string nomeArquivo)
{
    SDL_Surface* imagem = IMG_Load(nomeArquivo.c_str());

    return imagem;
}

void Util::aplicarImagem( float x, float y, SDL_Surface* fonte, SDL_Surface* destino )
{
    SDL_Rect offset;

    offset.x = static_cast<int>(x);
    offset.y = static_cast<int>(y);

    SDL_BlitSurface( fonte, NULL, destino, &offset );
}

void Util::aplicarImagemAnimada( float x, float y, SDL_Surface* fonte, SDL_Surface* destino, int indice, int tamQuadro)
{
    SDL_Rect offset;
    offset.x = static_cast<int>(x);
    offset.y = static_cast<int>(y);

	SDL_Rect quadro;
	quadro = fonte->clip_rect;
	quadro.x = indice * tamQuadro;
	quadro.w = tamQuadro;

    SDL_BlitSurface( fonte, &quadro, destino, &offset );
}
