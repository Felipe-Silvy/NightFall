#include "Jogo.h"
#include "Entidade.h"

NightFall::Jogo::Jogo() : pJog1(), GG() // SOBRECARGA COM PARAMETROS TLVZ
{
    Ente::setGG(&GG);
    executar();
}

NightFall::Jogo::~Jogo() {}

void NightFall::Jogo::executar()
{
    pJog1.setTextura("Jogador");

    while (GG.verificaAbertura())
    {
        sf::Event event;
        while (GG.getWindow()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GG.fecharJanela();
        }

        GG.limpaJanela();
        GG.desenharEnte(&pJog1);
        GG.mostraElementos();
    }
    
}