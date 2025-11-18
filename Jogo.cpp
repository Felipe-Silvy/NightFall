#include "Jogo.h"
#include "Entidade.h"

NightFall::Jogo::Jogo() : pJog1(), GG(), MenuJogo(), Fase1() // SOBRECARGA COM PARAMETROS TLVZ
{
    Ente::setGG(&GG);
    MenuJogo.setJogo(this);
    Fase1.setJogo(this);
    Fase2.setJogo(this);
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
    Fase1.executar();
}

void NightFall::Jogo::iniciarFase2()
{
    std::cout << "FASE 2 INICIADA" << std::endl;
    Fase2.setJogador(&pJog1);
   //Fase2.setGerenciadorGrafico(&GG);
    Fase2.executar();
}
