#include "Jogo.h"
#include "Entidade.h"

NightFall::Jogo::Jogo() : 
window(sf::VideoMode(1000, 600), "Jogo TecProg", sf::Style::Close)
{
    executar();
}

NightFall::Jogo::~Jogo() {}

void NightFall::Jogo::executar()
{
    pJog1.setWindow(&window);
    pJog1.setVelocidade(0.1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            pJog1.mover(1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            pJog1.mover(2);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pJog1.mover(3);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pJog1.mover(4);
        }

        window.clear();
        pJog1.draw();
        window.display();
    }

}