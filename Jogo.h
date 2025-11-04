#pragma once

#include <SFML/Graphics.hpp>
#include "Jogador.h"

namespace NightFall {
    class Jogo
    {
    private:
        NightFall::Entidades::Personagens::Jogador pJog1;
        // GerenciadorGrafico GG;
        // ...

        sf::RenderWindow window;

    public:
        Jogo();
        ~Jogo();
        void executar();
        // ...
    };
}

