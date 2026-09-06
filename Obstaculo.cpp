#include "Obstaculo.h"
#include "Gerenciadores/Gerenciador_Grafico.h"


// Construtor com parametros
NightFall::Entidades::Obstaculos::Obstaculo::Obstaculo() : 
	Entidade(), 
	danoso(false), 
	cooldownInteracao(0.0f),
	estado(0)
{
}

NightFall::Entidades::Obstaculos::Obstaculo::~Obstaculo()
{
}

// Implementação do método salvarDataBuffer
// Este é um método concreto, então pode ter uma implementação padrão ou vazia.
void NightFall::Entidades::Obstaculos::Obstaculo::salvarDataBuffer()
{
	Entidade::salvarDataBuffer();
	buffer << estado << " ";
}

void NightFall::Entidades::Obstaculos::Obstaculo::carregarObstaculo(int estado)
{
	this->estado = estado;
}

const int NightFall::Entidades::Obstaculos::Obstaculo::getEstado() const
{
	return estado;
}

void NightFall::Entidades::Obstaculos::Obstaculo::gravitar()
{
	float velocidade = 10.0f; 

	if (getPosicao().y + getTamanho().y < pGG->getAlturaChao())
	{
		setPosicao(getPosicao().x, getPosicao().y + velocidade * deltaTempo);
	}
	else
	{
		setPosicao(getPosicao().x, pGG->getAlturaChao() - getTamanho().y);
	}
}
