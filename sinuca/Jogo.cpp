#include "Jogo.h"

// inicialização de atributos estáticos
TelaJogo *GerenciadorTelas::telaJogo = new TelaJogo();
TelaMenu *GerenciadorTelas::telaMenu = new TelaMenu();
TelaOpcoesJogadores *GerenciadorTelas::telaOpcoesJogadores = new TelaOpcoesJogadores();
TelaTutorial *GerenciadorTelas::telaTutorial = new TelaTutorial();
TelaFim *GerenciadorTelas::telaFim = new TelaFim();
TelaCreditos *GerenciadorTelas::telaCreditos = new TelaCreditos();
Tela *GerenciadorTelas::telaAtual = NULL;

int GerenciadorTelas::qtdJogadores = 1;
int GerenciadorTelas::vencedor = 1;
bool GerenciadorTelas::rodando = true;

bool TelaJogo::jogoRodando = false;

SDL_Surface *Bola::imagem = NULL;

const int Jogador::forcaMaxima = 50;
const int MesaDeJogo::diametroBolas = 32;

// JOGADOR
SDL_Surface *Jogador::imgTaco = NULL;
Vetor Jogador::posTaco;
int Jogador::idAnimTaco = 0;
int Jogador::forca_tacada = 0;
float Jogador::angulo_tacada = 180;
bool Jogador::teclaTacadaPressionada = false;
// BARRA DE FORÇA
SDL_Surface *Jogador::imgForca = NULL;
SDL_Surface *Jogador::imgBarraPreta = NULL;
Vetor Jogador::posForca;
Vetor Jogador::posBarraPreta;

// MesaDeJogo
SDL_Surface *MesaDeJogo::imgPontuacaoAtual = NULL;
vector<SDL_Surface *> *MesaDeJogo::imgPontuacao = NULL;
int MesaDeJogo::juiz = 0;
bool MesaDeJogo::animacaoCarregada = false;

// ControleSom
Mix_Music *ControleSom::musicaAtual = NULL;
Mix_Chunk *ControleSom::efeitoTacada = NULL;
Mix_Chunk *ControleSom::efeitoColisao = NULL;
Mix_Chunk *ControleSom::efeitoEncacapada = NULL;
Mix_Chunk *ControleSom::efeitoSelecao = NULL;
Mix_Chunk *ControleSom::efeitoBotao = NULL;
Mix_Chunk *ControleSom::efeitoMesa = NULL;
Mix_Chunk *ControleSom::efeitoItem = NULL;
int ControleSom::canal = 0;

Jogo::Jogo()
{
	this->gerenciadorTelas = new GerenciadorTelas();
}

void Jogo::iniciar(SDL_Surface *bufferTela)
{
	this->gerenciadorTelas->iniciar();
	this->bufferTela = bufferTela;
	ControleSom::carregar();
}

void Jogo::controle(Uint8 *botoes)
{
	this->gerenciadorTelas->controle(botoes);
}

void Jogo::atualizar()
{
	this->gerenciadorTelas->atualizar();
}

void Jogo::desenhar()
{
	this->gerenciadorTelas->desenhar(this->bufferTela);
}
