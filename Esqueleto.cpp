#include "Esqueleto.h"
#include "Jogador.h"

sf::Vector2f NightFall::Entidades::Personagens::Esqueleto::ultimaPosicao = { 0, 0 };

NightFall::Entidades::Personagens::Esqueleto::Esqueleto() : Inimigo(), tamanho(0)
{
    nivel_maldade = 2;
    num_vidas = 10;
    corpo.setScale(0.1f, 0.1f);
    ultimaPosicao.x += 200.0f + ((rand() % 10) - 5) * 10;
    setPosicao(ultimaPosicao);
    velocidade = 50.0f;
}

NightFall::Entidades::Personagens::Esqueleto::~Esqueleto()
{
}

void NightFall::Entidades::Personagens::Esqueleto::danificar(Jogador* p)
{
    if (p != nullptr)
        p->receberDano(nivel_maldade);
}

void NightFall::Entidades::Personagens::Esqueleto::salvar()
{
}

void NightFall::Entidades::Personagens::Esqueleto::executar()
{
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
}