#include "MetodosBola.h"
/*Autor: Democrito
  Atualizado: 20/06/09*/

int MetodosBola :: velocidade(int, vel_x,int vel_y){
     int velocidade;
     velocidade = sqrt(pow(vel_x,2) + pow(vel_y,2));
     return velocidade;
     }//velocidade resultante p/ outros cálculos

double MetodosBola :: quantidadeMovimento(int velocidade, int massa){
       double qv = velocidade*massa;
       return qv;
       }//momento linear ou quantidade de movimento

double MetodosBola :: energiaCinetica(int massa, int velocidade){
       double vel_quadrado = pow(velocidade, 2);
       double energ = (massa*vel_quadrado)/2;
       return energ;
       }//calcula a e. cinética

int MetodosBola :: pesada(int massa){
    return massa+(this->massaExtra);
    }//aumenta a massa

int MetodosBola :: leve(int massa){
    return massa-(this->massaExtra);
    }//diminui a massa

double MetodosBola :: atrito(int velocidade){
       return = velocidde*(this->coef);
       }//coloca atrito
