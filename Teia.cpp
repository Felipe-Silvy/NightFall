#include "Teia.h"
#include "Jogador.h"
#include "Gerenciadores/Gerenciador_Grafico.h"

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
	id = 6;
}

NightFall::Entidades::Obstaculos::Teia::Teia(const bool danosidade, const float desacel, const float larg) : Obstaculo()
{
	danoso = danosidade;
	desaceleracao = desacel;
	largura = larg;

	id = 6;

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
	cooldownInteracao += deltaTempo;

	if (cooldownInteracao >= 5.0f) {
		if (rand() % 2) {
			corpo.setScale(largura * 0.15f, largura * 0.15f);
			setPosicao(getPosicao().x, pGG->getAlturaChao() - getTamanho().y);
			estado = 1;
		}
		else {
			corpo.setScale(largura * 0.1f, largura * 0.1f);
			setPosicao(getPosicao().x, pGG->getAlturaChao() - getTamanho().y);
			estado = 0;
		}
		cooldownInteracao = 0;
	}

	gravitar();
}

void NightFall::Entidades::Obstaculos::Teia::obstaculizar(Personagens::Jogador* p)
{
	float desacelerar_pratico = desaceleracao;
	if (!estado)
		desacelerar_pratico *= 0.8f;
	
	p->setVelocidade(sf::Vector2f(p->getVelocidade().x * desacelerar_pratico, p->getVelocidade().y));
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
	bufferInterno.str("");
	buffer.clear();

	salvarDataBuffer();
}

void NightFall::Entidades::Obstaculos::Teia::carregarTeia(float larg, float desacel)
{
	largura = larg;
	desaceleracao = desacel;
}

void NightFall::Entidades::Obstaculos::Teia::salvarDataBuffer()
{
	Obstaculo::salvarDataBuffer();
	buffer << largura << " " << desaceleracao << std::endl;
}
