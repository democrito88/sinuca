#ifndef _VETOR_H_
#define _VETOR_H_

#include <cmath>

class Vetor
{
	public:
		float x, y;

		Vetor();
		Vetor(float x, float y);

		float getModulo();			// retorna o tamanho do vetor
		Vetor getVetUnitario();		// retorna o vetor unitario

		void operator = (Vetor v);
};

#endif
