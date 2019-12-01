#include "Tempo.h"

Tempo::Tempo()
{
    this->tempoInicio = 0;
	this->tempoPausado = 0;
	this->pausado = false;
	this->rolando = false;
}

void Tempo::comecar()
{
    this->rolando = true;
    this->pausado = false;

	this->tempoInicio = SDL_GetTicks();
}

void Tempo::parar()
{
    this->rolando = false;
    this->pausado = false;
}

void Tempo::pausar()
{
    if( ( this->rolando == true ) && ( this->pausado == false ) )
    {
        this->pausado = true;
		this->tempoPausado = SDL_GetTicks() - this->tempoInicio;
    }
}

void Tempo::continuar()
{
	if( this->pausado == true )
    {
        this->pausado = false;
		this->tempoInicio = SDL_GetTicks() - this->tempoPausado;
        this->tempoPausado = 0;
    }
}

int Tempo::getTempo()
{
    this->tempoUltimoLoop = SDL_GetTicks() - this->tempoInicio;

    if( this->rolando == true )
    {
        if( this->pausado == true )
        {
			return this->tempoPausado;
        }
        else
        {
			return SDL_GetTicks() - this->tempoInicio;
        }
    }

    return 0;
}

int Tempo::getTempoUltimoLoop()
{
    return this->tempoUltimoLoop;
}

bool Tempo::taRolando()
{
	return this->rolando;
}

bool Tempo::taPausado()
{
    return this->pausado;
}
