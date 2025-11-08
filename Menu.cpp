#include "Menu.h"
#include "Gerenciador_Grafico.h"
#include "Jogo.h"

NightFall::Menu::Menu() : Ente()
{
	pJog = nullptr;
    pGG = nullptr;

    botaoFase1.setSize(sf::Vector2f(200, 100));
    botaoFase1.setFillColor(sf::Color(30, 30, 60));
    botaoFase1.setOutlineThickness(3);
    botaoFase1.setOutlineColor(sf::Color::White);

    botaoFase2.setSize(sf::Vector2f(200, 100));
    botaoFase2.setFillColor(sf::Color(60, 0, 0));
    botaoFase2.setOutlineThickness(3);
    botaoFase2.setOutlineColor(sf::Color::White);
 

    tituloMenu.setString("NightFall");
    tituloMenu.setCharacterSize(60);
    tituloMenu.setFillColor(sf::Color::White);

    textoFase1.setString("Fase 1");
    textoFase1.setCharacterSize(30);
    textoFase1.setFillColor(sf::Color::White);

    textoFase2.setString("Fase 2");
    textoFase2.setCharacterSize(30);
    textoFase2.setFillColor(sf::Color::White);
}

NightFall::Menu::~Menu()
{
}

void NightFall::Menu::setJogo(Jogo* pjogo)
{
	pJog = pjogo;
}

void NightFall::Menu::setGerGrafico(Gerenciadores::Gerenciador_Grafico* pGer)
{
    pGG = pGer;

    if (pGG)
    {
        sf::Font* fonte = pGG->getFonte();
        if (fonte == nullptr) {
            std::cout << "ERRO: Menu nao conseguiu pegar a fonte do pGG!" << std::endl;
            return;
        }

    

        // Aplicar a fonte
        tituloMenu.setFont(*fonte);
        textoFase1.setFont(*fonte);
        textoFase2.setFont(*fonte);

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
        float posX_Botao1 = (tamJanela.x - (botaoFase1.getSize().x + botaoFase2.getSize().x + espacamento)) / 2.0f;

        // Define as posições
        botaoFase1.setPosition(posX_Botao1, posY);
        botaoFase2.setPosition(posX_Botao1 + botaoFase1.getSize().x + espacamento, posY);
    

        // Centralizar Texto 1 (dentro do botaoFase1)
        sf::FloatRect rectBotao1 = botaoFase1.getGlobalBounds();
        sf::FloatRect rectTexto1 = textoFase1.getGlobalBounds();
        textoFase1.setPosition(
            rectBotao1.left + (rectBotao1.width - rectTexto1.width) / 2.0f - rectTexto1.left,
            rectBotao1.top + (rectBotao1.height - rectTexto1.height) / 2.0f - rectTexto1.top
        );

        // Centralizar Texto 2 (dentro do botaoFase2)
        sf::FloatRect rectBotao2 = botaoFase2.getGlobalBounds();
        sf::FloatRect rectTexto2 = textoFase2.getGlobalBounds();
        textoFase2.setPosition(
            rectBotao2.left + (rectBotao2.width - rectTexto2.width) / 2.0f - rectTexto2.left,
            rectBotao2.top + (rectBotao2.height - rectTexto2.height) / 2.0f - rectTexto2.top
        );
    }
}

void NightFall::Menu::executar()
{
    if (pGG == nullptr)
        return;

    // UTILIZAR O GERENCIADOR DE EVENTOS DEPOIS
    sf::RenderWindow* janela = pGG->getWindow();

    while (janela->isOpen()) 
	{
        sf::Event event;
        while (janela->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                pGG->fecharJanela();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) { // Se o botão esquerdo do mouse foi clicado

                    // Obtém a posição do clique do mouse
                    sf::Vector2f mousePos = janela->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    // Verifica se o clique ocorreu dentro do botão da Fase 1
                    if (botaoFase1.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Botao Fase 1 clicado!" << std::endl;
                        pJog->iniciarFase1(); 
                    }
                    // Verifica se o clique ocorreu dentro do botão da Fase 2
                    else if (botaoFase2.getGlobalBounds().contains(mousePos)) {
                        std::cout << "Botao Fase 2 clicado!" << std::endl;
                       // pJog->iniciarFase2(); 
                    }
                }
            }
        }

        janela->clear(); 

        janela->draw(corpo); // Desenha o fundo
        janela->draw(botaoFase1);
        janela->draw(botaoFase2);
        janela->draw(tituloMenu);
        janela->draw(textoFase1);
        janela->draw(textoFase2);

        janela->display();
	}

}
