#pragma once
#include "Ente.h"

namespace NightFall {
    class Jogo;

    class Menu :
        public Ente
    {
    private:
        Jogo* pJog;
        Gerenciadores::Gerenciador_Grafico* pGG;
        // ...

        // Tela Menu
        sf::Text tituloMenu;

        // Elementos para o botão da Fase 1
        sf::RectangleShape botaoFase1;
        sf::Text textoFase1;

        // Elementos para o botão da Fase 2
        sf::RectangleShape botaoFase2;
        sf::Text textoFase2;
    public:
        Menu();
        ~Menu();
        void executar();
        void setJogo(Jogo* pjogo);
        void setGerGrafico(Gerenciadores::Gerenciador_Grafico* pGer);
        // ...
    };
}

