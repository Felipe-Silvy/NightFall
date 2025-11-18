#include "Entidade.h"

NightFall::Entidades::Entidade::Entidade() :
	Ente(), deltaTempo(0.0f),
	cooldownDano(0.0f)
{
	relogioMovimento.restart();
}

NightFall::Entidades::Entidade::~Entidade() {}

void NightFall::Entidades::Entidade::salvarDataBuffer()
{ 
	// Implementar depois
};

const bool NightFall::Entidades::Entidade::podeDanificar()
{
	cooldownDano += deltaTempo;

	if (cooldownDano >= 0.5f)
	{
		cooldownDano = 0.f;
		return true;
	}
	return false;
}


