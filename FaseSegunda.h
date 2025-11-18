#pragma once
#include "Fase.h"

namespace NightFall {
    namespace Fases {
        class FaseSegunda :
            public Fase
        {
        private:
           const int maxVampiros;
           int numVampiros;
           const int maxCristais;
           int numCristais;
        protected:
            void criarVampiros();
            void criarCristais();
            void criarInimigos();
            void criarObstaculo();
            void criarProjeteis();
        public:
            FaseSegunda();
            ~FaseSegunda();
            void executar();
            void resetarFase();
        };
    }
}

