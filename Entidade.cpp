#include "Entidade.h"

NightFall::Entidades::Entidade::Entidade() :
	Ente(), x(0) , y(0) 
{
}

void NightFall::Entidades::Entidade::setPosicao(sf::Vector2f pos)
{
	corpo.setPosition(pos);
}

NightFall::Entidades::Entidade::~Entidade() {}

void NightFall::Entidades::Entidade::salvarDataBuffer()
{ 
	// Implementar depois
};


