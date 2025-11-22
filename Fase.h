#pragma once
#include "Ente.h"
#include "Gerenciador_Colisoes.h"
#include "ListaEntidades.h"

namespace NightFall {
    // Foward Declarations

    class Jogo;
    namespace Entidades {
        namespace Personagens {
            class Jogador;
        }
    }
    namespace Gerenciadores
    {
        class Gerenciador_Eventos;
    }
    namespace Fases {
        class Fase :
            public Ente
        {
        protected:
            NightFall::Listas::ListaEntidades lista_ents; 
            Gerenciadores::Gerenciador_Colisoes GC;
            Gerenciadores::Gerenciador_Eventos* pGE;
            Entidades::Personagens::Jogador* pJog1;
            Entidades::Personagens::Jogador* pJog2;
            NightFall::Jogo* pJog;

            const int maxMorcegos;
            int numMorcegos;
            const int maxPlataformas;
            int numPlataformas;
            
            sf::Sprite pontoFinal;
            sf::Vector2f posFinal;

            bool fase_ativa;

        protected:
            void criarMorcegos(); // Verificar tipo
            void criarPlataformas(); // Verificar tipo
            virtual void criarInimigos() = 0;
            virtual void criarObstaculo() = 0;
            void criarCenario();

        public: 
            Fase();
            ~Fase();
            void povoarFase(); //Prepara a fase antes de executar, desnecessario se for recuperar jogada
            virtual void executar();
            void setJogador(Entidades::Personagens::Jogador* pJog);
            void setJogo(Jogo* pjogo);
            virtual void resetarFase();
            const bool getAtiva() const;

            void salvarFase();
            void recuperarFase();

            virtual Entidades::Entidade* instanciarEntidadeExclusiva(int id, std::ifstream& arq) = 0;
            Entidades::Entidade* instanciarEntidadeGenerica(int id, std::ifstream& arq, bool* primeiroJogador, int esta);
        };
    }
}

/*
//carregar abstratos
void carregarObstaculo(int estado);
void carregarPersonagem(int vidasSalvas, int velMax, sf::Vector2f velAtual, int pulo, bool chao, float cortempo);
void carregarInimigo(int direcao, int vagar);

//carregar concretos
//ID 3
void carregarJogador(int pont, int poder);
//ID 4
void carregarPlataforma(int alt, float origPosY, bool mobilidade, int amplitude);
//ID 5
void carregarMorcego(float rai);
//ID 6
void carregarTeia(float larg, float desacel);
//ID 7
void carregarEsqueleto(int tam, int rigid);
//ID 8
void carregarCristal(int danosi);
//ID 9
void carregarVampiro(short int forca, bool atirou);
//ID 10
void carregarFaca(bool atividade, int dano, int esq);
*/

