#include "Plataforma.h"
#include "Teia.h"
#include "Jogador.h"
#include <algorithm> // para std::swap
#include <cstdlib>   // para rand
#include <ctime>

std::vector<sf::Vector2f> NightFall::Entidades::Obstaculos::Plataforma::posicoesParaPlataforma = {
    { 50.0f, 400.0f },
    { 600.0f, 400.0f },
    { 900.0f, 400.0f },
    { 200.0f, 230.0f },
    { 500.0f, 230.0f },
    { 1000.0f, 230.0f }
};

NightFall::Entidades::Obstaculos::Plataforma::Plataforma() : 
    Obstaculo (),
    altura(300)
{
    corpo.setScale(0.3f, 0.3f);


    if (Plataforma::posicoesParaPlataforma.empty())
    {
        // fallback: posição (0,0) ou qualquer comportamento definido pela classe
        setPosicao(sf::Vector2f(100.f, 400.f));
        return;
    }

    int qualPosicao = rand() % (int)(Plataforma::posicoesParaPlataforma.size());

    sf::Vector2f posicao = Plataforma::posicoesParaPlataforma[qualPosicao];

    if (qualPosicao != static_cast<int>(Plataforma::posicoesParaPlataforma.size()) - 1)
    {
        std::swap(Plataforma::posicoesParaPlataforma[qualPosicao],
                  Plataforma::posicoesParaPlataforma.back());
    }
    Plataforma::posicoesParaPlataforma.pop_back();

    setPosicao(posicao); 
}

NightFall::Entidades::Obstaculos::Plataforma::~Plataforma()
{
}

void NightFall::Entidades::Obstaculos::Plataforma::obstaculizar(Personagens::Jogador* p)
{
    if (p == nullptr)
        return;

    // Calcula os centros dos dois objetos
    sf::Vector2f posJog = p->getPosicao();
    sf::Vector2f tamJog = p->getTamanho();

    sf::Vector2f posPlat = getPosicao();
    sf::Vector2f tamPlat = getTamanho();

    sf::Vector2f centroJog = posJog + tamJog * 0.5f;
    sf::Vector2f centroPlat = posPlat + tamPlat * 0.5f;

    // Calcula as distancias e sobreposicao
    sf::Vector2f dist;
    dist.x = centroJog.x - centroPlat.x;
    dist.y = centroJog.y - centroPlat.y;

    sf::Vector2f sobrepos;
    sobrepos.x = (tamJog.x + tamPlat.x) * 0.5f - std::fabs(dist.x);
    sobrepos.y = (tamJog.y + tamPlat.y) * 0.5f - std::fabs(dist.y);

    if (sobrepos.x <= 0.f || sobrepos.y <= 0.f)
        return; // sem colisao real

    //  Decide o eixo de menor penetracao (onde resolver)
    if (sobrepos.x < sobrepos.y)
    {
        // Colisão horizontal empurra lateralmente
        if (dist.x > 0.f)
            p->setPosicao(posJog.x + sobrepos.x, posJog.y); // empurra pra direita
        else
            p->setPosicao(posJog.x - sobrepos.x, posJog.y); // empurra pra esquerda

        // zera velocidade horizontal para não deslizar
        p->setVelocidadeX(0.f);
    }
    else
    {
        // Colisão vertical empurra pra cima/baixo
        if (dist.y > 0.f)
        {
            // Jogador abaixo da plataforma
            p->setPosicao(posJog.x, posJog.y + sobrepos.y);
            p->setVelocidadeY(0.f);
        }
        else
        {
            // Jogador em cima da plataforma
            p->setPosicao(posJog.x, posJog.y - sobrepos.y);
            p->setVelocidadeY(0.f);
            p->setNoChao(true); // agora ele esta apoiado
        }
    }
}


void NightFall::Entidades::Obstaculos::Plataforma::executar()
{
    //sobe e desce
}

void NightFall::Entidades::Obstaculos::Plataforma::salvar()
{

}