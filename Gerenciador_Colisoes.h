#pragma once
#include <vector>
#include <list>
#include <set>
#include <SFML/Graphics.hpp>
#include <iostream>

// Declarações (Forward declarations) das classes 

namespace NightFall {
    namespace Entidades {
        class Faca;
        class Entidade;

        namespace Personagens {
            class Jogador;
            class Inimigo;
        }

        namespace Obstaculos {
            class Obstaculo;
        }
    }

    namespace Gerenciadores {

        class Gerenciador_Grafico;

        class Gerenciador_Colisoes {
        private:
            std::vector<Entidades::Personagens::Inimigo*> LIs;
            std::list<Entidades::Obstaculos::Obstaculo*> LOs;
            std::set<Entidades::Faca*> LPs;
            std::vector<Entidades::Personagens::Jogador*> LJs;

            Gerenciador_Grafico* pGrafico;

            const bool VerificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
            void tratarColisoesJogsObstacs();
            void tratarColisoesJogsInimigs();
            void tratarColisoesJogsProjeteis();

        public:
            Gerenciador_Colisoes();
            ~Gerenciador_Colisoes();

            void incluirInimigo(Entidades::Personagens::Inimigo* pi);
            void removeInimigo(Entidades::Personagens::Inimigo* pi);
            void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
            void incluirProjetil(Entidades::Faca* pj);
            void executar();
            void setJogador(Entidades::Personagens::Jogador* pJogador);
            std::vector<Entidades::Personagens::Inimigo*>* getListaInimigos();
            std::set<Entidades::Faca*>* getListaProjeteis();

            // Conhecendo o Gerenciador Grafico
            void setGerGrafico(Gerenciador_Grafico* pG);
            void limparColecoes();
        };
    } // namespace Gerenciadores
} // namespace NightFall