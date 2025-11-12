#pragma once
#include <vector>
#include <list>
#include <set>
#include <SFML/Graphics.hpp>
#include <iostream>

// Declarações (Forward declarations) das classes 

namespace NightFall {
    namespace Entidades {
        class Projetil;
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
            std::set<Entidades::Projetil*> LPs;
            Entidades::Personagens::Jogador* pJog1;
            Entidades::Personagens::Jogador* pJog2;
            std::vector<Entidades::Entidade*> LJs;
            // ...

            static Gerenciador_Colisoes* pColisao;
            //Gerenciador_Colisoes();

            Gerenciador_Grafico* pGrafico;

        public: 
            Gerenciador_Colisoes();
            ~Gerenciador_Colisoes();

            static Gerenciador_Colisoes* getGerenciador_Colisoes();

            const bool VerificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
            void tratarColisoesJogsObstacs();
            void tratarColisoesJogsInimigs();
            void tratarColisoesJogsProjeteis();
            void incluirInimigo(Entidades::Personagens::Inimigo* pi);
            void removeInimigo(Entidades::Personagens::Inimigo* pi);
            void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
            void incluirProjetil(Entidades::Projetil* pj);
            void executar();
            // ...

            void setJogador(Entidades::Personagens::Jogador* pJogador);
            std::vector<Entidades::Personagens::Inimigo*>* getListaInimigos();

            // Conhecendo Gerenciador Grafico
            void setGerGrafico(Gerenciador_Grafico* pG);
        };
    } // namespace Gerenciadores
} // namespace NightFall

