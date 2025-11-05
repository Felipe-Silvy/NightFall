#include "Jogo.h"
#include "Entidade.h"

NightFall::Jogo::Jogo() : GG() // SOBRECARGA COM PARAMETROS TLVZ
{
    executar();
}

NightFall::Jogo::~Jogo() {}

void NightFall::Jogo::executar()
{
        sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
        }

}