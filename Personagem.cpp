#include "Personagem.h"
#include "Gerenciador_Grafico.h"
#include <iostream>

const float NightFall::Entidades::Personagens::Personagem::FRICCAO = 1200.0f;

NightFall::Entidades::Personagens::Personagem::Personagem() : 
    Entidade(), 
    num_vidas(10), 
    velocidade(70.0f),
    noChao(false),
    velocidadeAtual(0.0f, 0.0f),
    aceleracao(0.0f, 0.0f),
    forcaPulo(500.0f)
{

}

NightFall::Entidades::Personagens::Personagem::~Personagem() {}

void NightFall::Entidades::Personagens::Personagem::receberDano(unsigned int dano)
{
    num_vidas -= dano;
    std::cout << "Dano recebido, vida:" << num_vidas << std::endl;
}

void NightFall::Entidades::Personagens::Personagem::aplicarForca(sf::Vector2f forca)
{
    //codigo feito para aplicar uma forca na aceleracao
    //de forma parecida com a formula da fisica
    // F = m * a, mas como a massa do corpo é 1.
    //Apenas soma ja que pra cada 1 na força
    //tambem aumenta 1 na aceleracao
    aceleracao += forca;
}

void NightFall::Entidades::Personagens::Personagem::setVelocidadeX(float vx)
{
    velocidadeAtual.x = vx;
}

void NightFall::Entidades::Personagens::Personagem::setVelocidadeY(float vy)
{
    velocidadeAtual.y = vy;
}

void NightFall::Entidades::Personagens::Personagem::setNoChao(bool valor)
{
    noChao = valor;
}

void NightFall::Entidades::Personagens::Personagem::setVelocidade(sf::Vector2f vel)
{
    velocidadeAtual = vel;
}

const int NightFall::Entidades::Personagens::Personagem::getVida() const
{
    return num_vidas;
}

void NightFall::Entidades::Personagens::Personagem::setVida(int vd)
{
    num_vidas = vd;
}

const sf::Vector2f NightFall::Entidades::Personagens::Personagem::getVelocidade() const
{
    return velocidadeAtual;
}

const bool NightFall::Entidades::Personagens::Personagem::getNoChao() const
{
    return noChao;
}

void NightFall::Entidades::Personagens::Personagem::desenhar() {
    if (pGG != nullptr && num_vidas > 0)
        pGG->desenharEnte(this);
}

/*
void NightFall::Entidades::Personagens::Personagem::knockback(float direcao)
{
    const float FORCA_EMPURAO_X = 50.f;
    const float FORCA_PULO_Y = -10.f;

    sf::Vector2f novaVel (direcao * FORCA_EMPURAO_X, getVelocidade().y + FORCA_PULO_Y);
    setVelocidade(novaVel);
}
*/
