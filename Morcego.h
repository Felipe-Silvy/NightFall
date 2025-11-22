#pragma once
#include "Inimigo.h"

namespace NightFall {
    namespace Entidades {
        namespace Personagens {
            class Morcego :
                public Inimigo
            {
            private:
                float raio;
                float voo;
                static sf::Vector2f ultimaPosicao;
            public:
                Morcego();
                ~Morcego();
                void executar();
                void danificar(Jogador* p);
                void mover();
                void resetarUltimaPosicao();

                void salvarDataBuffer();
                void salvar();
                void carregarMorcego(float rai);
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall


