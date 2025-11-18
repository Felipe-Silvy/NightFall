#include "Jogador.h"
#include "Gerenciador_Grafico.h"
#include <iostream>
#include "Vampiro.h"

NightFall::Entidades::Personagens::Vampiro::Vampiro()
{
    forca = 2;
    nivel_maldade = 50;
    num_vidas = 80;
    corpo.setScale(0.1f, 0.1f);
    ultimaPosicao.x += 200.0f + ((rand() % 10) - 5) * 10;
    setPosicao(ultimaPosicao);
    velocidade = 50.0f;
}

NightFall::Entidades::Personagens::Vampiro::~Vampiro()
{
}

sf::Vector2f NightFall::Entidades::Personagens::Vampiro::ultimaPosicao = { 0, 0 };


void NightFall::Entidades::Personagens::Vampiro::danificar(Jogador* p)
{
    if (p != nullptr && podeDanificar())
    {
        p->receberDano(forca*nivel_maldade);
        std::cout << "Esqueleto danificou" << std::endl;
    }
}

void NightFall::Entidades::Personagens::Vampiro::salvar()
{
}

void NightFall::Entidades::Personagens::Vampiro::executar()
{
    //Estrutura de codigo inspirada e parecida com codigo do ex-monitor Giovane Limas Salvi

    sf::Vector2f posJogador1 = pJogador1->getCorpo().getPosition();
    sf::Vector2f posJogador2;

    if (pJogador2)
        posJogador2 = pJogador2->getCorpo().getPosition();
    sf::Vector2f posInimigo = corpo.getPosition();

    if (fabs(posJogador1.x - posInimigo.x) <= alcancePerseguir &&
        fabs(posJogador1.y - posInimigo.y) <= alcancePerseguir)
    {
        perseguir(posJogador1, posInimigo);
    }
    else if (fabs(posJogador2.x - posInimigo.x) <= alcancePerseguir &&
        fabs(posJogador2.y - posInimigo.y) <= alcancePerseguir)
    {
        perseguir(posJogador2, posInimigo);
    }
    else
    {
        vagar();
    }

    mover();

    retornarCorNormal();
}

void NightFall::Entidades::Personagens::Vampiro::resetarUltimaPosicao()
{
    ultimaPosicao = sf::Vector2f(0.0f, 0.0f);
}