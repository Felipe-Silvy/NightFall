#include "Projetil.h"
#include "Jogador.h"

NightFall::Entidades::Projetil::Projetil() :
	ativo(true),
	danoProjetil(10)
{

}

NightFall::Entidades::Projetil::~Projetil()
{

}

void NightFall::Entidades::Projetil::executar()
{

}

void NightFall::Entidades::Projetil::salvar()
{

}

void NightFall::Entidades::Projetil::projDanificar(NightFall::Entidades::Personagens::Jogador* pJogador)
{
	if (ativo)
	{
		pJogador->receberDano(danoProjetil);
	}
}
