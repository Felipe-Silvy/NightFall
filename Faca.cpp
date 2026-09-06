#include "Faca.h"
#include "Jogador.h"
#include "Vampiro.h"
#include "Gerenciadores/Gerenciador_Grafico.h"

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

// Atualiza movimento da faca: quando ativa, avança horizontalmente e sofre gravidade;
// quando inativa, segue a posição do vampiro que a carrega.
void NightFall::Entidades::Faca::executar()
{
	deltaTempo = relogioMovimento.getElapsedTime().asSeconds();
	relogioMovimento.restart();

	//o executar da faca só é chamado quando ela está ativa, mas ainda é 
	//feita essa verificacao para garantir o funcionamento correto
	if (ativo)
	{
		if(esquerda)
			corpo.move(-0.07f, 0.f);
		else
			corpo.move(0.07f, 0.f);

		gravitar();
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

void NightFall::Entidades::Faca::gravitar()
{
	float velocidade = 10.0f; // pixels/segundo

	if (getPosicao().y + getTamanho().y < pGG->getAlturaChao())
	{
		setPosicao(getPosicao().x, getPosicao().y + velocidade * deltaTempo);
	}
	else
	{
		setPosicao(getPosicao().x, pGG->getAlturaChao() - getTamanho().y);
	}

}