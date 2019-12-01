#ifndef _BOLA_H_
#define _BOLA_H_

#include "../util/Util.h"
#include "../util/Vetor.h"

class Bola
{
	private:
		Vetor posicao;
		Vetor posicaoAnterior;
		Vetor velocidade;
		Vetor direcao;			// vetor unitário q indica a direcao
		float moduloVel;
		int valor;									// posição no sprite...pode ser tb a pontuação da bola

		static SDL_Surface *imagem;
		float massa;			// mesmo arquivo de imagem pra todas as bolas

		//int velocidade;
        double qv;
        double energ;

        bool estaEmJogo;
        //static const float coef;
        //static const int massaExtra;


	public:
		Bola();
		~Bola();
		Bola(Vetor posicao, int valor);

		static void carregar();						// carrega o arquivo das bolas
		void iniciar();								// configuração individual das bolas
		void atualizar();
		void desenhar(SDL_Surface *bufferTela);
        int getVelX();
        int getVelY();
        void setVelX(int velX);
        void setVelY(int velY);
        void mover(float atrito);
        int getMassa();
        void setMassa(int massa);
        Vetor getCentro();
        static SDL_Surface* getImagem();
        Vetor getPosicao();
        void setPosicao(Vetor posicao);
		void setValor(int pontuacao);
		int getValor();
		void setEstaEmJogo(bool esta);
		bool getEstaEmJogo();
		Vetor getPosicaoAnterior();
		Vetor getVelocidade();
		void setVelocidade(Vetor velocidade);
		double energiaCinetica();

/*        void quantidadeMovimento();
        void pesada();
        void leve();
        void atrito();
*/
};

/*
const float Bola::coef = 0.9;     //valores hipotéticos
const int Bola::massaExtra = 50;  //sujeitos a mudança
*/

#endif
