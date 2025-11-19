#pragma once
#include "Inimigo.h"

namespace NightFall {
    namespace Entidades {

        class Faca;

        namespace Personagens {
            class Vampiro :
                public Inimigo
            {
            private:
                short int forca;
                static sf::Vector2f ultimaPosicao;
                Entidades::Faca* pFaca;
            public:
                Vampiro();
                ~Vampiro();
                void salvar();
                void executar();
                void danificar(Jogador* p);
                void resetarUltimaPosicao();
                void setFaca(Faca* pFac);
                void ativarFaca();
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall
