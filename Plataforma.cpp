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
};

//ESTADOS DA PLATAFORMA
//ESTADO 0 - PLATAFORMA IMOVEL
//ESTADO 1 - PLATAFORMA MOVEL
//ESTADO 2 - PAREDE

NightFall::Entidades::Obstaculos::Plataforma::Plataforma() : 
    Obstaculo (),
    altura(3),
    posicaoOriginalY(0),
    movel(rand()%3),
    amplitudeMovimento(25.f)
{
    id = 4;     //ID DA CLASSE PLATAFORMA EH 4
    corpo.setScale(0.3f, altura * 0.1f);

    if (movel)
    {
        estado = 1;
    }
    else
    {
        estado = 0;
    }

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

NightFall::Entidades::Obstaculos::Plataforma::Plataforma(int est) :
    Obstaculo(),
    altura(6),
    posicaoOriginalY(0),
    amplitudeMovimento(25.f)
{
    id = 4;
    estado = est;
    if (estado == 2)
    {
        (this)->setTextura("Parede");
        corpo.setScale(0.3f, altura * 0.1f);
        setPosicao(640.0f, pGG->getAlturaChao() - getTamanho().y);
    }
    else
    {
        if (est)
        {
            movel = true;
        }
        else
        {
            movel = false;
        }
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
        return; 

    if (sobrepos.x < sobrepos.y)
    {
        // Colisão horizontal empurra lateralmente
        if (dist.x > 0.f)
            p->setPosicao(posJog.x + sobrepos.x, posJog.y); // empurra pra direita
        else
            p->setPosicao(posJog.x - sobrepos.x, posJog.y); // empurra pra esquerda

        // zera velocidade horizontal para não deslizar
        p->setVelocidade(sf::Vector2f(0.f, p->getVelocidade().y));
    }
    else
    {
        // Colisão vertical empurra pra cima/baixo
        if (dist.y > 0.f)
        {
            // Jogador abaixo da plataforma
            p->setPosicao(posJog.x, posJog.y + sobrepos.y);
            p->setVelocidade(sf::Vector2f(p->getVelocidade().x, 0.f));
        }
        else
        {
            // Jogador em cima da plataforma
            p->setPosicao(posJog.x, posJog.y - sobrepos.y);
            p->setVelocidade(sf::Vector2f(p->getVelocidade().x, 0.f));
            p->setNoChao(true);
        }
    }
}


void NightFall::Entidades::Obstaculos::Plataforma::executar()
{
    deltaTempo = relogioMovimento.getElapsedTime().asSeconds();
    relogioMovimento.restart();
    cooldownInteracao += deltaTempo;
    
    if (estado != 1)
    {
        if (getPosicao().y < pGG->getAlturaChao() - getTamanho().y)
        {
            gravitar();
            if (estado != 2)  //as plataformas propriamente ditas
            {                 //(todas em que estado != 2)
                empuxo();     //são capazes de flutuar, portanto, sobem tanto quanto
            }                 //descem, pelo efeito da gravidade
        }
        return;
    }

    //amplitude é a distancia entre o meio e o topo da onda senoide (matematica)
    float velocidade = 2.f;     //velocidade em que a onda varia

    //a funcao sin() do std é a funcao matematica seno, que varia entre -1 e 1.
    //nos multiplicamos pela amplitude para que ela nao varie apenas entre -1 e 1
    //e sim entre 25 pixels a baixo e 25 pixels a cima
    float movimentoVertical = std::sin(cooldownInteracao * velocidade) * amplitudeMovimento;
    //isso se assemelha a funcao matematica Y = sen(X* velocidade) * amplitude
        
    setPosicao(getPosicao().x, posicaoOriginalY + movimentoVertical);
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
    };
}

void NightFall::Entidades::Obstaculos::Plataforma::salvar()
{
    bufferInterno.str("");
    buffer.clear();

    salvarDataBuffer();
}

void NightFall::Entidades::Obstaculos::Plataforma::salvarDataBuffer()
{
    Obstaculo::salvarDataBuffer();
    buffer << altura << " " << posicaoOriginalY << " "
        << movel << " " << amplitudeMovimento 
        << std::endl;
}

void NightFall::Entidades::Obstaculos::Plataforma::carregarPlataforma
        (int alt, float origPosY, bool mobilidade, int amplitude)
{
    altura = alt;
    posicaoOriginalY = origPosY;
    movel = mobilidade;
    amplitudeMovimento = amplitude;
}


void NightFall::Entidades::Obstaculos::Plataforma::empuxo()
{
    float velocidade = 10.0f; // pixels por segundo

    // Calcula nova posição subindo
    float novaY = getPosicao().y - velocidade * deltaTempo;

    // Limite superior (por exemplo, o teto ou posição limite)
    float limiteSuperior = posicaoOriginalY; // você escolhe seu limite real

    // Se passou do limite, fixa
    if (novaY < limiteSuperior)
        novaY = limiteSuperior;

    setPosicao(getPosicao().x, novaY);
}