#include "Menu.h"
#include "Gerenciador_Grafico.h"
#include "Jogo.h"

NightFall::Menu::Menu() : Ente()
{
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


    escolheAcao();
}

void NightFall::Menu::escolheAcao()
{
    textoBotao1.setString("Jogar");
    textoBotao2.setString("Ranking");
    centralizarTextos();

    loopComAcoes(
        [this]() { escolheJogo(); },
        [this]() { mostrarRanking(); }
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
        [this]() { pJog->setDoisJogadores(true); escolheFase(); }
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
}

void NightFall::Menu::mostrarRanking()
{
    std::cout << "Mostrando Ranking" << std::endl;
}

void NightFall::Menu::continuarJogo()
{
    std::cout << "Continuando Jogo Salvo" << std::endl;
    // Vitor faça sua mágica aqui
}

void NightFall::Menu::loopComAcoes(
    std::function<void()> acaoBotao1,
    std::function<void()> acaoBotao2
)
{
    sf::RenderWindow* janela = pGG->getWindow();

    while (janela->isOpen())
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