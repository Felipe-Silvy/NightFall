#include "Cristal.h"
#include "Jogador.h"
#include "Gerenciador_Grafico.h"

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
	corpo.setScale(0.25f, 0.25f);

	if (Cristal::posicoesXCristal.empty())
	{
		setPosicao(sf::Vector2f(100.f, 400.f));
		return;
	} 

	int qualPosicao = rand() % (int)(Cristal::posicoesXCristal.size());

	sf::Vector2f posicao;

	posicao.x = Cristal::posicoesXCristal[qualPosicao];
	posicao.y = 0.0f;

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

void NightFall::Entidades::Obstaculos::Cristal::executar()
{
	//Devemos implementar um executar no cristal
	//Talvez semelhante a teia ou a plataforma?

	deltaTempo = relogioMovimento.restart().asSeconds();
	relogioMovimento.restart();
	cooldownInteracao += deltaTempo;

	if (cooldownInteracao >= 5.0f) {
		if (rand() % 2) {
			setPosicao(getPosicao().x + 10.0f, pGG->getAlturaChao() - getTamanho().y);
		}
		else {
			setPosicao(getPosicao().x - 10.0f, pGG->getAlturaChao() - getTamanho().y);
		}
		cooldownInteracao = 0;
	}

	if (getPosicao().y + getTamanho().y < pGG->getAlturaChao())
	{
		setPosicao(getPosicao().x, 0.01f);
	}
	else
	{
		setPosicao(getPosicao().x, pGG->getAlturaChao() - getTamanho().y);
	}
}

void NightFall::Entidades::Obstaculos::Cristal::obstaculizar(Personagens::Jogador* p)
{
	if (p != nullptr && podeDanificar())
	{
		std::cout << "Machucado pelo cristal" << std::endl;
		p->receberDano(danosidade);
	}
}

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

void NightFall::Entidades::Obstaculos::Cristal::salvar()
{
	bufferInterno.str("");
	buffer.clear();

	salvarDataBuffer();
}

void NightFall::Entidades::Obstaculos::Cristal::salvarDataBuffer()
{
	//cristal nao precisa passar danosidade para o buffer
	//porque todos os cristais tem a mesmas danosidade
	//possivelmente alterar danosidade para um valor rand?
	Obstaculo::salvarDataBuffer();
	//buffer << danosidade << std::endl;
}