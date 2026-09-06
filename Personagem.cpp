#include "Personagem.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include <iostream>

const float NightFall::Entidades::Personagens::Personagem::FRICCAO = 1200.0f;

NightFall::Entidades::Personagens::Personagem::Personagem() : 
    Entidade(), 
    num_vidas(10), 
    velocidade(70.0f),
    noChao(false),
    velocidadeAtual(0.0f, 0.0f),
    aceleracao(0.0f, 0.0f),
    forcaPulo(500.0f),
    tempoMudancaCor(0.f)
{
}

NightFall::Entidades::Personagens::Personagem::~Personagem() {}

void NightFall::Entidades::Personagens::Personagem::receberDano(unsigned int dano)
{
    num_vidas -= dano;
    std::cout << "Dano recebido, vida:" << num_vidas << std::endl;
    tempoMudancaCor = 0.2f;           // piscar vermelho por 0.2s
    corpo.setColor(sf::Color(255, 0, 0));
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

void NightFall::Entidades::Personagens::Personagem::gravitar()
{
    if (!noChao)
    {
        aceleracao.y += 1000.0f;
    }
    else
    {
        aceleracao.y = 0.0f;
        velocidadeAtual.y = 0.0f;
    }
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

void NightFall::Entidades::Personagens::Personagem::desenhar()
{
    if (pGG != nullptr && num_vidas > 0)
        pGG->desenharEnte(this);
}
void NightFall::Entidades::Personagens::Personagem::retornarCorNormal()
{
    if (tempoMudancaCor > 0.f) {
        tempoMudancaCor -= deltaTempo;
        if (tempoMudancaCor <= 0.f) {
            corpo.setColor(sf::Color(255, 255, 255)); // volta ao normal
        }
    }
}

void NightFall::Entidades::Personagens::Personagem::salvarDataBuffer()
{
    Entidade::salvarDataBuffer();
    buffer << num_vidas << " "
        << velocidade << " "
        << velocidadeAtual.x << " "
        << velocidadeAtual.y << " "
        << forcaPulo << " "
        << noChao << " "
        << tempoMudancaCor << " ";
}

void NightFall::Entidades::Personagens::Personagem::carregarPersonagem
    (int vidasSalvas, int velMax, sf::Vector2f velAtual, int pulo, bool chao, float cortempo)
{
    num_vidas = vidasSalvas;
    velocidade = velMax;
    velocidadeAtual = velAtual;
    forcaPulo = pulo;
    noChao = chao;
    tempoMudancaCor = cortempo;
}
