#include "Bandeira.h"
#include "Gerenciador_Grafico.h"

NightFall::Entidades::Obstaculos::Bandeira::Bandeira() :
    chegouFinal(false)
{
	corpo.setScale(0.1f, 0.1f);

	// Obter tamanho da textura para posicionar corretamente
	//sf::Vector2u tamanhoTextura = pGG->getTextura("Bandeira").getSize();
	//sf::Vector2f tamanhoEscalado(
		//tamanhoTextura.x * corpo.getScale().x,
		//tamanhoTextura.y * corpo.getScale().y
	//);

	// Define posição no canto inferior direito da tela (VideoMode 1280x720)
	sf::Vector2f posFinal;
	posFinal.x = 1280.0f - -100.0f;
	posFinal.y = pGG->getChao() - 100.0f;

	corpo.setPosition(posFinal);
}

NightFall::Entidades::Obstaculos::Bandeira::~Bandeira()
{
}

const bool NightFall::Entidades::Obstaculos::Bandeira::getChegouFinal() const
{
    return chegouFinal;
}

void NightFall::Entidades::Obstaculos::Bandeira::executar()
{
}

void NightFall::Entidades::Obstaculos::Bandeira::obstaculizar(Personagens::Jogador* p)
{
    chegouFinal = true;
}

void NightFall::Entidades::Obstaculos::Bandeira::salvar()
{

}