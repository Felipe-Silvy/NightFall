#include "Esqueleto.h"

sf::Vector2f NightFall::Entidades::Personagens::Esqueleto::ultimaPosicao = { 0, 0 };

NightFall::Entidades::Personagens::Esqueleto::Esqueleto() : Inimigo(), tamanho(0)
{
	nivel_maldade = 2;
	num_vidas = 10;
	corpo.setScale(0.15f, 0.15f);
	ultimaPosicao.x += 200.0f + ((rand() % 10) - 5) * 10;
	setPosicao(ultimaPosicao);
}

NightFall::Entidades::Personagens::Esqueleto::~Esqueleto()
{
}

void NightFall::Entidades::Personagens::Esqueleto::danificar(Jogador* p)
{
}

void NightFall::Entidades::Personagens::Esqueleto::salvar()
{
}

void NightFall::Entidades::Personagens::Esqueleto::executar()
{
}