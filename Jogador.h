#pragma once
#include "Personagem.h"

namespace NightFall {
    namespace Entidades {
        namespace Personagens {
            class Jogador :
                public Personagem
            {
            protected:
                int pontos;
                // #...
            public:
                Jogador();
                ~Jogador();
                // void colidir(Inimigo* pIn);
                void executar();
                void salvar();
                void mover(); 
                // ...
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall

