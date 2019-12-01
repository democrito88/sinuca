#ifndef _UTIL_H_
#define _UTIL_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "SDL_rotozoom.h"
#include "ControleSom.h"
#include <string>

class Util
{
    public:
        static SDL_Surface *carregarImagem(std::string nomeArquivo);
        static void aplicarImagem( float x, float y, SDL_Surface* fonte, SDL_Surface* destino );
		static void aplicarImagemAnimada( float x, float y, SDL_Surface* fonte, SDL_Surface* destino, int indice, int tamQuadro);
};

#endif // _UTIL_H_
