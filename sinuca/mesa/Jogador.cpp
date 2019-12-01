#include "Jogador.h"

Jogador::Jogador(char* nome)
{
	this->nome = (char *) calloc(strlen(nome) + 1, sizeof(char));
	strcpy(this->nome, nome);
    this->pontuacao = 0;
    this->combos = 0;
    this->contarCombo = false;
    this->item = NULL;
}

Jogador::~Jogador()
{
	delete this->nome;

	if(imgTaco != NULL)
		SDL_FreeSurface(imgTaco);

	if(imgForca != NULL)
		SDL_FreeSurface(imgForca);

	if(imgBarraPreta != NULL)
		SDL_FreeSurface(imgBarraPreta);
}

void Jogador::carregar()
{
     imgTaco = Util::carregarImagem("./recursos/imagens/taco.PNG");

	imgForca = Util::carregarImagem("./recursos/imagens/forca.PNG");
	imgBarraPreta = Util::carregarImagem("./recursos/imagens/barraPreta.PNG");
	posForca = Vetor(275, 10);
	posBarraPreta = Vetor(275, 10);

	forca_tacada = 0;
    angulo_tacada = 180;
    teclaTacadaPressionada = false;
}

void Jogador::atualizar(Vetor posCentroBola)
{
	posTaco = posCentroBola;

	float percent = (float)forca_tacada/(float)forcaMaxima;

    posBarraPreta.x = 275 + (int)(215*percent);
}

void Jogador::atualizarAnimacao()	// concorrente
{
	SDL_Delay(TEMPO_ANIM_TACO);
	idAnimTaco++;
    idAnimTaco = (idAnimTaco > 2)? 0 : idAnimTaco;
}

char* Jogador::getNome()
{
    return this->nome;
}

int Jogador::getPontuacao()
{
     return this->pontuacao;
}

void Jogador::setPontuacao(int pontuacao)
{
    this->pontuacao = pontuacao;
}

int Jogador::getForca_Tacada()
{
    return forca_tacada;
}

void Jogador::setForca_Tacada(int forca)
{
     forca_tacada = forca;
}

int Jogador::getForcaX()
{
    return (forca_tacada)*cos(angulo_tacada*3.14/180);
}

int Jogador::getForcaY()
{
    return -1*(forca_tacada)*sin(angulo_tacada*3.14/180);
}

int Jogador::getAngulo_tacada()
{
    return angulo_tacada;
}

void Jogador::setAngulo_tacada(float angulo)
{
     angulo_tacada = angulo;
}

void Jogador::setCombos(int combos)
{
    this->combos = combos;
}

int Jogador::getCombos()
{
    return this->combos;
}

void Jogador::setContarCombo(bool cc)
{
    this->contarCombo = cc;
}

bool Jogador::getContarCombo()
{
    return this->contarCombo;
}

void Jogador::desenhar(SDL_Surface *bufferTela)
{
	const float pi = 3.14f;
    float raio = (TAM_BOLA/2) + (imgTaco->h/2) + 1;
    float posX = raio * cos(angulo_tacada * pi / 180);
    float posY = -1 * raio * sin(angulo_tacada * pi / 180);

    Vetor pos;

    for(int i = 0; i < 3; i++)
    {
        pos.x = posTaco.x + posX - (imgTaco->h/2);
        pos.y = posTaco.y + posY - (imgTaco->h/2);

        int id = (idAnimTaco == i)? 1 : 0;
        Util::aplicarImagemAnimada(pos.x, pos.y, imgTaco, bufferTela, id, 10);

        raio += imgTaco->h + 1;
        posX = raio * cos(angulo_tacada * pi / 180);
        posY = -1 * raio * sin(angulo_tacada * pi / 180);
    }

	Util::aplicarImagem(posForca.x, posForca.y, imgForca, bufferTela);
	Util::aplicarImagem(posBarraPreta.x, posBarraPreta.y, imgBarraPreta, bufferTela);
}

Item* Jogador::getItem()
{
    return this->item;
}

void Jogador::setItem(Item* item)
{
    this->item = item;
}

int Jogador::jogar(Uint8 *botoes)
{
     /*Implementando método primeiramente com a idéia de segurar o botão de tacada e depois soltar qdo tiver c a força adequada.
     Se ficar ruim de jogar, mudamos a jogabilidade.*/

     //Significa que o player acabou de soltar a tecla
     if(!botoes[SDLK_SPACE] && teclaTacadaPressionada==true)
     {
         teclaTacadaPressionada = false;
         return 1;
     }

     if(botoes[SDLK_SPACE])
     {
		  teclaTacadaPressionada = true;
          //DEFINIR A TAXA DE AUMENTO DA FORÇA
          forca_tacada+=2;
     }

     if(forca_tacada > forcaMaxima)
     {
          teclaTacadaPressionada = false;
          return 1;
     }

     //Definir taxa de mudança de ângulo
     if(botoes[SDLK_LEFT])
          angulo_tacada+=2;

     if(botoes[SDLK_RIGHT])
          angulo_tacada-=2;

     if(angulo_tacada < 0)
          angulo_tacada = 359;

     if(angulo_tacada>359)
          angulo_tacada = 0;

	return 0;
}
