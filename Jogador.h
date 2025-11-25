#pragma once
#include "Personagem.h"

namespace NightFall {
    namespace Entidades {
        namespace Personagens {

            class Inimigo;

            class Jogador :
                public Personagem
            {
            private:
                int pontos;
                int poderDano;

            public:
                Jogador();
                ~Jogador();
                void colidir(Entidades::Personagens::Inimigo* pIn);
                void executar();

                void salvarDataBuffer();
                void salvar();
                void carregarJogador(int pont, int poder);

                void mover(); 
    
                void pular();
                void atacar(std::vector<Inimigo*>* lista);
                int getDano();
                void operator++();
                const int getPontos() const;
                void setPontos(int pts);
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall

