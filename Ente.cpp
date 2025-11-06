#include "Ente.h"
#include "Gerenciador_Grafico.h"

NightFall::Gerenciadores::Gerenciador_Grafico* NightFall::Ente::pGG = nullptr;

NightFall::Ente::Ente() : id(0) , corpo()
{
    corpo.setPosition(0.f, 0.f);
    corpo.setScale(0.2f, 0.2f);
}

NightFall::Ente::~Ente() {}

void NightFall::Ente::desenhar() {
   // if (pFig != nullptr && pGG != nullptr)
      //  pGG->desenhar(pFig);
}

void NightFall::Ente::setGG(Gerenciadores::Gerenciador_Grafico* pG)
{
    if (pG != nullptr)
        pGG = pG;
}

const sf::Sprite& NightFall::Ente::getCorpo() const
{
    return corpo;
}

void NightFall::Ente::setTextura(const std::string& id)
{
    corpo.setTexture(pGG->getTextura(id));
}

const sf::Vector2f NightFall::Ente::getTamanho() const
{
    sf::Vector2u tamanhoTextura = corpo.getTexture()->getSize();
    sf::Vector2f escala = corpo.getScale();

    sf::Vector2f tamanhoReal(
        tamanhoTextura.x * escala.x,
        tamanhoTextura.y * escala.y
    );
    return tamanhoReal;
}

const sf::Vector2f NightFall::Ente::getPosicao() const
{
    return corpo.getPosition();
}
