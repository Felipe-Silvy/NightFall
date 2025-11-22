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

                bool movel;

                float amplitudeMovimento;

            public:
                Plataforma();
                Plataforma(int est);
                ~Plataforma();
                void executar();
                void obstaculizar(Personagens::Jogador* p);

                void setPosicaoOriginalY(float pos);
                static void resetPosicoes();

                void salvar();
                void salvarDataBuffer();
                void carregarPlataforma(int alt, float origPosY, bool mobilidade, int amplitude);
            };
        }
    }
}




