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
            public:
                Esqueleto();
                ~Esqueleto();
                void salvar();
                void executar();
                void danificar(Jogador* p);
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall



