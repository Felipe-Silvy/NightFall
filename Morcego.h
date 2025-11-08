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
                static sf::Vector2f ultimaPosicao;
            public:
                Morcego();
                ~Morcego();
                void salvar();
                void executar();
                void danificar(Jogador* p);
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall


