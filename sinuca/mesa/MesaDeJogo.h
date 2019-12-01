#ifndef _MESADEJOGO_H_
#define _MESADEJOGO_H_

#include <vector>
#include <sstream>

#include "Bola.h"
#include "Jogador.h"
#include "Item.h"

#define DIST_ENTRE_AS_BOLAS_X 28		// acertar isso aki depois q definir o tamanho das bolas
#define DIST_COMBO 20

#define TEMPO_ANIM_NOME 100
#define TEMPO_MSG_NA_CARA 30

using namespace std;

class MesaDeJogo
{
	private:
		vector<Bola *> *bolas;
		vector<Jogador *> *jogadores;
		Item *item;

        TTF_Font *fonte;
		vector<SDL_Surface *> *imgValorBolas;
		static vector<SDL_Surface *> *imgPontuacao;
		SDL_Color coresNomes[4];

		int guia;
		static int juiz;
		int numeroJogadores;

		static const int diametroBolas;

		bool imprimeItem;
		bool pegouItem;
        bool miraLouca;
        bool jogarDeNovo;

        static SDL_Surface *imgPontuacaoAtual;
		static bool animacaoCarregada;

		SDL_Surface *imgMensagemNaCara;
		int tempoMensagemNaCara;
		TTF_Font *fonteMsg;

		SDL_Surface *imgMsgCombo;
		TTF_Font *fonteCombo;
		int contCombo;

		void colisaoEntreBolas(Bola* a,Bola* b);
		bool detectaColisao(Bola* a, Bola* b);
		void colisaoMesa(Bola* a);
        double coeficienteDeAtrito;
        void atualizarHUD();
        void colisaoItem();

	public:
		MesaDeJogo();
		~MesaDeJogo();

		void iniciar();
		void finalizar();
		void atualizar();
		void imprimirObjetos(SDL_Surface *bufferTela);

		void gerenciarJogo(Uint8 *botoes);
		bool continuarJogo();
		void imprimirObjetos();
		//PENSAR NUM NOME MELHOR PARA ESTE MÉTODO.
		void imprimirIlustradoresPartida(SDL_Surface *bufferTela);
		void sortearAparicaoItem();
		void moverItem();

		vector<Bola* > getBolas();

		void colisaoBuracos();

		void enlouquecerMira();

        static void atualizarAnimNome();
		void testarFimDeJogo(bool cheat);

};

#endif
