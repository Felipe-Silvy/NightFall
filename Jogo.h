#pragma once

#include <SFML/Graphics.hpp>
#include "Jogador.h"
#include "Gerenciador_Grafico.h"
#include "Menu.h"
#include "FasePrimeira.h"

namespace NightFall {
    class Jogo
    {
    private:
        NightFall::Entidades::Personagens::Jogador pJog1;
        NightFall::Gerenciadores::Gerenciador_Grafico GG;
        NightFall::Menu MenuJogo;
        NightFall::Fases::FasePrimeira Fase1;
        // ...
    public:
        Jogo();
        ~Jogo();
        void executar();
        void iniciarFase1(bool jogou);
        void iniciarFase2(bool jogou);
        // ...
    };
}

