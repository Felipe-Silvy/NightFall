#include "Menu.h"
#include "Gerenciador_Grafico.h"
#include "Jogo.h"

NightFall::Menu::Menu() : botaoFase1(), botaoFase2()
{
	pJog = nullptr;
    pGG = nullptr;

    botaoFase1.setSize(sf::Vector2f(200, 100));
    botaoFase1.setFillColor(sf::Color::Green);
    botaoFase1.setOutlineThickness(3);
    botaoFase1.setOutlineColor(sf::Color::White);
    botaoFase1.setPosition(100, 200); // Posição do quadrado

    botaoFase2.setSize(sf::Vector2f(200, 100));
    botaoFase2.setFillColor(sf::Color::Magenta);
    botaoFase2.setOutlineThickness(3);
    botaoFase2.setOutlineColor(sf::Color::White);
    botaoFase2.setPosition(400, 200); // Posição do quadrado
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
}

void NightFall::Menu::executar()
{
    if (pGG == nullptr)
        return;

    sf::RenderWindow* janela = pGG->getWindow();

    while (pGG->verificaAbertura()) 
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

        janela->clear(sf::Color(50, 50, 50)); // Fundo cinza escuro
        janela->draw(botaoFase1);
        janela->draw(botaoFase2);
        janela->display();
	}

}











