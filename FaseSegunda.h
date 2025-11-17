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
           // const int maxTeias;
           // int numTeias;
        protected:
            void criarVampiros();
            // void criarObstaculosDificeis();
            void criarInimigos();
            void criarObstaculo();
        public:
            FaseSegunda();
            ~FaseSegunda();
            void executar();
            void resetarFase();
        };
    }
}

