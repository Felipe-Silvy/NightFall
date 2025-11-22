#include "Jogo.h"
#include "Entidade.h"

NightFall::Jogo::Jogo() : pJog1(), pJog2(), GG(), MenuJogo(), Fase1(), Fase2(), doisJogadores(false)
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
    pJog1.setTextura("Jogador1");
    pJog2.setTextura("Jogador2");
    MenuJogo.executar();
}

void NightFall::Jogo::iniciarFase1()
{
    std::cout << "FASE 1 INICIADA" << std::endl;
    Fase1.setJogador(&pJog1); 
    if (doisJogadores) {
        Fase1.setJogador(&pJog2);
        std::cout << "2 Jogadores" << std::endl;
    }

    Fase1.executar();
}

void NightFall::Jogo::iniciarFase2()
{
    std::cout << "FASE 2 INICIADA" << std::endl;
    Fase2.setJogador(&pJog1);
    if (doisJogadores) {
        Fase2.setJogador(&pJog2);
        std::cout << "2 Jogadores" << std::endl;
    }

    Fase2.executar();
}

void NightFall::Jogo::setDoisJogadores(bool boleano)
{
    doisJogadores = boleano;
}

const bool NightFall::Jogo::getDoisJogadores() const
{
    return doisJogadores;
}

void NightFall::Jogo::jogoPausar()
{
    MenuJogo.executarTelaPause();
}

void NightFall::Jogo::salvarJogo()
{
    if (Fase1.getAtiva())
    {
        Fase1.salvarFase();
    }
    else if (Fase2.getAtiva())
    {
        Fase2.salvarFase();
    }
    else
    {
        std::cout << "Nao ha fase ativa, erro inesperado" << std::endl;
    }
}
