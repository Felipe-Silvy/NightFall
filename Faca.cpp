#include "Faca.h"
#include "Jogador.h"

NightFall::Entidades::Faca::Faca() :
	ativo(false),
	danoProjetil(10)
{
}

NightFall::Entidades::Faca::~Faca()
{

}

void NightFall::Entidades::Faca::executar()
{

}

void NightFall::Entidades::Faca::salvar()
{

}

void NightFall::Entidades::Faca::projDanificar(NightFall::Entidades::Personagens::Jogador* pJogador)
{
	if (ativo)
	{
		pJogador->receberDano(danoFaca);
	}
}
