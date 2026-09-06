#include "Ente.h"
#include "Gerenciadores/Gerenciador_Grafico.h"

NightFall::Gerenciadores::Gerenciador_Grafico* NightFall::Ente::pGG = nullptr;

NightFall::Ente::Ente() : id(-1) , corpo()
{
   corpo.setPosition(0.f, 0.f);
   corpo.setScale(0.2f, 0.2f);
}

NightFall::Ente::~Ente() {}

// Solicita ao Gerenciador Gráfico que desenhe este ente na tela.
void NightFall::Ente::desenhar() {
   if (pGG != nullptr)
      pGG->desenharEnte(this);
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
    sf::Vector2f tamanhoBase(0.f, 0.f);

    const sf::Texture* pTextura = corpo.getTexture();
    if (pTextura != nullptr)
    {
        sf::Vector2u tamanhoTextura = pTextura->getSize();
        tamanhoBase.x = static_cast<float>(tamanhoTextura.x);
        tamanhoBase.y = static_cast<float>(tamanhoTextura.y);
    }
    sf::Vector2f escala = corpo.getScale();
    sf::Vector2f tamanhoReal(
        tamanhoBase.x * escala.x,
        tamanhoBase.y * escala.y
    );

    return tamanhoReal;
}

const sf::Vector2f NightFall::Ente::getPosicao() const
{
    return corpo.getPosition();
}

void NightFall::Ente::setTamanho(float x, float y)
{
    corpo.setScale(x, y);
}

void NightFall::Ente::setTamanho(sf::Vector2f tam)
{
    corpo.setScale(tam);
}

void NightFall::Ente::setPosicao(float x, float y)
{
    corpo.setPosition(x, y);
}

void NightFall::Ente::setPosicao(sf::Vector2f pos)
{
    corpo.setPosition(pos);
}

// Move o sprite pelo deslocamento fornecido.
void NightFall::Ente::moverCorpo(sf::Vector2f deslocamento)
{
    corpo.move(deslocamento);
}


