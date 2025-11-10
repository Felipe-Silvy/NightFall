#include "Personagem.h"
#include <iostream>

const float NightFall::Entidades::Personagens::Personagem::FRICCAO = 1200.0f;

NightFall::Entidades::Personagens::Personagem::Personagem() : 
    Entidade(), 
    num_vidas(10), 
    velocidade(70.0f),
    noChao(false),
    velocidadeAtual(0.0f, 0.0f),
    aceleracao(0.0f, 0.0f),
    forcaPulo(500.0f),
    deltaTempo(0.0f)
{
    relogioMovimento.restart();
}

NightFall::Entidades::Personagens::Personagem::~Personagem() {}

void NightFall::Entidades::Personagens::Personagem::receberDano(unsigned int dano)
{
    num_vidas -= dano;
    std::cout << num_vidas << std::endl;
}

void NightFall::Entidades::Personagens::Personagem::aplicarForca(sf::Vector2f forca)
{
    //aceleracao depende de forca
    aceleracao += forca;
}

void NightFall::Entidades::Personagens::Personagem::setVelocidadeX(float vx)
{
    velocidadeAtual.x = vx;
}

void NightFall::Entidades::Personagens::Personagem::setVelocidadeY(float vy)
{
    velocidadeAtual.y = vy;
}

void NightFall::Entidades::Personagens::Personagem::setNoChao(bool valor)
{
    noChao = valor;
}

const int NightFall::Entidades::Personagens::Personagem::getVida() const
{
    return num_vidas;
}

const sf::Vector2f NightFall::Entidades::Personagens::Personagem::getVelocidade() const
{
    return velocidadeAtual;
}

const bool NightFall::Entidades::Personagens::Personagem::getNoChao() const
{
    return noChao;
}
