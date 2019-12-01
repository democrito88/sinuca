#include "Vetor.h"

Vetor::Vetor()
{
	this->x = 0;
	this->y = 0;
}

Vetor::Vetor(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Vetor::getModulo()
{
	float quadrado = pow(this->x, 2) + pow(this->y, 2);
	float res = sqrtf(quadrado);

	return res;
}

Vetor Vetor::getVetUnitario()
{
   float tam = getModulo();

   if(tam == 0.0f)
      tam = 1.0f;

   return Vetor(this->x/tam, this->y/tam);
}

void Vetor::operator = (Vetor v)
{
	this->x = v.x;
	this->y = v.y;
}