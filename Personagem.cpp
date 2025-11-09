#include "Personagem.h"

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
}


void NightFall::Entidades::Personagens::Personagem::aplicarForca(sf::Vector2f forca)
{
    //aceleracao depende de forca
    aceleracao += forca;
}
