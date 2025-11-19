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

void NightFall::Entidades::Obstaculos::Cristal::salvarDataBuffer()
{

}

void NightFall::Entidades::Obstaculos::Cristal::executar()
{
	//Devemos implementar um executar no cristal
	//Talvez semelhante a teia ou a plataforma?

	deltaTempo = relogioMovimento.restart().asSeconds();
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

}