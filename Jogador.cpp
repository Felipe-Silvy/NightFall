#include "Jogador.h"
#include "Inimigo.h"

NightFall::Entidades::Personagens::Jogador::Jogador() : Personagem() , pontos(0)
{
}

NightFall::Entidades::Personagens::Jogador::~Jogador() { pontos = 0; }

void NightFall::Entidades::Personagens::Jogador::colidir(Entidades::Personagens::Inimigo* pIn)
{
    pIn->danificar(this);
}

void NightFall::Entidades::Personagens::Jogador::executar ()
{
    //mover();
}

void NightFall::Entidades::Personagens::Jogador::salvar() {}

void NightFall::Entidades::Personagens::Jogador::mover()
{
    /*
    deltaTempo = relogioMovimento.getElapsedTime().asSeconds();
    
    if (!noChao)
        aceleracao.y += 1000.0f;

    //segundo a fisica, velocidade é aceleracao * tempo

    velocidade += aceleracao * deltaTempo;

    if (velocidade.x > velocidadeMax) 
        velocidade.x = velocidadeMax;
    if (velocidade.x < -velocidadeMax) 
        velocidade.x = -velocidadeMax;

    sf::Vector2f movimento = velocidade * deltaTempo;

    (this)->moverCorpo(movimento);

    if ( fabs(aceleracao.x) < 0.001f && noChao) //nao esta se movendo para nenhum dos dois lados (eu acho)
    {
        if (velocidade.x > 0.0f || velocidade.x < 0.0f)
        {
            int sinal_da_friccao;
            
            if (velocidade.x > 0.0f)
                sinal_da_friccao = 1;
            else
                sinal_da_friccao = -1;

            velocidade.x -= sinal_da_friccao * FRICCAO * deltaTempo;

            if ((sinal_da_friccao > 0 && velocidade.x < 0) || (sinal_da_friccao < 0 && velocidade.x > 0))
            //isso é errado porque o sinal da friccao deve ser o mesmo da velocidade
                velocidade.x = 0;
        }
    }

    aceleracao = sf::Vector2f(0.f, 0.f);
    relogioMovimento.restart();
    */
}

void NightFall::Entidades::Personagens::Jogador::pular()
{
    /*
    if (noChao)
    {
        velocidadeAtual.y = -forcaPulo;
        noChao = false;
    }
    */
}

void NightFall::Entidades::Personagens::Jogador::atacar()
{
    
}

void NightFall::Entidades::Personagens::Personagem::setVelocidade(float vel)
{
    velocidade = vel;
}

