#include "Item.h"
#include "MesaDeJogo.h"
#include <time.h>

//by Bob. 26/06/09

Item::Item(){
       }

Item::~Item()
{
	if(this->imagem != NULL)
		SDL_FreeSurface(imagem);
}

Item::Item(int posX, int posY, vector<Bola *> bolas, double* coefAtritoMesa, bool* miraLouca, int* miraLoucaContador){
     this->posX = posX;
     this->posY = posY;
     this->bolas = bolas;
     this->coefAtritoMesa = coefAtritoMesa;
     this->miraLouca = miraLouca;
     this->miraLoucaContador = miraLoucaContador;
     }

void Item::efeito(){
    if(this->tipo==0)
        *this->coefAtritoMesa=0.5;
    else{
        if(this->tipo==1)
            *this->coefAtritoMesa=0.01;
        else{
            if(this->tipo==2)
            {
                 for(int i=1;i<this->bolas.size();i++)
                 {
                     this->bolas.at(i)->setValor(this->bolas.size()-1);
                 }
            }else{
                if(this->tipo==3)
                {
                    for(int i=1;i<this->bolas.size();i++)
                    {
                        this->bolas.at(i)->setValor(1);
                    }
                }else{
                    if(this->tipo==4)
                    {
                        *this->miraLoucaContador++;
                    }
                }
            }
        }
    }
}

void Item::desfazerEfeito(){
    if(this->tipo==0)
        *this->coefAtritoMesa=0.14;
    else{
        if(this->tipo==1)
            *this->coefAtritoMesa=0.14;
        else{
            if(this->tipo==2)
            {
                 for(int i=1;i<this->bolas.size();i++)
                 {
                     this->bolas.at(i)->setValor(i);
                 }
            }else{
                if(this->tipo==3)
                {
                    for(int i=1;i<this->bolas.size();i++)
                    {
                        this->bolas.at(i)->setValor(i);
                    }
                }
            }
        }
    }
}

void Item::iniciar()
{
    int randNum = rand()%100;

    if(randNum <= 25)
    {
        this->tipo = 0;
        this->imagem = Util::carregarImagem("./recursos/imagens/item_massa++.PNG");
    }
    else{
        if(randNum > 25 && randNum <= 50)
        {
            this->tipo = 1;
            this->imagem = Util::carregarImagem("./recursos/imagens/item_massa--.PNG");
        }else{
            if(randNum > 50 && randNum <=65)
            {
                this->tipo = 2;
                this->imagem = Util::carregarImagem("./recursos/imagens/item_valores_bolas++.PNG");
            }else{
                if(randNum > 65 && randNum <=80)
                {
                    this->tipo = 3;
                    this->imagem = Util::carregarImagem("./recursos/imagens/item_valores_bolas--.PNG");
                }else{
                    if(randNum > 80 && randNum <=100)
                    {
                        this->tipo = 4;
                        this->imagem = Util::carregarImagem("./recursos/imagens/item_mira_louca.PNG");
                    }
                }
            }
        }
    }
}

void Item::atualizar()
{
}

void Item::desenhar(SDL_Surface *bufferTela)
{
     Util::aplicarImagem(this->posX,this->posY,this->imagem,bufferTela);
}

int Item::getPosX()
{
    return this->posX;
}

int Item::getPosY()
{
    return this->posY;
}
