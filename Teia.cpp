#include "Teia.h"
#include "Jogador.h"
#include "Gerenciador_Grafico.h"

std::vector<float> NightFall::Entidades::Obstaculos::Teia::posicoesXTeia = {
	{100.0f},
	{500.0f},
	{900.0f},
	{300.0f},
	{700.0f},
	{1100.0f}
};

NightFall::Entidades::Obstaculos::Teia::Teia() : Obstaculo(), largura(-1), desaceleracao(-1)
{
}

NightFall::Entidades::Obstaculos::Teia::Teia(const bool danosidade, const float desacel, const float larg) : Obstaculo()
{
	danoso = danosidade;
	desaceleracao = desacel;
	largura = larg;

	corpo.setScale(largura * 0.1f, largura * 0.1f);

	if (Teia::posicoesXTeia.empty())
	{
		setPosicao(sf::Vector2f(100.f, 400.f));
		return;
	}

	int qualPosicao = rand() % (int)(Teia::posicoesXTeia.size());

	sf::Vector2f posicao;
	
	posicao.x = Teia::posicoesXTeia[qualPosicao];
	posicao.y = pGG->getAlturaChao() - 75;

	if (qualPosicao != static_cast<int>(Teia::posicoesXTeia.size()) - 1)
	{
		std::swap(Teia::posicoesXTeia[qualPosicao],
			Teia::posicoesXTeia.back());
	}
	Teia::posicoesXTeia.pop_back();

	setPosicao(posicao);
}

NightFall::Entidades::Obstaculos::Teia::~Teia()
{
}

void NightFall::Entidades::Obstaculos::Teia::executar()
{
	deltaTempo = relogioMovimento.getElapsedTime().asSeconds();
	relogioMovimento.restart();
	cooldownInteração += deltaTempo;

	if (cooldownInteração >= 5.0f) {
		if (rand() % 2) {
			corpo.setScale(largura * 0.2f, largura * 0.2f);
		}
		else {
			corpo.setScale(largura * 0.1f, largura * 0.1f);
		}
		cooldownInteração = 0;
	}
}

void NightFall::Entidades::Obstaculos::Teia::obstaculizar(Personagens::Jogador* p)
{
	p->setVelocidadeX((p->getVelocidade().x * desaceleracao));
}

void NightFall::Entidades::Obstaculos::Teia::resetPosicoes()
{
	NightFall::Entidades::Obstaculos::Teia::posicoesXTeia = {
		{100.0f},
		{500.0f},
		{900.0f},
		{300.0f},
		{700.0f},
		{1100.0f}
	};
}

void NightFall::Entidades::Obstaculos::Teia::salvar()
{

}
