#include "Bola.h"

Bola::Bola()
{
}

Bola::~Bola()
{
	/*
	if(this->imagem != NULL)
	{
		SDL_FreeSurface(this->imagem);
	}
	*/
}

Bola::Bola(Vetor posicao, int valor)
{
	this->posicao = posicao;
	this->valor = valor;

    //SÓ PARA TESTES
	this->massa = 2;
}

void Bola::carregar()
{
	imagem = Util::carregarImagem("./recursos/imagens/bolas.PNG");
}

void Bola::iniciar()
{
    this->posicaoAnterior.x = this->posicao.x;
    this->posicaoAnterior.y = this->posicao.y;
    this->velocidade.x = 0;
	this->velocidade.y = 0;
    this->estaEmJogo = true;

	this->direcao = Vetor(0.0f, 0.0f);
	this->moduloVel = 0;
}

void Bola::atualizar()
{
}

void Bola::desenhar(SDL_Surface *bufferTela)
{
	Util::aplicarImagemAnimada(this->posicao.x, this->posicao.y, imagem, bufferTela, this->valor, 32);
}

int Bola::getVelX()
{
    return this->velocidade.x;
}

int Bola::getVelY()
{
    return this->velocidade.y;
}

void Bola::setVelX(int velX)
{
    this->velocidade.x = velX;
}

void Bola::setVelY(int velY)
{
    this->velocidade.y = velY;
}

void Bola::mover(float atrito)
{
    this->posicaoAnterior.x = this->posicao.x;
    this->posicaoAnterior.y = this->posicao.y;

	if(this->moduloVel < 0)
	{
		this->velocidade = Vetor(0.0f, 0.0f);
		this->moduloVel = 0;
		this->direcao = Vetor(0.0f, 0.0f);
		return;
	}

	this->posicao.x += this->velocidade.x;
    this->posicao.y += this->velocidade.y;

	this->moduloVel = this->moduloVel - (atrito * this->massa);
	this->velocidade.x = this->direcao.x * moduloVel;
	this->velocidade.y = this->direcao.y * moduloVel;
}

SDL_Surface* Bola::getImagem()
{
    return imagem;
}

Vetor Bola::getCentro(){
    Vetor vetor(this->posicao.x+(this->imagem->h/2),this->posicao.y+(this->imagem->h/2));
    return vetor;
    }

int Bola::getMassa()
{
    return this->massa;
}

void Bola::setMassa(int massa)
{
    this->massa = massa;
}

Vetor Bola::getPosicao()
{
    return this->posicao;
}

void Bola::setPosicao(Vetor posicao)
{
    this->posicao = posicao;
}

Vetor Bola::getPosicaoAnterior()
{
    return this->posicaoAnterior;
}

void Bola::setValor(int pontuacao)
{
    this->valor = pontuacao;
}

int Bola::getValor()
{
    return this->valor;
}

void Bola::setEstaEmJogo(bool esta)
{
    this->estaEmJogo = esta;
}

bool Bola::getEstaEmJogo()
{
    return this->estaEmJogo;
}

Vetor Bola::getVelocidade()
{
	return this->velocidade;
}

void Bola::setVelocidade(Vetor velocidade)
{
	this->velocidade = velocidade;
	if(velocidade.x == 0 && velocidade.y == 0)
	{
		this->direcao = Vetor(0.0f, 0.0f);
		this->moduloVel = 0;
	}

	this->direcao = velocidade.getVetUnitario();
	this->moduloVel = velocidade.getModulo();
}

double Bola::energiaCinetica(){

       return ((this->getMassa()*pow(this->getVelocidade().getModulo(), 2))/2);
       }//calcula a e. cinética


/*
float Bola :: velocidade(int, vel_x,int vel_y){
     float velocidade;
     velocidade = sqrtf(pow(vel_x,2) + pow(vel_y,2));
     return velocidade;
     }//velocidade resultante p/ outros cálculos

double Bola :: quantidadeMovimento(int velocidade, int massa){
       double qv = velocidade*massa;
       return qv;
       }//momento linear ou quantidade de movimento
*/
/*
int Bola :: pesada(int massa){
    return massa+(this->massaExtra);
    }//aumenta a massa

int Bola :: leve(int massa){
    return massa-(this->massaExtra);
    }//diminui a massa

//VERIFICAR A NECESSIDADE DESSE MÉTODO
double Bola :: atrito(int velocidade){
       return = velocidde*(this->coef);
       }//coloca atrito

*/
