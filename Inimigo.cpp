#include "Inimigo.h"
#include "Jogador.h"
#include "Gerenciador_Grafico.h"
#include <cmath>

NightFall::Entidades::Personagens::Jogador* NightFall::Entidades::Personagens::Inimigo::pJogador1 = nullptr;
NightFall::Entidades::Personagens::Jogador* NightFall::Entidades::Personagens::Inimigo::pJogador2 = nullptr;

NightFall::Entidades::Personagens::Inimigo::Inimigo() : 
	Personagem(), 
	nivel_maldade(10+rand()%20),
	alcancePerseguir(200.0f),
	direcaoAleatoria( rand() % 3 ),
    tempoVagar(0.0f),
    cooldownDano(0.0f)
{
    corpo.setOrigin(0.f, 0.f);
    
	num_vidas = 20;
}

NightFall::Entidades::Personagens::Inimigo::~Inimigo()
{
	nivel_maldade = 0;
}

void NightFall::Entidades::Personagens::Inimigo::mover()
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

    if (fabs(aceleracao.x) < 0.001f && noChao) //nao esta se movendo para nenhum dos dois lados (eu acho)
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

void NightFall::Entidades::Personagens::Inimigo::perseguir(sf::Vector2f posJogador, sf::Vector2f posInimigo)
{
	if (posJogador.x < posInimigo.x)
	{
		aplicarForca(sf::Vector2f(-100.0f, 0.0f));
	}
	else
	{
		aplicarForca(sf::Vector2f(100.0f, 0.0f));
	}
}

void NightFall::Entidades::Personagens::Inimigo::vagar()
{
    tempoVagar += deltaTempo;  

    if (tempoVagar >= 1.0f)
    {
        tempoVagar = 0.f;
        direcaoAleatoria = rand() % 3;
    }

    // 0 é ficar parado
    // 1 é esquerda
    // 2 é direita

    switch (direcaoAleatoria)
    {
    case 0:
        break;
    case 1:
        aplicarForca(sf::Vector2f(-2000.0f, 0.f));
        break;
    default:
        aplicarForca(sf::Vector2f(2000.f, 0.f));
        break;
    }
}

void NightFall::Entidades::Personagens::Inimigo::setJogador(Jogador* pJogad)
{
    if (pJogador1 == nullptr)
        pJogador1 = pJogad;
    else if (pJogador2 == nullptr)
        pJogador2 = pJogad;
}

const bool NightFall::Entidades::Personagens::Inimigo::podeDanificar()
{
    cooldownDano += deltaTempo;

    if (cooldownDano >= 0.5f)
    {
        cooldownDano = 0.f;
        return true;
    }
    return false;
}
