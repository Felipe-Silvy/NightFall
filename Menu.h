#pragma once
#include "Ente.h"
#include <functional>

namespace NightFall {
    class Jogo;

    class Menu :
        public Ente
    {
    private:
        Jogo* pJog;

        // Título Principal
        sf::Text tituloMenu;

        // Elementos para o botão 1
        sf::RectangleShape botao1;
        sf::Text textoBotao1;

        // Elementos para o botão 2
        sf::RectangleShape botao2;
        sf::Text textoBotao2;

        bool sairDoLoop;

    public:
        Menu();
        ~Menu();
        void executar();
        void executarTelaPause();
        void setJogo(Jogo* pjogo);
        void escolheAcao();
        void escolheJogo();
        void escolheJogadores();
        void escolheFase();
        void escolhePause();
        void atualizarRanking(const std::vector<int>& pontos);
        std::string capturarNomeSFML(int numJog);
        void mostrarRanking();
        void continuarJogo();
        void loopComAcoes(std::function<void()> acaoBotao1,std::function<void()> acaoBotao2);
        void centralizarTextos();
    };
}

