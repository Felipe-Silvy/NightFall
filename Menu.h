#pragma once
#include "Ente.h"

namespace NightFall {
    class Jogo;

    class Menu :
        public Ente
    {
    private:
        Jogo* pJog;
        // ...
    public:
        Menu();
        ~Menu();
        void executar();
        void setJogo(Jogo* pjogo);
        // ...
    };
}

