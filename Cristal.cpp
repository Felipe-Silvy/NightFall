#include "Cristal.h"
#include "Jogador.h"
#include "Gerenciadores/Gerenciador_Grafico.h"

std::vector<float> NightFall::Entidades::Obstaculos::Cristal::posicoesXCristal = {
	{100.0f},
	{300.0f},
	{500.0f},
	{700.0f},
	{900.0f},
	{1100.0f}
};

NightFall::Entidades::Obstaculos::Cristal::Cristal() :
	danosidade(20),
	Obstaculo()
{
	id = 8;
	danoso = true;
	corpo.setScale(0.23f, 0.23f);

	if (Cristal::posicoesXCristal.empty())
	{
		setPosicao(sf::Vector2f(100.f, 400.f));
		return;
	} 

	int qualPosicao = rand() % (int)(Cristal::posicoesXCristal.size());

	sf::Vector2f posicao;

	posicao.x = Cristal::posicoesXCristal[qualPosicao];
	posicao.y = pGG->getAlturaChao() - getTamanho().y;

	if (qualPosicao != static_cast<int>(Cristal::posicoesXCristal.size()) - 1)
	{
		std::swap(Cristal::posicoesXCristal[qualPosicao],
			Cristal::posicoesXCristal.back());
	}
	Cristal::posicoesXCristal.pop_back();

	setPosicao(posicao);
}

NightFall::Entidades::Obstaculos::Cristal::~Cristal()
{

}

// Atualiza o tempo, faz o cristal se mover aleatoriamente a cada 5 segundos e aplica gravidade.
void NightFall::Entidades::Obstaculos::Cristal::executar()
{
	deltaTempo = relogioMovimento.restart().asSeconds();
	relogioMovimento.restart();
	cooldownInteracao += deltaTempo;

	if (cooldownInteracao >= 5.0f) {
		if (rand() % 2)
		{
			setPosicao(getPosicao().x + 10.0f, getPosicao().y);
			estado = 0;
		}
		else
		{
			setPosicao(getPosicao().x - 10.0f, getPosicao().y);
			estado = 1;
		}
		cooldownInteracao = 0;
	}

	gravitar();
}

// Causa dano ao jogador quando há colisão e o cristal está apto a danificar.
void NightFall::Entidades::Obstaculos::Cristal::obstaculizar(Personagens::Jogador* p)
{
	if (p != nullptr && podeDanificar())
	{
		std::cout << "Machucado pelo cristal" << std::endl;
		if (estado)
			p->receberDano((unsigned int)(danosidade * 1.5f));
		else
			p->receberDano(danosidade);
	}
}

// Restaura a lista de posições iniciais possíveis para os cristais.
void NightFall::Entidades::Obstaculos::Cristal::resetPosicoes()
{
	NightFall::Entidades::Obstaculos::Cristal::posicoesXCristal = {
		{100.0f},
		{300.0f},
		{500.0f},
		{700.0f},
		{900.0f},
		{1100.0f}
	};
}

// Limpa os buffers internos e salva os dados do cristal.
void NightFall::Entidades::Obstaculos::Cristal::salvar()
{
	bufferInterno.str("");
	buffer.clear();

	salvarDataBuffer();
}

void NightFall::Entidades::Obstaculos::Cristal::carregarCristal(short int danosi)
{
	danosidade = danosi;
}

void NightFall::Entidades::Obstaculos::Cristal::salvarDataBuffer()
{
	//cristal nao precisa passar danosidade para o buffer
	//porque todos os cristais tem a mesmas danosidade
	Obstaculo::salvarDataBuffer();
	buffer << danosidade << std::endl;
}