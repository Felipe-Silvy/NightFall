#include "Jogador.h"
#include "Inimigo.h"
#include "Gerenciador_Grafico.h"
#include <iostream>
#include <iomanip>.

NightFall::Entidades::Personagens::Jogador::Jogador() : Personagem() , pontos(0), poderDano(20)
{
    corpo.setScale(0.07f, 0.07f);
    velocidade = 200.0f;
    num_vidas = 200;
    forcaPulo = 600.0f;
}

NightFall::Entidades::Personagens::Jogador::~Jogador() { pontos = 0; }

void NightFall::Entidades::Personagens::Jogador::colidir(Entidades::Personagens::Inimigo* pIn)
{
   pIn->danificar(this);
}

void NightFall::Entidades::Personagens::Jogador::executar ()
{
    mover();
}

void NightFall::Entidades::Personagens::Jogador::salvar() {}

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
    
    if (!noChao)
    {
        aceleracao.y += 1000.0f;
    }
    else
    {
        aceleracao.y = 0.0f;
        velocidadeAtual.y = 0.0f;
    }

    //segundo a fisica, velocidade é aceleracao * tempo

    velocidadeAtual += aceleracao * deltaTempo;

    if (velocidadeAtual.x > velocidade)
        velocidadeAtual.x = velocidade;
    if (velocidadeAtual.x < -velocidade)
        velocidadeAtual.x = -velocidade;

    sf::Vector2f movimento = velocidadeAtual * deltaTempo;

    moverCorpo(movimento);

    if ( fabs(aceleracao.x) < 0.001f && noChao) //nao esta se movendo para nenhum dos dois lados (eu acho)
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
            //isso é errado porque o sinal da friccao deve ser o mesmo da velocidade
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

void NightFall::Entidades::Personagens::Jogador::atacar()
{
}

int NightFall::Entidades::Personagens::Jogador::getDano()
{
    return poderDano;
}

void NightFall::Entidades::Personagens::Personagem::setVelocidade(float vel)
{
    velocidade = vel;
}



