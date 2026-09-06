#pragma once

#include <SFML/Graphics.hpp>
#include "Jogador.h"
#include "Gerenciadores/Gerenciador_Grafico.h"
#include "Menu.h"
#include "Fases/FasePrimeira.h"
#include "Fases/FaseSegunda.h"

namespace NightFall {
    class Jogo
    {
    private:
        NightFall::Entidades::Personagens::Jogador pJog1;
        NightFall::Entidades::Personagens::Jogador pJog2;
        NightFall::Gerenciadores::Gerenciador_Grafico GG;
        NightFall::Menu MenuJogo;
        NightFall::Fases::FasePrimeira Fase1;
        NightFall::Fases::FaseSegunda Fase2;

        bool doisJogadores;

    public:
        Jogo();
        ~Jogo();
        void executar();
        void iniciarFase1();
        void iniciarFase2();
        void setDoisJogadores(bool boleano);
        const bool getDoisJogadores() const;
        void jogoPausar();
        void salvarJogo();
        void recuperarJogo();
        void mudarRanking(const std::vector<int>& pontos);
        void zerarJogador1();
    };
}

