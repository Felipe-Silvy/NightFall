#include "Personagem.h"

NightFall::Entidades::Personagens::Personagem::Personagem() : Entidade(), num_vidas(0), velocidade(0.0) {}

NightFall::Entidades::Personagens::Personagem::~Personagem() {}

void NightFall::Entidades::Personagens::Personagem::receberDano(unsigned int dano)
{
    num_vidas -= dano;
}