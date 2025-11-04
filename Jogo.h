#pragma once

#include <SFML/Graphics.hpp>
#include "Jogador.h"
#include "Gerenciador_Grafico.h"

namespace NightFall {
    class Jogo
    {
    private:
        NightFall::Entidades::Personagens::Jogador pJog1;
        NightFall::Gerenciadores::Gerenciador_Grafico GG;
        // ...
    public:
        Jogo();
        ~Jogo();
        void executar();
        // ...
    };
}

