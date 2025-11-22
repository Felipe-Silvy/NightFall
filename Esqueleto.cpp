#include "Esqueleto.h"
#include "Jogador.h"
#include "Gerenciador_Grafico.h"
#include <iostream>

sf::Vector2f NightFall::Entidades::Personagens::Esqueleto::ultimaPosicao = { 0, 0 };

NightFall::Entidades::Personagens::Esqueleto::Esqueleto() :
    Inimigo(), 
    tamanho(10),
    rigidez_ossea(rand()%6)
{
    id = 7;
    nivel_maldade = 40;
    num_vidas = 50;
    corpo.setScale(tamanho / 100.0f, tamanho / 100.0f);
    ultimaPosicao.x += 200.0f + ((rand() % 10) - 5) * 10;
    setPosicao(ultimaPosicao);
    velocidade = 50.0f;
}

NightFall::Entidades::Personagens::Esqueleto::~Esqueleto()
{
}

void NightFall::Entidades::Personagens::Esqueleto::danificar(Jogador* p)
{
    if (p != nullptr && podeDanificar())
    {
        p->receberDano(nivel_maldade);
        std::cout << "Esqueleto danificou" << std::endl;
    }
}

void NightFall::Entidades::Personagens::Esqueleto::executar()
{
    //Estrutura de codigo inspirada e parecida com codigo do ex-monitor Giovane Limas Salvi
    
    sf::Vector2f posJogador1 = pJogador1->getCorpo().getPosition();
    sf::Vector2f posJogador2;

    if (pJogador2)
        posJogador2 = pJogador2->getCorpo().getPosition();
    sf::Vector2f posInimigo = corpo.getPosition();

    if (fabs(posJogador1.x - posInimigo.x) <= alcancePerseguir &&
        fabs(posJogador1.y - posInimigo.y) <= alcancePerseguir)
    {
        perseguir(posJogador1, posInimigo);
    }
    else if (fabs(posJogador2.x - posInimigo.x) <= alcancePerseguir &&
            fabs(posJogador2.y - posInimigo.y) <= alcancePerseguir)
    {
        perseguir(posJogador2, posInimigo);
    }
    else
    {
        vagar();
    }

    mover(); 
    
    retornarCorNormal();
}

void NightFall::Entidades::Personagens::Esqueleto::resetarUltimaPosicao()
{
    ultimaPosicao = sf::Vector2f(0.0f, 0.0f);
}

void NightFall::Entidades::Personagens::Esqueleto::receberDano(unsigned int dano)
{
    dano -= rigidez_ossea;

    //a rigidez ossea do esqueleto faz ele receber menos dano

    num_vidas -= dano;
    std::cout << "Dano reduzido em " << rigidez_ossea << " recebido, vida:" << num_vidas << std::endl;
    tempoMudancaCor = 0.2f;           // piscar vermelho por 0.2s
    corpo.setColor(sf::Color(255, 0, 0));
}

void NightFall::Entidades::Personagens::Esqueleto::salvar()
{
    bufferInterno.str("");
    buffer.clear();

    salvarDataBuffer();
}

void NightFall::Entidades::Personagens::Esqueleto::carregarEsqueleto
    (int tam, int rigid)
{
    tamanho = tam;
    rigidez_ossea = rigid;
}

void NightFall::Entidades::Personagens::Esqueleto::salvarDataBuffer()
{
    Inimigo::salvarDataBuffer();
    buffer << tamanho << " " << rigidez_ossea << std::endl;
}