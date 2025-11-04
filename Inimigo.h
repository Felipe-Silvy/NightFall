#pragma once
#include "Personagem.h" 

namespace NightFall {
    namespace Entidades {
        namespace Personagens {
            class Jogador;

            class Inimigo :
                public Personagem
            {
            protected:
                int nivel_maldade;
                Jogador* pJogador;
                // ...
            public:
                Inimigo();
                ~Inimigo();
                // void salvaDataBuffer();
                virtual void executar() = 0;
                virtual void danificar(Jogador* p) = 0;
                virtual void salva() = 0;
                // ...
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall
