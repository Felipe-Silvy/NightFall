#include "Faca.h"
#include "Jogador.h"
#include "Vampiro.h"

NightFall::Entidades::Faca::Faca() :
	ativo(false),
	danoFaca(30),
	pVampiro(nullptr),
	esquerda(false)
{
	corpo.setScale(0.05f, 0.05f);
}

NightFall::Entidades::Faca::~Faca()
{
}

void NightFall::Entidades::Faca::executar()
{
	//o executar da faca só é chamado quando ela está ativa, mas ainda é 
	//feita essa verificacao para garantir o funcionamento correto
	if (ativo)
	{
		/*if(esquerda)
			corpo.move(-20.0f, 0.0f); // Isso está errado, tem que utilizar o mover que nem em Inimigo 
		else
			corpo.move(20.0f, 0.0f);*/

		// LEMBRAR QUE AO ATINGIR O JOGADOR OU CAIR NO CHÃO DEVE SER DELETADA, PONTEIRO DO VAMPIRO DEVE FICAR NULLPTR
		
	}
	else
	{
		setPosicao(pVampiro->getPosicao());
	}
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

void NightFall::Entidades::Faca::setVampiro(Personagens::Vampiro* vamps)
{
	if (vamps != nullptr)
	{
		pVampiro = vamps;
	}
}

const bool NightFall::Entidades::Faca::getAtivo() const
{
	return ativo;
}

void NightFall::Entidades::Faca::setAtivo(const bool novaAtividade)
{
	ativo = novaAtividade;
}

void NightFall::Entidades::Faca::setDirecao(bool esq)
{
	esquerda = esq;
}
