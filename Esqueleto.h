#pragma once
#include "Inimigo.h"

namespace NightFall {
    namespace Entidades {
        namespace Personagens {
            class Esqueleto :
                public Inimigo
            {
            private:
                int tamanho;
                static sf::Vector2f ultimaPosicao;
                int rigidez_ossea;
            public:
                Esqueleto();
                ~Esqueleto();
                void executar();
                void danificar(Jogador* p);
                void resetarUltimaPosicao();

                void receberDano(unsigned int dano);

                void salvarDataBuffer();
                void salvar();
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall



