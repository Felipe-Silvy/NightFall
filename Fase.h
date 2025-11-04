#pragma once
#include "Ente.h"
#include "Gerenciador_Colisoes.h"

namespace NightFall {
    namespace Fases {
        class Fase :
            public Ente
        {
        protected:
            // ListaEntidades lista_ents;
            Gerenciadores::Gerenciador_Colisoes GG;
        public: 
            Fase();
            ~Fase();
            virtual void executar();
        protected:
            void criarInimFaceis(); // Verificar tipo
            void criarPlataformas(); // Verificar tipo
            virtual void criarInimigos() = 0;
            virtual void criarObstaculo() = 0;
            void criarCenario();
        };
    }
}


