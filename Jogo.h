#pragma once

#include <SFML/Graphics.hpp>
#include "Jogador.h"
#include "Gerenciador_Grafico.h"
#include "Menu.h"
#include "FasePrimeira.h"
#include "FaseSegunda.h"

namespace NightFall {
    class Jogo
    {
    private:
        NightFall::Entidades::Personagens::Jogador pJog1;
        NightFall::Gerenciadores::Gerenciador_Grafico GG;
        NightFall::Menu MenuJogo;
        NightFall::Fases::FasePrimeira Fase1;
        // ...
        NightFall::Fases::FaseSegunda Fase2;
    public:
        Jogo();
        ~Jogo();
        void executar();
        void iniciarFase1();
        void iniciarFase2();
        // ...
    };
}

