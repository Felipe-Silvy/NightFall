#pragma once
#include "Ente.h"
#include "Gerenciador_Colisoes.h"
#include "ListaEntidades.h"

namespace NightFall {

    // Foward Declarations
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
            Gerenciadores::Gerenciador_Grafico* pGG; 
            Gerenciadores::Gerenciador_Eventos* pGE;
            Entidades::Personagens::Jogador* pJog1;
            Entidades::Personagens::Jogador* pJog2;
            
        public: 
            Fase();
            ~Fase();
            virtual void executar();
            void setGerenciadorGrafico(Gerenciadores::Gerenciador_Grafico* pG);
            void setJogador(Entidades::Personagens::Jogador* pJog);
        protected:
            void criarMorcegos(); // Verificar tipo
            void criarPlataformas(); // Verificar tipo
            virtual void criarInimigos() = 0;
            virtual void criarObstaculo() = 0;
            void criarCenario();
            //FALTA COLOCAR ISSO EM ALGUM LUGAR
        };
    }
}


