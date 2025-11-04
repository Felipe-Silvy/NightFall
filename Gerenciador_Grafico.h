#pragma once

#include <SFML/Graphics.hpp>
#include "Ente.h"

namespace NightFall {
    namespace Gerenciadores {

        class Gerenciador_Grafico {
        private:
            sf::RenderWindow window;
            // outros atributos se necessário

        public:
            // Construtor
            Gerenciador_Grafico();

            // Destrutor
            ~Gerenciador_Grafico();

            // Método para desenhar um ente
            void desenharEnte(Ente* e);
        };

    } // namespace Gerenciadores
} // namespace NightFall
