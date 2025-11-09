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
                static Jogador* pJogador1;
                static Jogador* pJogador2;

                const float alcancePerseguir;
                int direcaoAleatoria;
                float tempoVagar;

                // ...
            public:
                Inimigo();
                ~Inimigo();
                // void salvaDataBuffer();
                virtual void executar() = 0;
                virtual void danificar(Jogador* p) = 0;
                virtual void salvar() = 0; // Perguntar se é Salva ou Salvar
                // ...
                virtual void mover();
                virtual void perseguir(sf::Vector2f posJogador, sf::Vector2f posInimigo);
                virtual void vagar();
                static void setJogador(Jogador* pJogad);
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall
