/*Pessoal, tou criando esse header mas não sei direito como fazer xD Corrijam o q precisar =D*/
/*Vão adicionando o que acharem que precisa adicionar*/

//PROJETO

#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#define TEMPO_ANIM_TACO 100
#define TAM_BOLA 32

#include "../util/Util.h"
#include "../util/Vetor.h"
#include "Item.h"

class Jogador
{
      private:
              int pontuacao;
              char* nome;
              Item* item;
              //Atributo para o jogo ficar mais bonitinho xD O jogador escolhe a cor que quer jogar antes da partida
              //As cores serão representadas por números inteiros. Definir, depois, quais cores serão q quais números às representarão.
              int cor;

              static int forca_tacada;
              static float angulo_tacada;
              static bool teclaTacadaPressionada;
              static const int forcaMaxima;

              static SDL_Surface *imgTaco;
              static Vetor posTaco;
              static int idAnimTaco;

              int combos;
              bool contarCombo;

              // BARRA DE FORÇA
			  static SDL_Surface *imgForca;
			  static SDL_Surface *imgBarraPreta;
			  static Vetor posForca;
			  static Vetor posBarraPreta;

      public:
			Jogador(char* nome);
			~Jogador();

             int getPontuacao();
             void setPontuacao(int pontuacao);
             char* getNome();
             Item* getItem();
             void setItem(Item* item);

             void setCombos(int combos);
             void setContarCombo(bool cc);
             int getCombos();
             bool getContarCombo();

             static int jogar(Uint8 *botoes);
             static void carregar();
             static void atualizar(Vetor posBola);
             static void desenhar(SDL_Surface *bufferTela);

             static int getForca_Tacada();
             static void setForca_Tacada(int forca);
             static int getAngulo_tacada();
             static void setAngulo_tacada(float angulo);
             static int getForcaX();
             static int getForcaY();
			 static void atualizarAnimacao();	// concorrente
};

#endif
