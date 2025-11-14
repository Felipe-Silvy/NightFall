#include "Plataforma.h"
#include "Teia.h"
#include "Jogador.h"
#include "Gerenciador_Grafico.h"
#include <algorithm> 
#include <cstdlib>  
#include <ctime>

std::vector<sf::Vector2f> NightFall::Entidades::Obstaculos::Plataforma::posicoesParaPlataforma = {
    { 50.0f, 400.0f },
    { 850.0f, 400.0f },
    { 250.0f, 230.0f },
    { 650.0f, 230.0f },
    { 1050.0f, 230.0f },
    { 40.0f, 80.0f }
};

NightFall::Entidades::Obstaculos::Plataforma::Plataforma() : 
    Obstaculo (),
    altura(3),
    parede(false),
    posicaoOriginalY(0),
    movel(rand()%3)
{
    corpo.setScale(0.3f, altura * 0.1f);

    if (Plataforma::posicoesParaPlataforma.empty())
    {
        setPosicao(sf::Vector2f(100.f, 200.f));
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
    posicaoOriginalY = posicao.y;
    std::cout <<"Plataforma x = " << posicao.x << " y = " << posicao.y << std::endl;
}

NightFall::Entidades::Obstaculos::Plataforma::Plataforma(bool par, bool mov) :
    Obstaculo(),
    altura(6),
    parede(par),
    movel(mov),
    posicaoOriginalY(0)
{
    if (par)
    {
        (this)->setTextura("Parede");
        corpo.setScale(0.3f, altura * 0.1f);
        setPosicao(640.0f, pGG->getAlturaChao() - getTamanho().y);
    }
    else
    {
        corpo.setScale(0.3f, altura * 0.1f);

        if (Plataforma::posicoesParaPlataforma.empty())
        {
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
        posicaoOriginalY = posicao.y;
    }
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
    if (parede || !movel)
        return;

    deltaTempo = relogioMovimento.getElapsedTime().asSeconds();
    relogioMovimento.restart();
    cooldownInteração += deltaTempo;

    float amplitude = 25.f;     //distancia entre o meio e o topo da onda senoide (matematica)
    float velocidade = 2.f;     //velocidade em que a onda varia

    //a funcao sin() do std é a funcao matematica seno, que varia entre -1 e 1.
    //nos multiplicamos pela amplitude para que ela nao varie apenas entre -1 e 1
    //e sim entre 25 pixels a baixo e 25 pixels a cima
    float movimentoVertical = std::sin(cooldownInteração * velocidade) * amplitude;
    //isso se assemelha a funcao matematica Y = sen(X* velocidade) * amplitude
        
    setPosicao(getPosicao().x, posicaoOriginalY + movimentoVertical);
}

void NightFall::Entidades::Obstaculos::Plataforma::salvar()
{

}

void NightFall::Entidades::Obstaculos::Plataforma::setPosicaoOriginalY(float pos)
{
    posicaoOriginalY = pos;
}

void NightFall::Entidades::Obstaculos::Plataforma::resetPosicoes()
{
    NightFall::Entidades::Obstaculos::Plataforma::posicoesParaPlataforma = {
    { 50.0f, 400.0f },
    { 850.0f, 400.0f },
    { 250.0f, 230.0f },
    { 650.0f, 230.0f },
    { 1050.0f, 230.0f },
    { 20.0f, 80.0f }
    };
}
