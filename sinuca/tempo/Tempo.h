#ifndef _TEMPO_H_
#define _TEMPO_H_

#include <SDL/SDL.h>

class Tempo
{
    private:
		int tempoInicio;
		int tempoPausado;

		int tempoUltimoLoop;

		bool pausado;
		bool rolando;

    public:
        static int QuadrosPorSegundo;

		Tempo();

		void comecar();
		void parar();
		void pausar();
		void continuar();

		int getTempo();
		int getTempoUltimoLoop();

		bool taRolando();
		bool taPausado();
};

#endif
