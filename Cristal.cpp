#include "Cristal.h"
#include "Jogador.h"
#include "Gerenciador_Grafico.h"

std::vector<float> NightFall::Entidades::Obstaculos::Cristal::posicoesXCristal = {
	{150.0f},
	{250.0f},
	{450.0f},
	{650.0f},
	{850.0f},
	{1050.0f}
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
		{150.0f},
		{250.0f},
		{450.0f},
		{650.0f},
		{850.0f},
		{1050.0f}
	};
}

void NightFall::Entidades::Obstaculos::Cristal::salvar()
{

}