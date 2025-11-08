#include "Jogador.h"
#include "Inimigo.h"

NightFall::Entidades::Personagens::Jogador::Jogador() : Personagem() , pontos(0)
{
    corpo.setScale(0.10f, 0.10f);
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
    
    deltaTempo = relogioMovimento.getElapsedTime().asSeconds();
    
    if (getPosicao().y >= 300.0f)
    {
        noChao = true;
        sf::Vector2f posicaoNoChao = getPosicao();
        posicaoNoChao.y = 300.0f;
        setPosicao(posicaoNoChao);
    }

    if (!noChao)
        aceleracao.y += 1000.0f;

    //segundo a fisica, velocidade é aceleracao * tempo

    velocidadeAtual += aceleracao * deltaTempo;

    if (velocidadeAtual.x > velocidade)
        velocidadeAtual.x = velocidade;
    if (velocidadeAtual.x < -velocidade)
        velocidadeAtual.x = -velocidade;

    sf::Vector2f movimento = velocidadeAtual * deltaTempo;

    (this)->moverCorpo(movimento);

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
    relogioMovimento.restart();
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

void NightFall::Entidades::Personagens::Personagem::setVelocidade(float vel)
{
    velocidade = vel;
}

