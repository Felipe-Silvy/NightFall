#pragma once
#include "Personagem.h"

namespace NightFall {
    namespace Entidades {
        namespace Personagens {

            class Inimigo;

            class Jogador :
                public Personagem
            {
            protected:
                int pontos;
                int poderDano;
                // #...
            public:
                Jogador();
                ~Jogador();
                void colidir(Entidades::Personagens::Inimigo* pIn);
                void executar();
                void salvar();
                void mover(); 
                // ...

                //Fora da UML
                void pular();
                void atacar();
                int getDano();
               // void operator++();
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall

