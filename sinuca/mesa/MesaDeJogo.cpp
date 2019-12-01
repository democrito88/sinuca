#include "MesaDeJogo.h"
#include <math.h>
#include <time.h>
#include "../telas/GerenciadorTelas.h"

MesaDeJogo::MesaDeJogo()
{
	this->fonte = NULL;
	this->item = NULL;
	this->imgPontuacao = NULL;
	this->bolas = NULL;
	this->jogadores = NULL;
}

MesaDeJogo::~MesaDeJogo()
{
}

void MesaDeJogo::finalizar()			// é chamado em TelaJogo::aoSair()
{

	if(this->bolas != NULL)
	{
		SDL_FreeSurface(Bola::getImagem());
		this->bolas->clear();
		delete this->bolas;
	}

	if(this->jogadores != NULL)
	{
		this->jogadores->clear();
		delete this->jogadores;
	}

	/*
	if(this->item != NULL)
		delete this->item;
	*/

	TTF_CloseFont(this->fonte);
	TTF_CloseFont(this->fonteCombo);
	TTF_CloseFont(this->fonteMsg);

	if(this->imgPontuacao != NULL)
	{
		for(int i=0; i< this->imgPontuacao->size(); i++)
			SDL_FreeSurface(this->imgPontuacao->at(i));

		delete this->imgPontuacao;
	}

	if(this->imgValorBolas != NULL)
	{
		for(int i=0; i< this->imgValorBolas->size(); i++)
			SDL_FreeSurface(this->imgValorBolas->at(i));

		delete this->imgValorBolas;
	}

	if(imgPontuacaoAtual != NULL)
		SDL_FreeSurface(this->imgPontuacaoAtual);

	if(imgMensagemNaCara != NULL)
		SDL_FreeSurface(this->imgMensagemNaCara);

	if(imgMsgCombo != NULL)
		SDL_FreeSurface(this->imgMsgCombo);
}

void MesaDeJogo::iniciar()		// é chamado em TelaJogo::aoEntrar()
{
    srand(time(NULL));
	this->fonte = TTF_OpenFont("./recursos/fontes/comic.ttf", 12);
	SDL_Color cores[4] = { {255, 0, 0}, {0, 255, 0}, {50, 50, 255}, {255, 255, 0} };
	for(int i=0; i < 4; i++)
		this->coresNomes[i] = cores[i];
	this->guia = -1;
	this->juiz = 0;
	this->imprimeItem = false;
    this->pegouItem = false;
    this->miraLouca=false;
    this->jogarDeNovo = false;

	Bola::carregar();			// carrega a imagem das bolas

	this->bolas = new vector<Bola *>(16);

	//VALOR SETADO APENAS PARA TESTES
	this->numeroJogadores = GerenciadorTelas::getQtdJogadores();;
	this->jogadores = new vector<Jogador *>(this->numeroJogadores);

	char nomes[4][20] = {"Gammer Um", "Gammer Dois", "Gammer Tres", "Gammer Quatro"};
	for(int i=0;i<numeroJogadores;i++)
	{
	    this->jogadores->at(i) = new Jogador(nomes[i]);
	}
	Jogador::carregar();

	this->bolas->at(0) = new Bola(Vetor(575, 284), 0);

	int variacaoX = 70;
	int variacaoY = 220;
	for(int i = 1; i < 6; i++)
	{
		this->bolas->at(i) = new Bola(Vetor(variacaoX, variacaoY), i);
		variacaoY += 33;
	}
	variacaoX += DIST_ENTRE_AS_BOLAS_X;
	variacaoY = 220 + 16;
	for(int i = 6; i < 10; i++)
	{
		this->bolas->at(i) = new Bola(Vetor(variacaoX, variacaoY), i);
		variacaoY += 33;
	}
	variacaoX += DIST_ENTRE_AS_BOLAS_X;
	variacaoY = 220 + 16 + 16;
	for(int i = 10; i < 13; i++)
	{
		this->bolas->at(i) = new Bola(Vetor(variacaoX, variacaoY), i);
		variacaoY += 33;
	}
	variacaoX += DIST_ENTRE_AS_BOLAS_X;
	variacaoY = 220 + 16 + 16 + 16;
	for(int i = 13; i < 15; i++)
	{
		this->bolas->at(i) = new Bola(Vetor(variacaoX, variacaoY), i);
		variacaoY += 33;
	}
	variacaoX += DIST_ENTRE_AS_BOLAS_X;
	variacaoY = 220 + 16 + 16 + 16 + 16;
	this->bolas->at(15) = new Bola(Vetor(variacaoX, variacaoY), 15);

	for(int i=0;i<this->bolas->size();i++)
	{
	    this->bolas->at(i)->iniciar();
	}

    /////////// HUD /////////////
	this->imgPontuacao = new vector<SDL_Surface *>(this->numeroJogadores);		// jogadores.size()
	for(int i = 0; i < this->numeroJogadores; i++)							// pegar o nome dos jogadores
	{
		std::stringstream nome;
		nome << this->jogadores->at(i)->getNome() << ": " << this->jogadores->at(i)->getPontuacao();
		this->imgPontuacao->at(i) = TTF_RenderText_Solid(this->fonte, nome.str().c_str(), this->coresNomes[i]);
	}

	this->imgValorBolas = new vector<SDL_Surface *>(16);

	SDL_Color cor = {255, 255, 255};
	for(int i = 0; i < 16; i++) // 15 bolas
	{
		std::stringstream valor;
		valor << i;
		this->imgValorBolas->at(i) = TTF_RenderText_Solid(this->fonte, valor.str().c_str(), cor);
	}

    this->coeficienteDeAtrito = 0.1f;

	this->imgMensagemNaCara = NULL;
	this->tempoMensagemNaCara = 0;
	this->fonteMsg = TTF_OpenFont("./recursos/fontes/corpse.ttf", 42);

	this->fonteCombo = TTF_OpenFont("./recursos/fontes/comic.ttf", 18);
	this->imgMsgCombo = TTF_RenderText_Solid(this->fonteCombo, "Combo X1", cor);
	this->contCombo = 1;

	this->imgPontuacaoAtual = NULL;
	this->animacaoCarregada = false;
}

void MesaDeJogo::atualizar()
{
	Jogador::atualizar(this->bolas->at(0)->getCentro());	// atualiza o taco
}

//Haverá uma variavel chamada guia q indicará o q o jogo executará
void MesaDeJogo::gerenciarJogo(Uint8 *botoes)
{

     if(this->guia==-1)
     {
         Item* temp = this->jogadores->at(juiz)->getItem();

         if(temp != NULL)
            temp->efeito();


         this->jogadores->at(juiz)->setContarCombo(false);

         this->sortearAparicaoItem();
         this->pegouItem = false;
         this->guia = 0;
     }

     //imaginei uma variavel "juiz" p dizer d quem eh a vez de jogar
     //a classe Jogador poderia ter no metodo jogar() um retorno 1 ou 0.
     //1 para dizer q pode prosseguir c os calculos do jogo
     //0 p dizer q ainda está regulando angulação e força
     //Qdo o jogador definisse o angulo e a força da jogada, o método retornaria 1

     if(this->guia==0)
     {
          this->moverItem();
          guia = jogadores->at(juiz)->jogar(botoes);

		  if(this->miraLouca == true)
            this->enlouquecerMira();
     }

     //Imprimindo força em cima da bola branca
     //A bola branca poderia ser o elemento 0 do array de bolas
     //A classe jogador teria 2 atributos: força x e força y
     //Estes seriam setados quando fosse concluido o estagio da jogada

	 /*
         this->jogadores->at(2)->setPontuacao(this->jogadores->at(juiz)->getAngulo_tacada());
         this->jogadores->at(3)->setPontuacao(this->guia);
	*/

     if(this->guia==1)
     {
         this->moverItem();
		   ControleSom::tocar(ControleSom::efeitoTacada);
           float velX = this->bolas->at(0)->getVelX() + (this->jogadores->at(juiz)->getForcaX())/this->bolas->at(0)->getMassa();
           float velY = this->bolas->at(0)->getVelY() + (this->jogadores->at(juiz)->getForcaY())/this->bolas->at(0)->getMassa();
		   this->bolas->at(0)->setVelocidade(Vetor(velX, velY));
           this->guia++;
     }


    if(this->guia==2)
    {

        this->moverItem();
          int i,j;

          //Método usará as atuais velocidades para somar às posições
          for(i=0;i<this->bolas->size();i++)
          {
            if(this->bolas->at(i)->getEstaEmJogo())
            {
                this->bolas->at(i)->mover(this->coeficienteDeAtrito);
            }
          }

          for(i=0;i<this->bolas->size();i++)
          {

            if(this->bolas->at(i)->getEstaEmJogo())
            {
               for(j=i;j<this->bolas->size();j++)
               {
                if(this->bolas->at(j)->getEstaEmJogo())
                {
                     if(i!=j)
                     {
                             //O método deve setar as novas velocidades nas bolas q colidirem
                             this->colisaoEntreBolas(this->bolas->at(i),this->bolas->at(j));
                     }
                }
               }
            }
          }

          //Método que fará a detecção de colisão das bolas com a mesa
          for(i=0;i<this->bolas->size();i++)
          {
                this->colisaoMesa(this->bolas->at(i));
          }

           this->colisaoBuracos();

          if(this->continuarJogo())
            this->guia++;
     }

     //this->imprimirObjetos();

     //passa a vez para o próximo
     if(this->guia==3)
     {
        if(this->jogadores->at(juiz)->getContarCombo() == false)
        {
             this->jogadores->at(juiz)->setCombos(0);
             this->jogarDeNovo = false;
        }

        this->guia=-1;
        this->jogadores->at(juiz)->setForca_Tacada(0);
        this->jogadores->at(juiz)->setAngulo_tacada(180);
        this->imprimeItem = false;

        if(this->jogadores->at(juiz)->getItem() != NULL)
        {
             this->jogadores->at(juiz)->getItem()->desfazerEfeito();
             this->miraLouca = false;
             this->jogadores->at(juiz)->setItem(NULL);
        }

        if(this->pegouItem == true)
            this->jogadores->at(juiz)->setItem(item);

		if(this->jogarDeNovo==false)
		{
	        this->juiz++;

			SDL_Color corMsg = {255, 255, 255};
			this->contCombo = 1;

			if(this->imgMsgCombo != NULL)
				SDL_FreeSurface(this->imgMsgCombo);
			this->imgMsgCombo = TTF_RenderText_Solid(this->fonteCombo, "Combo X1", corMsg);
		}

		testarFimDeJogo(false);
     }
     if(this->juiz>=this->numeroJogadores)
         this->juiz = 0;

     this->atualizarHUD();

}

void MesaDeJogo::moverItem()
{
        if(this->imprimeItem==true)
        {
            if(this->item->getPosX()<=70)
            {
                this->item->setVel(Vetor(this->item->getVel().x*(-1),this->item->getVel().y));
            }

            if(this->item->getPosX()>=730-50)
            {
                this->item->setVel(Vetor(this->item->getVel().x*(-1),this->item->getVel().y));
            }

            if(this->item->getPosY()<=111)
            {
                this->item->setVel(Vetor(this->item->getVel().x,this->item->getVel().y*(-1)));
            }

            if(this->item->getPosY()>=488-20)
            {
                this->item->setVel(Vetor(this->item->getVel().x,this->item->getVel().y*(-1)));
            }

            this->item->mover();
            this->colisaoItem();
        }
}

//Método que será chamado o tempo todo p sortear a aparição de um item
void MesaDeJogo::sortearAparicaoItem()
{
    int num = rand()%100;
    bool sair = false;
    Bola temp;

    if(num>=80)
    {
        this->imprimeItem = true;
        while(sair==false)
        {
            this->item = new Item(70 + rand()%600, 111 + rand()%300, (this->bolas), &this->coeficienteDeAtrito, &this->miraLouca);
            this->item->iniciar();

            Vetor temp2(this->item->getPosX(),this->item->getPosY());
            temp = Bola(temp2,-1);

            if(detectaColisao(this->bolas->at(0), &temp))
                sair = false;
            else
                sair = true;
        }
    }
    else
        this->imprimeItem = false;
}

void MesaDeJogo::enlouquecerMira()
{
    int num = rand()%4;

    if(num<=1)
        this->jogadores->at(juiz)->setAngulo_tacada(this->jogadores->at(juiz)->getAngulo_tacada()-4);
    else
        this->jogadores->at(juiz)->setAngulo_tacada(this->jogadores->at(juiz)->getAngulo_tacada()+4);
}

void MesaDeJogo::atualizarHUD()
{
	/*
    /////////// HUD /////////////
	for(int i = 0; i < 4; i++)							// pegar o nome dos jogadores
	{
		std::stringstream nome;
		nome << this->jogadores->at(i)->getNome() << ": " << this->jogadores->at(i)->getPontuacao();
		this->imgPontuacao->at(i) = TTF_RenderText_Solid(this->fonte, nome.str().c_str(), this->coresNomes[i]);
	}

	std::stringstream nome;
	nome << this->bolas->at(0)->getMassa() << "   " << this->bolas->at(0)->getVelX() << this->bolas->at(0)->getVelY() << "   " << this->bolas->at(1)->getVelX() << this->bolas->at(1)->getVelY() << "   " << this->jogadores->at(juiz)->getForcaX() << this->jogadores->at(juiz)->getForcaY();
	this->imgPontuacao->at(0) = TTF_RenderText_Solid(this->fonte, nome.str().c_str(), this->coresNomes[0]);
	*/
}


//Método que verifica se todas as bolas já estão paradas para continuar o jogo
bool MesaDeJogo::continuarJogo()
{
     int i;
     for(i=0;i<this->bolas->size();i++)
     {
           if(this->bolas->at(i)->getVelX()!=0 || this->bolas->at(i)->getVelY()!=0)
                 break;
     }

     if(i<this->bolas->size())
          return false;
     else
          return true;
}

bool MesaDeJogo::detectaColisao(Bola* a, Bola* b){
    double dist;
    dist = sqrt(pow(a->getCentro().x - b->getCentro().x,2)+pow(a->getCentro().y - b->getCentro().y,2));
    if(dist <= (a->getImagem()->h/2)+(b->getImagem()->h/2)){
        return true;
        }
    else
        return false;
    }

void MesaDeJogo::colisaoItem()
{
    Vetor temp2(this->item->getPosX(),this->item->getPosY());
    Bola temp(temp2,-1);

    if(detectaColisao(this->bolas->at(0), &temp))
    {
        this->imprimeItem = false;
        this->pegouItem = true;

		ControleSom::tocar(ControleSom::efeitoItem);

		string txtMsg = "";

		switch(this->item->getTipo())
		{
			case ITEM_ATRITO_MAIS: txtMsg = "MAIS ATRITO!!!"; break;
			case ITEM_ATRITO_MENOS: txtMsg = "MENOS ATRITO!!!"; break;
			case ITEM_VALORES_MAX: txtMsg = "TODAS AS BOLAS COM 15 PONTOS!!!"; break;
			case ITEM_VALORES_MIN: txtMsg = "TODAS AS BOLAS COM 1 PONTO!!!"; break;
			case 4: txtMsg = "MIRA LOUCA!!!"; break;
			default: break;
		}

		SDL_Color corMsg = {255, 255, 255};

		if(this->imgMensagemNaCara != NULL)
			SDL_FreeSurface(this->imgMensagemNaCara);

		this->imgMensagemNaCara = TTF_RenderText_Solid(this->fonteMsg, txtMsg.c_str(), corMsg);
		this->tempoMensagemNaCara = TEMPO_MSG_NA_CARA;
    }
}

void MesaDeJogo::colisaoEntreBolas(Bola* a,Bola* b)
{
    int totalEnergia = (a->energiaCinetica() + b->energiaCinetica());

    if(detectaColisao(a, b))
	{
		//	COMENTEI PQ FIQUEI COM MEDO DESSES CÁLCULOS! =P
		//  ¬¬' Pô Bio, tu faz a bagaça e ainda fica com medo...
        /*float angulo;

        int distX2,distY2;

        distX2 = a->getPosicaoAnterior().x - b->getPosicaoAnterior().x;
        distY2 = -1*(a->getPosicaoAnterior().y - b->getPosicaoAnterior().y);

        if(distX2 == 0)
            distX2 = 1;

        if(distY2 == 0)
            distY2 = 1;

		angulo = atanf(distY2/distX2);
        const float pi = 3.14f;

        if(distY2 < 0 && distX2 < 0)
            angulo+=pi;
        else{
            if(distY2 >= 0 && distX2 < 0)
                angulo+=pi;         //repetido!?
        }


        float raio = (a->getImagem()->h/2) + (b->getImagem()->h/2) + 1;
        float posX = raio * cos(angulo);
        float posY = -1 * raio * sin(angulo);

        Vetor pos;

        pos.x = b->getPosicao().x + posX;
        pos.y = b->getPosicao().y + posY;

        a->setPosicao(pos);
*/


		//ESSE É O Q TAVA ANTES
/*
        double distTotal = sqrt(pow(a->getCentro().x - b->getCentro().x,2)+pow(a->getCentro().y - b->getCentro().y,2));
        int distX = a->getPosicao().x - b->getPosicao().x;
        int distY = a->getPosicao().y - b->getPosicao().y;
        //setar as novas velocidades
        float velX = a->getVelX()+( totalEnergia*0.04*(distX/distTotal) );
        float velY = a->getVelY()+( totalEnergia*0.04*(distY/distTotal) );
        a->setVelocidade(Vetor(velX, velY));

        velX = b->getVelX()+( totalEnergia*0.04*(distX/distTotal)*(-1) );
        velY = b->getVelY()+( totalEnergia*0.04*(distY/distTotal)*(-1) );
        b->setVelocidade(Vetor(velX, velY));
*/

        //if((a->getVelocidade().getModulo() > 1) || (a->getVelocidade().getModulo() > 1))
		ControleSom::tocar(ControleSom::efeitoColisao);

		double aceleracao = 10;

        double distTotal = sqrt(pow(a->getCentro().x - b->getCentro().x,2)+pow(a->getCentro().y - b->getCentro().y,2));
        int distX = a->getPosicao().x - b->getPosicao().x;
        int distY = a->getPosicao().y - b->getPosicao().y;
        //setar as novas velocidades
        float velX = a->getVelX()+( aceleracao*(distX/distTotal) );
        float velY = a->getVelY()+( aceleracao*(distY/distTotal) );
        a->setVelocidade(Vetor(velX, velY));

        velX = b->getVelX()+( aceleracao*(distX/distTotal)*(-1) );
        velY = b->getVelY()+( aceleracao*(distY/distTotal)*(-1) );
        b->setVelocidade(Vetor(velX, velY));

	}
}
//Método de colisão c a mesa
//Existirá um atributo de conservação de enregia em colisões c a mesa nessa classe
//VALORES DESSE MÉTODO SETADOS APENAS PARA TESTES
void MesaDeJogo::colisaoMesa(Bola* a)
{
    if(a->getEstaEmJogo())
    {
     if(a->getPosicao().x<=70)
     {
            Vetor novaPosicao;
            if(a->getVelX()!=0)
                novaPosicao = Vetor(70,a->getPosicao().y + (a->getVelY()/a->getVelX())*(70 - a->getPosicao().x));
            else
                novaPosicao = Vetor(70,a->getPosicao().y);

            a->setPosicao(novaPosicao);
            float velX = a->getVelX()*(-1)*0.8;
			a->setVelocidade(Vetor(velX, a->getVelocidade().y));

			if(abs(velX) > 5)
				ControleSom::tocar(ControleSom::efeitoMesa);
     }

     if(a->getPosicao().x>=730-diametroBolas)
     {
            Vetor novaPosicao;
            if(a->getVelX()!=0)
                novaPosicao = Vetor(730-diametroBolas,a->getPosicao().y + -1*(a->getVelY()/a->getVelX())*(a->getPosicao().x - (730-diametroBolas)));
            else
                novaPosicao = Vetor(730-diametroBolas,a->getPosicao().y);

            a->setPosicao(novaPosicao);
            float velX = a->getVelX()*(-1)*0.8;
			a->setVelocidade(Vetor(velX, a->getVelocidade().y));

			if(abs(velX) > 5)
				ControleSom::tocar(ControleSom::efeitoMesa);
     }

     if(a->getPosicao().y<=111)
     {
            Vetor novaPosicao;
            if(a->getVelY()!=0)
                novaPosicao = Vetor(a->getPosicao().x + (a->getVelX()/a->getVelY())*(111 - a->getPosicao().y),111);
            else
                novaPosicao = Vetor(a->getPosicao().x,100);

            a->setPosicao(novaPosicao);
            float velY = a->getVelY()*(-1)*0.8;
			a->setVelocidade(Vetor(a->getVelocidade().x, velY));

			if(abs(velY) > 5)
				ControleSom::tocar(ControleSom::efeitoMesa);
     }

     if(a->getPosicao().y>=488-diametroBolas)
     {
            Vetor novaPosicao;
            if(a->getVelY()!=0)
                novaPosicao = Vetor(a->getPosicao().x + -1*(a->getVelX()/a->getVelY())*(a->getPosicao().y - (488-diametroBolas)),488-diametroBolas);
            else
                novaPosicao = Vetor(a->getPosicao().x,488-diametroBolas);

            a->setPosicao(novaPosicao);
            float velY = a->getVelY()*(-1)*0.8;
			a->setVelocidade(Vetor(a->getVelocidade().x, velY));

			if(abs(velY) > 5)
				ControleSom::tocar(ControleSom::efeitoMesa);
     }
    }
}

void MesaDeJogo::colisaoBuracos()
{
    /*
    Vetor pos(40,80);
    Vetor pos2(376,80);
    Vetor pos3(707,80);
    Vetor pos4(707,495);
    Vetor pos5(376,495);
    Vetor pos6(40,495);
    Bola* buraco = new Bola(pos,0);
    Bola* buraco2 = new Bola(pos2,0);
    Bola* buraco3 = new Bola(pos3,0);
    Bola* buraco4 = new Bola(pos4,0);
    Bola* buraco5 = new Bola(pos5,0);
    Bola* buraco6 = new Bola(pos6,0);
    buraco->carregar();
    buraco2->carregar();
    buraco3->carregar();
    buraco4->carregar();
    buraco5->carregar();
    buraco6->carregar();
    int i;

    for(i=0;i<this->bolas->size();i++)
    {
	    if(this->bolas->at(i)->getEstaEmJogo())
	    {
            if(detectaColisao(this->bolas->at(i),buraco) || detectaColisao(this->bolas->at(i),buraco2) || detectaColisao(this->bolas->at(i),buraco3) || detectaColisao(this->bolas->at(i),buraco4) || detectaColisao(this->bolas->at(i),buraco5) || detectaColisao(this->bolas->at(i),buraco6))
            {
                if(i==0)
                {
                    this->bolas->at(0)->setPosicao(Vetor(575, 284));
                    this->bolas->at(0)->setVelocidade(Vetor(0.0f, 0.0f));
                    this->jogadores->at(juiz)->setPontuacao(this->jogadores->at(juiz)->getPontuacao() - 5);
                }else{
                    this->jogadores->at(juiz)->setPontuacao(this->jogadores->at(juiz)->getPontuacao() + this->bolas->at(i)->getValor());
                    this->bolas->at(i)->setVelocidade(Vetor(0.0f, 0.0f));
                    this->bolas->at(i)->setEstaEmJogo(false);
                }
            }
	    }
    }

    free(buraco);
    free(buraco2);
    free(buraco3);
    free(buraco4);
    free(buraco5);
    free(buraco6);*/


    int i;
    int posX = 50 , posY = 91;
    vector<Bola> buracos(6);

    for(i=0; i<3; i++){
        Vetor pos(posX,posY);
        buracos.at(i) = Bola(pos, 0);
        posX += 334;
    }

    posX = 50;
    posY = 476;

    for(i=3; i<6; i++){
        Vetor pos(posX,posY);
        buracos.at(i) = Bola(pos, 0);
        posX += 334;
    }

    bool combo = false;
	SDL_Color corMsg = {255, 255, 255};

    for(i=0;i<this->bolas->size();i++){

        if(this->bolas->at(i)->getEstaEmJogo()){
            int j;

            for(j=0; j<6; j++){

                if( detectaColisao(this->bolas->at(i), &buracos.at(j)) ){

                    if(i==0)
                    {
                        this->bolas->at(0)->setPosicao(Vetor(575, 284));
                        this->bolas->at(0)->setVelocidade(Vetor(0.0f, 0.0f));
                        this->jogadores->at(juiz)->setPontuacao(this->jogadores->at(juiz)->getPontuacao()/2);
                    }else{
                        combo = true;
                        this->jogadores->at(juiz)->setCombos(this->jogadores->at(juiz)->getCombos()+1);
                        this->jogadores->at(juiz)->setPontuacao(this->jogadores->at(juiz)->getPontuacao() + this->bolas->at(i)->getValor()*this->jogadores->at(juiz)->getCombos());
                        this->bolas->at(i)->setVelocidade(Vetor(0.0f, 0.0f));
                        this->bolas->at(i)->setEstaEmJogo(false);

						this->contCombo++;
						stringstream txtCombo;
						txtCombo << "Combo X" << this->contCombo;

						if(this->imgMsgCombo != NULL)
							SDL_FreeSurface(this->imgMsgCombo);
						this->imgMsgCombo = TTF_RenderText_Solid(this->fonteCombo, txtCombo.str().c_str(), corMsg);
                    }
					ControleSom::tocar(ControleSom::efeitoEncacapada);

					string txtMsg = "";
					if(i == 0)
						txtMsg = "OPS!!!";
					else
						txtMsg = "BOLA NO BURACO!!!";

					if(this->imgMensagemNaCara != NULL)
						SDL_FreeSurface(this->imgMensagemNaCara);
					this->imgMensagemNaCara = TTF_RenderText_Solid(this->fonteMsg, txtMsg.c_str(), corMsg);
					this->tempoMensagemNaCara = TEMPO_MSG_NA_CARA;

					char ponto[50];
					sprintf(ponto, "%s: %d", this->jogadores->at(juiz)->getNome(), this->jogadores->at(juiz)->getPontuacao());

					if(this->imgPontuacao->at(juiz) != NULL)
						SDL_FreeSurface(this->imgPontuacao->at(juiz));
                    this->imgPontuacao->at(juiz) = TTF_RenderText_Solid(this->fonte, ponto, this->coresNomes[juiz]);
                }
            }
        }
    }

    if(combo == true)
    {
        this->jogarDeNovo = true;
        this->jogadores->at(juiz)->setContarCombo(true);
    }

}

void MesaDeJogo::imprimirObjetos(SDL_Surface *bufferTela)
{
    if(this->imprimeItem == true)
        this->item->desenhar(bufferTela);

	if(this->guia != 2)			// só desenha o taco antes da tacada
		Jogador::desenhar(bufferTela);

	for(int i = 0; i < this->bolas->size(); i++)
	{
	    if(this->bolas->at(i)->getEstaEmJogo())
	    {
            Bola *bola = this->bolas->at(i);
            bola->desenhar(bufferTela);

            if( (i > 0) && (this->guia != 2) )	// só imprime os valores antes da tacada
            {
                SDL_Surface *valor = this->imgValorBolas->at(bola->getValor());
                float posX = bola->getCentro().x - (valor->w/2);
                float posY = bola->getCentro().y - (valor->h/2);
                Util::aplicarImagem(posX, posY, valor, bufferTela);
            }
	    }
	}

	this->imprimirIlustradoresPartida(bufferTela);
}

void MesaDeJogo::imprimirIlustradoresPartida(SDL_Surface *bufferTela)
{
	Vetor coords[4] = {Vetor(30, 25), Vetor(600, 25), Vetor(30, 550), Vetor(600, 550)};

	for(int i=0; i<this->numeroJogadores; i++)
	{
		if(i == this->juiz)
		{
			if(this->animacaoCarregada)
				Util::aplicarImagem( coords[i].x, coords[i].y, imgPontuacaoAtual, bufferTela );
			Util::aplicarImagem( coords[i].x, coords[i].y + DIST_COMBO, imgMsgCombo, bufferTela );
		}
		else
			Util::aplicarImagem( coords[i].x, coords[i].y, imgPontuacao->at(i), bufferTela );
	}

	if(this->tempoMensagemNaCara <= 0)
		this->tempoMensagemNaCara = 0;
	else
	{
		Util::aplicarImagem( 400 - (this->imgMensagemNaCara->w/2), 300 - (this->imgMensagemNaCara->h/2), this->imgMensagemNaCara, bufferTela );
		this->tempoMensagemNaCara--;
	}
}

vector<Bola* > MesaDeJogo::getBolas()
{
    return *(this->bolas);
}

void MesaDeJogo::atualizarAnimNome()
{
	static float zoom = 1.0f;
	static int sentido = 1;

	SDL_Delay(TEMPO_ANIM_NOME);
	if(imgPontuacaoAtual != NULL)
	{
		animacaoCarregada = false;
		SDL_FreeSurface(imgPontuacaoAtual);
	}
	imgPontuacaoAtual = zoomSurface(imgPontuacao->at(juiz), zoom, zoom, 1);
	animacaoCarregada = true;

	if(zoom > 1.5f)
		sentido = -1;
	else if(zoom < 1)
		sentido = 1;

	zoom = zoom + sentido*0.1;
}

void MesaDeJogo::testarFimDeJogo(bool cheat)
{
	if(!cheat)
	{
		for(int i=0; i < this->bolas->size(); i++)
		{
			if(i == 0)
				continue;
			if(this->bolas->at(i)->getEstaEmJogo())
			{
				return;
			}
		}
	}

	int vencedor = 1;
	int maxPontos = -1;

	for(int i=0; i < this->jogadores->size(); i++)
	{
		if(this->jogadores->at(i)->getPontuacao() > maxPontos)
		{
			maxPontos = this->jogadores->at(i)->getPontuacao();
			vencedor = i+1;
		}
	}

	GerenciadorTelas::setVencedor(vencedor);

	SDL_Delay(1000);
	GerenciadorTelas::mudarTela(GerenciadorTelas::telaFim);
}
