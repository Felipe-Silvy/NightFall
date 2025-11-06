#include "Jogador.h"

NightFall::Entidades::Personagens::Jogador::Jogador() : Personagem() , pontos(0)
{
}

NightFall::Entidades::Personagens::Jogador::~Jogador() { pontos = 0; }

void NightFall::Entidades::Personagens::Jogador::executar () {}

void NightFall::Entidades::Personagens::Jogador::salvar() {}

void NightFall::Entidades::Personagens::Jogador::mover()
{
}

void NightFall::Entidades::Personagens::Personagem::setVelocidade(float vel)
{
    velocidade = vel;
}

