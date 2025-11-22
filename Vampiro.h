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
                bool jaAtirou;
                float quandoAtirar;
                static sf::Vector2f ultimaPosicao;
                Entidades::Faca* pFaca;
            public:
                Vampiro();
                ~Vampiro();
                void executar();
                void danificar(Jogador* p);
                void resetarUltimaPosicao();
                void setFaca(Faca* pFac);
                void ativarFaca();

                void salvarDataBuffer();
                void salvar();
                void carregarVampiro(short int forcaSalva, bool atirou);
            };
        } // namespace Personagens
    } // namespace Entidades
} // namespace NightFall
