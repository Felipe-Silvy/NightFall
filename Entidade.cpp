#include "Entidade.h"

NightFall::Entidades::Entidade::Entidade() :
	Ente(), x(0) , y(0), deltaTempo(0.0f)
{
	relogioMovimento.restart();
}

NightFall::Entidades::Entidade::~Entidade() {}

void NightFall::Entidades::Entidade::salvarDataBuffer()
{ 
	// Implementar depois
};


