#pragma once
#include "Fase.h"

namespace NightFall {
    namespace Fases {
        class FasePrimeira :
            public Fase
        {
        private:
            const int maxEsqueletos;
            int numEsqueletos;
            const int maxTeias;
            int numTeias;
        protected:
            void criarEsqueletos();
            void criarTeias();
            void criarInimigos();
            void criarObstaculo();
        public:
            FasePrimeira();
            ~FasePrimeira();
            void executar();
            void resetarFase();
        };
    }
}


