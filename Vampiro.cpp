#include "Jogador.h"
#include "Gerenciador_Grafico.h"
#include <iostream>
#include "Vampiro.h"
#include "Faca.h"

NightFall::Entidades::Personagens::Vampiro::Vampiro() :
    pFaca(nullptr), 
    quandoAtirar(0.0), 
    jaAtirou(false),
    indiceDaFacaAssociada(-1)
{
    id = 9;
    forca = 5 + rand()%11;
    nivel_maldade = 60;
    num_vidas = 80;
    corpo.setScale(0.1f, 0.1f);
    ultimaPosicao.x += 200.0f + ((rand() % 10) - 5) * 10;
    setPosicao(ultimaPosicao);
    velocidade = 50.0f;
}

NightFall::Entidades::Personagens::Vampiro::~Vampiro()
{
}

sf::Vector2f NightFall::Entidades::Personagens::Vampiro::ultimaPosicao = { 0, 0 };


void NightFall::Entidades::Personagens::Vampiro::danificar(Jogador* p)
{
    if (p != nullptr && podeDanificar())
    {
        p->receberDano(nivel_maldade + forca);
        std::cout << "Esqueleto danificou" << std::endl;
    }
}

void NightFall::Entidades::Personagens::Vampiro::executar()
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
    
    if (!jaAtirou)
        quandoAtirar += deltaTempo;

    if (quandoAtirar >= forca && pFaca != nullptr)
    {
        ativarFaca();
        std::cout << "Executou o deltatempo" << std::endl;
        quandoAtirar = 0.0;
        jaAtirou = true;
    }
        
}

void NightFall::Entidades::Personagens::Vampiro::resetarUltimaPosicao()
{
    ultimaPosicao = sf::Vector2f(0.0f, 0.0f);
}

void NightFall::Entidades::Personagens::Vampiro::setFaca(Faca* pFac)
{
    if (pFac != nullptr)
    {
        pFaca = pFac;
        pFac->setVampiro(this);
        indiceDaFacaAssociada = pFac->getIndiceFaca();
    }
}

void NightFall::Entidades::Personagens::Vampiro::ativarFaca()
{
    bool esquerda = true;
    pFaca->setAtivo(true);
    if ( pJogador1->getPosicao().x < getPosicao().x)
    {
        pFaca->setDirecao(esquerda);
    }
    else
    {
        pFaca->setDirecao(!esquerda);
    }
}

void NightFall::Entidades::Personagens::Vampiro::salvar()
{
    bufferInterno.str("");
    buffer.clear();

    salvarDataBuffer();
}

void NightFall::Entidades::Personagens::Vampiro::carregarVampiro
    (short int forcaSalva, bool atirou, int indFaca)
{
    forca = forcaSalva;
    jaAtirou = atirou;
    indiceDaFacaAssociada = indFaca;
}

void NightFall::Entidades::Personagens::Vampiro::salvarDataBuffer()
{
    Inimigo::salvarDataBuffer();
    buffer << forca << " " << jaAtirou << " " 
        << indiceDaFacaAssociada <<std::endl;
    //quandoAtirar é inicializado igual para todos os vampiros
    //pFaca sera recuperado de forma diferente
}
