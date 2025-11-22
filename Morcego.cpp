#include "Morcego.h"
#include "Jogador.h"
#include "Gerenciador_Grafico.h"
#include <iostream>

sf::Vector2f NightFall::Entidades::Personagens::Morcego::ultimaPosicao = { 0.0f, 300.0f };

NightFall::Entidades::Personagens::Morcego::Morcego() :
    Inimigo(),
    raio(1.5f),
    voo(1000.0f)
{
    id = 5;
	nivel_maldade = 20;
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
    if (p != nullptr && podeDanificar() )
    {
        p->receberDano(nivel_maldade);
        std::cout << "Morcego danificou" << std::endl;
    }
}

void NightFall::Entidades::Personagens::Morcego::executar()
{
    sf::Vector2f posJogador1 = pJogador1->getCorpo().getPosition();
    sf::Vector2f posJogador2;

    if (pJogador2)
        posJogador2 = pJogador2->getCorpo().getPosition();
    sf::Vector2f posInimigo = corpo.getPosition();

    if (fabs(posJogador1.x - posInimigo.x) <= alcancePerseguir * raio &&
        fabs(posJogador1.y - posInimigo.y) <= alcancePerseguir * raio)
    {
        perseguir(posJogador1, posInimigo);
    }
    else if (fabs(posJogador2.x - posInimigo.x) <= alcancePerseguir * raio &&
        fabs(posJogador2.y - posInimigo.y) <= alcancePerseguir * raio)
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

void NightFall::Entidades::Personagens::Morcego::mover()
{
    deltaTempo = relogioMovimento.restart().asSeconds();

    if (getPosicao().y + getTamanho().y >= pGG->getAlturaChao()
        && velocidadeAtual.y >= 0.f)
    {
        noChao = true;
        sf::Vector2f pos = getPosicao();
        pos.y = pGG->getAlturaChao() - getTamanho().y;
        setPosicao(pos);
        aceleracao.y = 0.0f;
        velocidadeAtual.y = 0.0f;
    }
    else
    {
        noChao = false;
    }
  
    if (!noChao)
    {
        aceleracao.y += 1000;
        aceleracao.y -= voo; //Gracas ao voo do morcego.
        //Ele se acelera para cima com a mesma aceleracao
        //que a gravidade. Assim ele é mantido no lugar
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

void NightFall::Entidades::Personagens::Morcego::resetarUltimaPosicao()
{
    ultimaPosicao = sf::Vector2f(0.0f, 300.0f);
}

void NightFall::Entidades::Personagens::Morcego::salvar()
{
    bufferInterno.str("");
    buffer.clear();

    salvarDataBuffer();
}

void NightFall::Entidades::Personagens::Morcego::carregarMorcego(float rai)
{
    raio = rai;
}

void NightFall::Entidades::Personagens::Morcego::salvarDataBuffer()
{
    //voo e raio sao sempre os mesmos para todos 
    //os morcegos logo nao precisam ser armazenados
    Inimigo::salvarDataBuffer();
    buffer << raio << std::endl;
}
