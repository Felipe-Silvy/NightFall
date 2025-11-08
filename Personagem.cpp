#include "Personagem.h"

const float NightFall::Entidades::Personagens::Personagem::FRICCAO = 200.0f;

NightFall::Entidades::Personagens::Personagem::Personagem() : Entidade(), num_vidas(0), velocidade(0.0) {}

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
