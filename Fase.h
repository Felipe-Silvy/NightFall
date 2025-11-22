#pragma once
#include "Ente.h"
#include "Gerenciador_Colisoes.h"
#include "ListaEntidades.h"

namespace NightFall {
    // Foward Declarations

    class Jogo;
    namespace Entidades {
        namespace Personagens {
            class Jogador;
        }
    }
    namespace Gerenciadores
    {
        class Gerenciador_Eventos;
    }
    namespace Fases {
        class Fase :
            public Ente
        {
        protected:
            NightFall::Listas::ListaEntidades lista_ents; 
            Gerenciadores::Gerenciador_Colisoes GC;
            Gerenciadores::Gerenciador_Eventos* pGE;
            Entidades::Personagens::Jogador* pJog1;
            Entidades::Personagens::Jogador* pJog2;
            NightFall::Jogo* pJog;

            const int maxMorcegos;
            int numMorcegos;
            const int maxPlataformas;
            int numPlataformas;
            
            sf::Sprite pontoFinal;
            sf::Vector2f posFinal;

            bool fase_ativa;

        protected:
            void criarMorcegos(); // Verificar tipo
            void criarPlataformas(); // Verificar tipo
            virtual void criarInimigos() = 0;
            virtual void criarObstaculo() = 0;
            void criarCenario();

        public: 
            Fase();
            ~Fase();
            virtual void executar();
            void setJogador(Entidades::Personagens::Jogador* pJog);
            void setJogo(Jogo* pjogo);
            virtual void resetarFase();
            const bool getAtiva() const;
            void salvarFase();
        };
    }
}


