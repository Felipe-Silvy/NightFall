#pragma once
#include "Inimigo.h"

namespace NightFall {
    namespace Entidades {
        namespace Personagens {
            class Vampiro :
                public Inimigo
            {
            private:
                short int forca;
                static sf::Vector2f ultimaPosicao;
            public:
                Vampiro();
                ~Vampiro();
                void salvar();
                void executar();
                void danificar(Jogador* p);
                void resetarUltimaPosicao();
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall
