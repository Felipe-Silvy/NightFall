#include "Jogo.h"
#include "Entidade.h"

NightFall::Jogo::Jogo() : pJog1(), GG(), MenuJogo(), Fase1() // SOBRECARGA COM PARAMETROS TLVZ
{
    Ente::setGG(&GG);
    MenuJogo.setJogo(this);
    MenuJogo.setGerGrafico(&GG);
    executar();
}

NightFall::Jogo::~Jogo() {}

void NightFall::Jogo::executar()
{
    pJog1.setTextura("Jogador");

    MenuJogo.executar();
}

void NightFall::Jogo::iniciarFase1()
{
    Fase1.setJogador(&pJog1); // passar parametro
    Fase1.setGerenciadorGrafico(&GG);
    Fase1.executar();
}

void NightFall::Jogo::iniciarFase2()
{
   // Fase2.setJogador(&pJog1);
   //Fase2.setGerenciadorGrafico(&GG);
   // Fase2.executar();
}
