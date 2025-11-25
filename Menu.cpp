#include "Menu.h"
#include "Gerenciador_Grafico.h"
#include "Jogo.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

NightFall::Menu::Menu() : Ente(), sairDoLoop(false)
{
    id = 0;     //ID DA CLASSE MENU EH 0
	pJog = nullptr;

    botao1.setSize(sf::Vector2f(200, 100));
    botao1.setFillColor(sf::Color(30, 30, 60));
    botao1.setOutlineThickness(3);
    botao1.setOutlineColor(sf::Color::White);

    botao2.setSize(sf::Vector2f(200, 100));
    botao2.setFillColor(sf::Color(60, 0, 0));
    botao2.setOutlineThickness(3);
    botao2.setOutlineColor(sf::Color::White);
 

    tituloMenu.setString("NightFall");
    tituloMenu.setCharacterSize(60);
    tituloMenu.setFillColor(sf::Color::White);


    textoBotao1.setCharacterSize(30);
    textoBotao1.setFillColor(sf::Color::White);

    textoBotao2.setCharacterSize(30);
    textoBotao2.setFillColor(sf::Color::White);
}

NightFall::Menu::~Menu()
{
}

void NightFall::Menu::setJogo(Jogo* pjogo)
{
    pJog = pjogo;
}

void NightFall::Menu::executar()
{
    if (pGG == nullptr)
        return;

    sf::Font* fonte = pGG->getFonte();
    if (fonte == nullptr) {
        std::cout << "ERRO: Menu nao conseguiu pegar a fonte do pGG!" << std::endl;
        return;
    }

    // Aplicar a fonte
    tituloMenu.setFont(*fonte);
    textoBotao1.setFont(*fonte);
    textoBotao2.setFont(*fonte);

    // Posicionar os textos (centralizados)

    // Centralizar Título (no topo da janela)
    sf::Vector2f tamJanela = static_cast<sf::Vector2f>(pGG->getWindow()->getSize());
    sf::FloatRect rectTitulo = tituloMenu.getGlobalBounds();
    tituloMenu.setPosition((tamJanela.x - rectTitulo.width) / 2.0f, 50.0f);

    // Centralizando e escalando Imagem de Fundo 
    setTextura("FundoMenu");
    const sf::Texture* pTextura = corpo.getTexture();
    // Verificação de segurança (impede crash)
    if (pTextura == nullptr) {
        std::cout << "ERRO: Sprite 'corpo' (Menu) sem textura!" << std::endl;
        return;
    }
    sf::Vector2f tamTextura = static_cast<sf::Vector2f>(pTextura->getSize());
    // Calcula e aplica a escala
    corpo.setScale(tamJanela.x / tamTextura.x, tamJanela.y / tamTextura.y);

    corpo.setPosition(0.f, 0.f);

    //Centralizando Botões
    const float espacamento = 100.0f; // Espaço entre os botões
    const float posY = 200.0f;      // Altura Y desejada

    // Calcula o "X" inicial para o primeiro botão
    float posX_Botao1 = (tamJanela.x - (botao1.getSize().x + botao2.getSize().x + espacamento)) / 2.0f;

    // Define as posições
    botao1.setPosition(posX_Botao1, posY);
    botao2.setPosition(posX_Botao1 + botao1.getSize().x + espacamento, posY);


    escolheAcao();      //JOGAR OU RANKING
}

void NightFall::Menu::executarTelaPause()
{
    if (pGG == nullptr)
        return;

    sf::Font* fonte = pGG->getFonte();
    if (fonte == nullptr) {
        std::cout << "ERRO: Menu nao conseguiu pegar a fonte do pGG!" << std::endl;
        return;
    }

    // Aplicar a fonte
    tituloMenu.setFont(*fonte);
    textoBotao1.setFont(*fonte);
    textoBotao2.setFont(*fonte);

    // Posicionar os textos (centralizados)

    // Centralizar Título (no topo da janela)
    sf::Vector2f tamJanela = static_cast<sf::Vector2f>(pGG->getWindow()->getSize());
    sf::FloatRect rectTitulo = tituloMenu.getGlobalBounds();
    tituloMenu.setPosition((tamJanela.x - rectTitulo.width) / 2.0f, 50.0f);

    // Centralizando e escalando Imagem de Fundo 
    setTextura("FundoMenu");
    const sf::Texture* pTextura = corpo.getTexture();
    // Verificação de segurança (impede crash)
    if (pTextura == nullptr) {
        std::cout << "ERRO: Sprite 'corpo' (Menu) sem textura!" << std::endl;
        return;
    }
    sf::Vector2f tamTextura = static_cast<sf::Vector2f>(pTextura->getSize());
    // Calcula e aplica a escala
    corpo.setScale(tamJanela.x / tamTextura.x, tamJanela.y / tamTextura.y);

    corpo.setPosition(0.f, 0.f);

    //Centralizando Botões
    const float espacamento = 100.0f; 
    const float posY = 200.0f;     

    float posX_Botao1 = (tamJanela.x - (botao1.getSize().x + botao2.getSize().x + espacamento)) / 2.0f;

    // Define as posições
    botao1.setPosition(posX_Botao1, posY);
    botao2.setPosition(posX_Botao1 + botao1.getSize().x + espacamento, posY);

    escolhePause();
}

void NightFall::Menu::escolheAcao()     //JOGAR OU RANKING
{
    textoBotao1.setString("Jogar");
    textoBotao2.setString("Ranking");
    centralizarTextos();

    loopComAcoes(
        [this]() { escolheJogo(); },        //NOVO OU CONTINUAR
        [this]() { mostrarRanking(); }      //RANKING
    );
}

void NightFall::Menu::escolheJogo()
{
    textoBotao1.setString("Novo");
    textoBotao2.setString("Continuar");
    centralizarTextos();

    loopComAcoes(
        [this]() { escolheJogadores(); },
        [this]() { continuarJogo(); }
    );
}

void NightFall::Menu::escolheJogadores()
{
    textoBotao1.setString("1 Jogador");
    textoBotao2.setString("2 Jogadores");
    centralizarTextos();

    loopComAcoes(
        [this]() { pJog->setDoisJogadores(false); escolheFase(); },
        [this]() { pJog->setDoisJogadores(true); escolheFase(); }   //FASE 1 OU 2
    );
}

void NightFall::Menu::escolheFase()
{
    textoBotao1.setString("Fase 1");
    textoBotao2.setString("Fase 2");
    centralizarTextos();

    loopComAcoes(
        [this]() { pJog->iniciarFase1(); escolheAcao(); },
        [this]() { pJog->iniciarFase2(); escolheAcao(); }
    );
    //Depois de acabar a fase, volta pro menu de escolher ação
}

void NightFall::Menu::escolhePause()
{
    textoBotao1.setString("Voltar a fase");
    textoBotao2.setString("Salvar");
    centralizarTextos();

    loopComAcoes(
        [&]() { sairDoLoop = true; },  // Voltar
        [this]() { pJog->salvarJogo(); }
    );
    sairDoLoop = false;
}

void NightFall::Menu::atualizarRanking(const std::vector<int>& pontos)
{
    using namespace std;

    struct Entrada {
        string nome;
        int score;
    };

    vector<Entrada> ranking;

    ifstream arqIn("Ranking.txt");
    if (arqIn.is_open()) {
        string nome;
        int score;

        while (arqIn >> nome >> score) {
            ranking.push_back({ nome, score });
            if (ranking.size() >= 5) break;
        }
        arqIn.close();
    }

    sort(ranking.begin(), ranking.end(),
        [](const Entrada& a, const Entrada& b) {
            return a.score > b.score; // Maior primeiro
        }
    );

    for (size_t i = 0; i < pontos.size(); i++)
    {
        int pontosJogador = pontos[i];
        bool entra = false;

        if (ranking.size() < 5)
            entra = true;
        else if (pontosJogador > ranking.back().score)
            entra = true;

        if (!entra)
            continue;

        string nomeJogador = capturarNomeSFML(static_cast<int>(i) + 1);

        ranking.push_back({ nomeJogador, pontosJogador });

        sort(ranking.begin(), ranking.end(),
            [](const Entrada& a, const Entrada& b) {
                return a.score > b.score;
            }
        );

        if (ranking.size() > 5)
            ranking.resize(5);
    }

    ofstream arqOut("Ranking.txt", ios::trunc);
    if (!arqOut.is_open()) {
        cout << "ERRO AO SALVAR RANKING!" << endl;
        return;
    }

    for (auto& e : ranking)
        arqOut << e.nome << " " << e.score << "\n";

    arqOut.close();

    cout << "Ranking atualizado com sucesso!" << endl;
}



void NightFall::Menu::mostrarRanking()
{
    // Lê o ranking do arquivo
    struct Entrada {
        std::string nome;
        int score;
    };

    std::vector<Entrada> ranking;

    std::ifstream arq("Ranking.txt");
    if (arq.is_open()) {
        std::string nome;
        int score;
        while (arq >> nome >> score) {
            ranking.push_back({ nome, score });
        }
        arq.close();
    }

    // ordenar (
    std::sort(ranking.begin(), ranking.end(),
        [](const Entrada& a, const Entrada& b) {
            return a.score > b.score;
        }
    );

    sf::RenderWindow* janela = pGG->getWindow();

    // Ajustar textos dos botões para "Voltar"
    textoBotao1.setString("Voltar");
    textoBotao2.setString("");
    centralizarTextos();

    // Título da tela de ranking
    sf::Text titulo;
    titulo.setFont(*(pGG->getFonte()));
    titulo.setString("Ranking");
    titulo.setCharacterSize(60);
    titulo.setFillColor(sf::Color::White);

    sf::Vector2f tamJanela = (sf::Vector2f)janela->getSize();
    sf::FloatRect rectTitulo = titulo.getGlobalBounds();
    titulo.setPosition((tamJanela.x - rectTitulo.width) / 2.f, 40.f);

    // Textos do ranking
    sf::Text textoLinha;
    textoLinha.setFont(*(pGG->getFonte()));
    textoLinha.setCharacterSize(32);
    textoLinha.setFillColor(sf::Color::White);

    // Posição inicial das linhas
    float startY = 160.f;

    sairDoLoop = false;

    // loop da tela
    while (janela->isOpen() && !sairDoLoop)
    {
        sf::Event event;
        while (janela->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                pGG->fecharJanela();

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = janela->mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y }
                );

                // Botão "Voltar"
                if (botao1.getGlobalBounds().contains(mousePos))
                {
                    sairDoLoop = true;
                    escolheAcao();      // VOLTA PARA O MENU PRINCIPAL
                }
            }
        }

        janela->clear();

        janela->draw(corpo);
        janela->draw(titulo);

        // Desenha cada linha do ranking
        float y = startY;
        for (int i = 0; i < ranking.size(); i++)
        {
            textoLinha.setString(
                std::to_string(i + 1) + ".  " +
                ranking[i].nome + " - " +
                std::to_string(ranking[i].score)
            );

            float posX = botao1.getPosition().x + botao1.getSize().x + 40.f;
            textoLinha.setPosition(posX, y);
            y += 50.f;

            janela->draw(textoLinha);
        }

        // Botão voltar
        janela->draw(botao1);
        janela->draw(textoBotao1);

        janela->display();
    }

    sairDoLoop = false;
}


void NightFall::Menu::continuarJogo()
{
    std::cout << "Continuando Jogo Salvo" << std::endl;
    pJog->recuperarJogo();
}

void NightFall::Menu::loopComAcoes(
    std::function<void()> acaoBotao1,
    std::function<void()> acaoBotao2
)
{
    sf::RenderWindow* janela = pGG->getWindow();

    while (janela->isOpen() && !sairDoLoop)
    {
        sf::Event event;
        while (janela->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)  
                pGG->fecharJanela();

            //VOLTAR PARA O PRIMEIRO MENU
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
                sairDoLoop = true;
                pJog->zerarJogador1();
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = janela->mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y }
                );

                if (botao1.getGlobalBounds().contains(mousePos))
                    acaoBotao1();

                if (botao2.getGlobalBounds().contains(mousePos))
                    acaoBotao2();
            }
        }

        janela->clear();

        janela->draw(corpo);
        janela->draw(botao1);
        janela->draw(botao2);
        janela->draw(tituloMenu);
        janela->draw(textoBotao1);
        janela->draw(textoBotao2);

        janela->display();
    }
}

void NightFall::Menu::centralizarTextos()
{
    // Centralizar Texto 1
    sf::FloatRect rectBotao1 = botao1.getGlobalBounds();
    sf::FloatRect rectTexto1 = textoBotao1.getLocalBounds();
    textoBotao1.setPosition(
        rectBotao1.left + (rectBotao1.width - rectTexto1.width) / 2.0f - rectTexto1.left,
        rectBotao1.top + (rectBotao1.height - rectTexto1.height) / 2.0f - rectTexto1.top
    );

    // Centralizar Texto 2
    sf::FloatRect rectBotao2 = botao2.getGlobalBounds();
    sf::FloatRect rectTexto2 = textoBotao2.getLocalBounds();
    textoBotao2.setPosition(
        rectBotao2.left + (rectBotao2.width - rectTexto2.width) / 2.0f - rectTexto2.left,
        rectBotao2.top + (rectBotao2.height - rectTexto2.height) / 2.0f - rectTexto2.top
    );
}

std::string NightFall::Menu::capturarNomeSFML(int numJog)
{
    std::cout << "capturar nome inicio" << std::endl;
    std::string nome = "";
    sf::Text texto;
    texto.setFont(*(pGG->getFonte()));
    texto.setCharacterSize(40);
    texto.setFillColor(sf::Color::White);
    texto.setPosition(100.f, 200.f);

    sf::RenderWindow* janela = pGG->getWindow();

    while (janela->isOpen())
    {
        sf::Event event;
        while (janela->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                janela->close();

            // Captura caracteres
            if (event.type == sf::Event::TextEntered)
            {
                // ENTER finaliza
                if (event.text.unicode == '\r' || event.text.unicode == '\n')
                    return nome;

                // BACKSPACE
                if (event.text.unicode == 8)
                {
                    if (!nome.empty())
                        nome.pop_back();
                }
                // Caractere normal
                else if (event.text.unicode < 128 &&
                    std::isalnum(static_cast<char>(event.text.unicode)))
                {
                    if (nome.size() < 12)  // limite opcional
                        nome += static_cast<char>(event.text.unicode);
                }
            }
        }

        texto.setString("Digite o nome do Jogador " + std::to_string(numJog) + ":\n" + nome);

        janela->clear();
        janela->draw(corpo);
        janela->draw(texto);
        janela->display();
    }

    return nome;
}