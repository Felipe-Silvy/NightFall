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
                float posicaoOriginalY;

                bool parede;
                bool movel;

            public:
                Plataforma();
                Plataforma(bool par, bool mov);
                ~Plataforma();
                void executar();
                void obstaculizar(Personagens::Jogador* p);
                void salvar();
                void setPosicaoOriginalY(float pos);
                static void resetPosicoes();
            };
        }
    }
}




