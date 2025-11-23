#include "Faca.h"
#include "Jogador.h"
#include "Vampiro.h"

int NightFall::Entidades::Faca::contaIndices = 0;

NightFall::Entidades::Faca::Faca() :
	ativo(false),
	danoFaca(30),
	pVampiro(nullptr),
	esquerda(false),
	indiceFacaVampiro(contaIndices++)
{
	id = 10;
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
		if(esquerda)
			corpo.move(-0.07f, 0.005f); // Isso está errado, tem que utilizar o mover que nem em Inimigo 
		else
			corpo.move(0.07f, 0.005f);

		// LEMBRAR QUE AO ATINGIR O JOGADOR OU CAIR NO CHÃO DEVE SER DELETADA, PONTEIRO DO VAMPIRO DEVE FICAR NULLPTR
		
	}
	else
	{
		if (pVampiro != nullptr)
		{
			if (pVampiro->getVida() > 0)
			{
				float meioVampiroX = pVampiro->getPosicao().x + pVampiro->getTamanho().x / 2;
				float meioVampiroY = pVampiro->getPosicao().y + pVampiro->getTamanho().y / 3;
				setPosicao(meioVampiroX, meioVampiroY);
			}
			else
				setPosicao(0.0f, 0.0f);
		}
	}
}

void NightFall::Entidades::Faca::projDanificar(NightFall::Entidades::Personagens::Jogador* pJogador)
{
	if (ativo)
	{
		pJogador->receberDano(danoFaca);
		ativo = false;
	}
}

void NightFall::Entidades::Faca::setVampiro(Personagens::Vampiro* vamps)
{
	if (vamps != nullptr)
	{
		pVampiro = vamps;
	}
}

const int NightFall::Entidades::Faca::getIndiceFaca() const
{
	return indiceFacaVampiro;
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

void NightFall::Entidades::Faca::salvar()
{
	bufferInterno.str("");
	buffer.clear();

	salvarDataBuffer();
}

void NightFall::Entidades::Faca::salvarDataBuffer()
{
	Entidade::salvarDataBuffer();
	buffer << ativo << " " << danoFaca << " " 
		<< esquerda << " " << indiceFacaVampiro 
		<< std::endl;
}

void NightFall::Entidades::Faca::carregarFaca(bool atividade, int dano, bool esq, int indiceDaFaca)
{
	ativo = atividade;
	danoFaca = dano;
	esquerda = esq;
	indiceFacaVampiro = indiceDaFaca;
}
