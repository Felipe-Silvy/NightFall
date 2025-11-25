#include "Jogador.h"
#include "Inimigo.h"
#include "Gerenciador_Grafico.h"
#include <iostream>
#include <iomanip>

NightFall::Entidades::Personagens::Jogador::Jogador() : 
    Personagem() , 
    pontos(0), 
    poderDano(20)
{
    id = 3; //ID DA CLASSE JOGADOR EH 3
    corpo.setScale(0.07f, 0.07f);
    velocidade = 200.0f;
    num_vidas = 200;
    forcaPulo = 650.0f;
}

NightFall::Entidades::Personagens::Jogador::~Jogador() { pontos = 0; }

void NightFall::Entidades::Personagens::Jogador::colidir(Entidades::Personagens::Inimigo* pIn)
{
   pIn->danificar(this);
}

void NightFall::Entidades::Personagens::Jogador::executar ()
{
    mover();
    retornarCorNormal();
}

void NightFall::Entidades::Personagens::Jogador::mover()
{
    deltaTempo = relogioMovimento.restart().asSeconds();
    
    if (getPosicao().y + getTamanho().y >= pGG->getAlturaChao()
        && velocidadeAtual.y >= 0.f && !noChao)
    {
        noChao = true;
        sf::Vector2f pos = getPosicao();
        pos.y = pGG->getAlturaChao() - getTamanho().y;
        setPosicao(pos);
    }
    
    gravitar();

    //segundo a fisica, velocidade é aceleracao * tempo

    velocidadeAtual += aceleracao * deltaTempo;

    if (velocidadeAtual.x > velocidade)
        velocidadeAtual.x = velocidade;
    if (velocidadeAtual.x < -velocidade)
        velocidadeAtual.x = -velocidade;

    sf::Vector2f movimento = velocidadeAtual * deltaTempo;

    moverCorpo(movimento);

    if ( fabs(aceleracao.x) < 0.001f && noChao) 
    {
        if (velocidadeAtual.x > 0.0f || velocidadeAtual.x < 0.0f)
        {
            int sinal_da_friccao;
            
            if (velocidadeAtual.x > 0.0f)
                sinal_da_friccao = 1;
            else
                sinal_da_friccao = -1;

            velocidadeAtual.x -= sinal_da_friccao * FRICCAO * deltaTempo;

            if ((sinal_da_friccao > 0 && velocidadeAtual.x < 0) || (sinal_da_friccao < 0 && velocidadeAtual.x > 0))
                velocidadeAtual.x = 0;
        }
    }

    aceleracao = sf::Vector2f(0.f, 0.f);
}

void NightFall::Entidades::Personagens::Jogador::pular()
{
    if (noChao)
    {
        velocidadeAtual.y = -forcaPulo;
        noChao = false;
    }
}

void NightFall::Entidades::Personagens::Jogador::atacar(std::vector<Inimigo*>* lista)
{
    float alcanceAtaque = 100.f; 

    for (int i = 0; i < (int)lista->size(); i++)
    {
        Entidades::Personagens::Inimigo* inimigo = lista->at(i);
        if (inimigo == nullptr)
            continue;

        sf::Vector2f posInimigo = inimigo->getCorpo().getPosition();

        float distX = std::abs(posInimigo.x - getPosicao().x);
        float distY = std::abs(posInimigo.y - getPosicao().y);
        float distancia = std::sqrt(distX * distX + distY * distY);

        if (distancia <= alcanceAtaque)
        {
            std::cout << "Acertou ataque!!" << std::endl;

            inimigo->receberDano(poderDano);
            if (inimigo->getVida() <= 0)
            {
                operator++();
            }
        }
    }
}

int NightFall::Entidades::Personagens::Jogador::getDano()
{
    return poderDano;
}

const int NightFall::Entidades::Personagens::Jogador::getPontos() const
{
    return pontos;
}

void NightFall::Entidades::Personagens::Jogador::setPontos(int pts)
{
    pontos = pts;
}


void NightFall::Entidades::Personagens::Jogador::operator++()
{
    pontos = pontos + 1;
}

void NightFall::Entidades::Personagens::Jogador::salvar()
{
    bufferInterno.str("");
    buffer.clear();

    salvarDataBuffer();
}

void NightFall::Entidades::Personagens::Jogador::carregarJogador(int pont, int poder)
{
    pontos = pont;
    poderDano = poder;
}

void NightFall::Entidades::Personagens::Jogador::salvarDataBuffer()
{
    Personagem::salvarDataBuffer();
    buffer << pontos << " " << poderDano << std::endl;
}