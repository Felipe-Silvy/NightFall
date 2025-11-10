#pragma once
#include "Obstaculo.h"

namespace NightFall {
    namespace Entidades {
        namespace Personagens {
            class Jogador; // Declaração forward para evitar inclusão circular
        }

        namespace Obstaculos {
            class Plataforma : public Obstaculo
            {
            private:
                int altura;
                // ...
                static std::vector<sf::Vector2f> posicoesParaPlataforma;

            public:
                Plataforma();
                ~Plataforma();
                void executar();
                void obstaculizar(Personagens::Jogador* p);
                void salvar();
            };
        }
    }
}




