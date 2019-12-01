//NESTE ARQUIVO EST�O APENAS IMPLEMENTADOS OS M�TODOS QUE SER�O USADOS NA CLASSE MESA DE JOGO, A QUAL SER� IMPLEMENTADA POR DENIS

//Haver� uma variavel chamada guia q indicar� o q o jogo executar�
void MesaDeJogo::gerenciarJogo()
{
     //imaginei uma variavel "juiz" p dizer d quem eh a vez de jogar
     //a classe Jogador poderia ter no metodo jogar() um retorno 1 ou 0.
     //1 para dizer q pode prosseguir c os calculos do jogo
     //0 p dizer q ainda est� regulando angula��o e for�a
     //Qdo o jogador definisse o angulo e a for�a da jogada, o m�todo retornaria 1
     
     if(this->guia==0)
     {
          guia = jogadores[juiz]->jogar();
     }
     
     //Imprimindo for�a em cima da bola branca
     //A bola branca poderia ser o elemento 0 do array de bolas
     //A classe jogador teria 2 atributos: for�a x e for�a y
     //Estes seriam setados quando fosse concluido o estagio da jogada
     if(this->guia==1)
     {
           this->bolas[0]->setVelX(bolas[0]->getVelX + (this->jogadores[juiz]->getForcaX())/this->bolas[0]->getMassa());
           this->bolas[0]->setVelY(bolas[0]->getVelY + (this->jogadores[juiz]->getForcaY())/this->bolas[0]->getMassa());
           this->guia++;
     }
     
     if(this->guia==2)
     {
          int i,j;     
          for(i=0;i<this->bolas->size();i++)
          {
               for(j=0;j<this->bolas->size();j++)
               {
                     if(i!=j)
                     {
                             //O m�todo deve setar as novas velocidades nas bolas q colidirem
                             this->colisaoEntreBolas(this->bolas[i],this->bolas[j]);
                     }
               }
          }
          
          //M�todo que far� a detec��o de colis�o das bolas com a mesa
          for(i=0;i<this->bolas->size();i++)
          {
                this->bolas[i]->colisaoMesa(this->bolas[i]);
          }  
          
          //M�todo usar� as atuais velocidades para somar �s posi��es
          for(i=0;i<this->bolas->size();i++)
          {
                this->bolas[i]->mover();
          }          
          
          //Distribuindo o efeito do atrito p todas as bolas
          //Existir� um atributo coeficiente de atrito (0->1)
          for(i=0;i<this->bolas->size();i++)
          {
                this->bolas[i]->setVelX(bolas[i]->getVelX*this->coeficienteDeAtrito);
                this->bolas[i]->setVelY(bolas[i]->getVelY*this->coeficienteDeAtrito);
          }
          this->guia++;
     }
     
     this->imprimirObjetos();
     
     //passa a vez para o pr�ximo
     this->juiz++;
     
     if(this->juiz>this->numeroJogadores)
         this->juiz = 0;
         
     this->guia=0;
     
}

//M�todo que verifica se todas as bolas j� est�o paradas para continuar o jogo
bool MesaDeJogo::continuarJogo()
{
     int i;
     for(i=0;i<this->bolas->size();i++)
     {
           if(this->bolas[i]->getVelX()!=0 && this->bolas[i]->getVelY()!=0)
                 break;
     }
     
     if(i<this->bolas->size())
          return false;
     else
          return true;
}

void MesaDeJogo::colisaoEntreBolas(Bola* a,Bola* b)
{
}

//M�todo de colis�o c a mesa
//Existir� um atributo de conserva��o de enregia em colis�es c a mesa nessa classe
void MesaDeJogo::colisaoMesa(Bola* a)
{
     if(a->getPosX()<=0 || a->getPosX()>=this->res_horizontal-/*largura da textura*/)
     {
            a->setVelX(a->getVelX()*(-1)*this->percentagem_conservacao_energia);
     }
          
     if(a->getPosY()<=0 || a->getPosY()>=this->res_vertical-/*altura da textura*/)
     {
            a->setVelY(a->getVelY()*(-1)*this->percentagem_conservacao_energia);
     }
}

void MesaDeJogo::imprimirObjetos()
{
}
