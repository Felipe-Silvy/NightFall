#include "Entidade.h"

NightFall::Entidades::Entidade::Entidade() :
	Ente(),
	deltaTempo(0.0f),
	cooldownDano(0.0f),
	buffer(&bufferInterno)
{
	relogioMovimento.restart();
}

NightFall::Entidades::Entidade::~Entidade() {}

void NightFall::Entidades::Entidade::salvarDataBuffer()
{
	//Informacoes pertinentes a ente
	buffer << id << " "
		<< corpo.getScale().x << " "
		<< corpo.getScale().y << " "
		<< corpo.getPosition().x << " "
		<< corpo.getPosition().y << " ";
}

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

void NightFall::Entidades::Entidade::relogioMovimentoResetar()
{
	relogioMovimento.restart();
	deltaTempo = 0.0f;
}

const std::string NightFall::Entidades::Entidade::getBufferString() const
{
	return bufferInterno.str(); ;
}


