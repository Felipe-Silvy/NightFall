#include "Jogador.h"

NightFall::Entidades::Personagens::Jogador::Jogador() : Personagem() , pontos(0)
{
    texturaEsquerda.loadFromFile("Assets/Imagens/esqueleto_e.png");
    texturaDireita.loadFromFile("Assets/Imagens/esqueleto_d.png");
    body.setTexture(&texturaDireita);
}

NightFall::Entidades::Personagens::Jogador::~Jogador() { pontos = 0; }

void NightFall::Entidades::Personagens::Jogador::executar () {}

void NightFall::Entidades::Personagens::Jogador::salvar() {}

void NightFall::Entidades::Personagens::Jogador::mover(int direc)
{
    if (direc == 1)
    {
        body.setTexture(&texturaEsquerda);
        body.move(sf::Vector2f(-velocidade, 0));
    }
    else if (direc == 2)
    {
        body.setTexture(&texturaDireita);
        body.move(sf::Vector2f(velocidade, 0));
    }
    else if (direc == 3)
    {
        body.move(sf::Vector2f(0, -velocidade));
    }
    else
    {
        body.move(sf::Vector2f(0, velocidade));
    }
}

void NightFall::Entidades::Personagens::Personagem::setVelocidade(float vel)
{
    velocidade = vel;
}

void NightFall::Entidades::Personagens::Jogador::setTextura(sf::Texture* text)
{
	body.setTexture(text);
}