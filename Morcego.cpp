#include "Morcego.h"
#include "Jogador.h"

sf::Vector2f NightFall::Entidades::Personagens::Morcego::ultimaPosicao = { 0, 0 };

NightFall::Entidades::Personagens::Morcego::Morcego() : Inimigo(), raio(0)
{
	nivel_maldade = 1;
	num_vidas = 1;
	corpo.setScale(0.05f, 0.05f);
	ultimaPosicao.x += 100.0f + ((rand() % 10) - 2) * 10; // mudar números
	ultimaPosicao.y += 30.0f + ((rand() % 10) - 2) * 10; // mudar números
	setPosicao(ultimaPosicao);
}

NightFall::Entidades::Personagens::Morcego::~Morcego()
{
}

void NightFall::Entidades::Personagens::Morcego::danificar(Jogador* p)
{
	if (p != nullptr)
		p->receberDano(nivel_maldade);
}

void NightFall::Entidades::Personagens::Morcego::salvar()
{
}

void NightFall::Entidades::Personagens::Morcego::executar()
{
}