#include "Morcego.h"
#include "Jogador.h"

sf::Vector2f NightFall::Entidades::Personagens::Morcego::ultimaPosicao = { 0, 200 };

NightFall::Entidades::Personagens::Morcego::Morcego() : Inimigo(), raio(0)
{
	nivel_maldade = 1;
	num_vidas = 1;
	corpo.setScale(0.1f, 0.1f);
	ultimaPosicao.x += 100.0f + ((rand() % 10) - 2) * 10; // mudar número

	//retirado para manter os morcegos em mesmo nivel
	//ultimaPosicao.y += 30.0f + ((rand() % 10) - 2) * 10; // mudar números
	setPosicao(ultimaPosicao);
}

NightFall::Entidades::Personagens::Morcego::~Morcego()
{
}

void NightFall::Entidades::Personagens::Morcego::danificar(Jogador* p)
{
	if (p != nullptr)
		p->receberDano(nivel_maldade);
}

void NightFall::Entidades::Personagens::Morcego::salvar()
{
}

void NightFall::Entidades::Personagens::Morcego::executar()
{
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
}

void NightFall::Entidades::Personagens::Morcego::mover()
{
    deltaTempo = relogioMovimento.restart().asSeconds();

    if (getPosicao().y >= 420.0f && velocidadeAtual.y >= 0.f)
    {
        noChao = true;
        sf::Vector2f pos = getPosicao();
        pos.y = 420.0f;
        setPosicao(pos);
        aceleracao.y = 0.0f;
        velocidadeAtual.y = 0.0f;
    }
    else
    {
        noChao = false;
    }

    /*
    if (!noChao)
    {
        bool sinal = (bool) rand() % 2;
        if (sinal)
            aceleracao.y += 100;
        else
            aceleracao.y -= 100;
    }
    */
        

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