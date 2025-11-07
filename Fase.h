#pragma once
#include "Ente.h"
#include "Gerenciador_Colisoes.h"
#include "ListaEntidades.h"

namespace NightFall {
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
            Gerenciadores::Gerenciador_Grafico* pGG; // Adicionado
            Gerenciadores::Gerenciador_Eventos* pGE;
        public: 
            Fase();
            ~Fase();
            virtual void executar();
        protected:
            void criarMorcegos(); // Verificar tipo
            void criarPlataformas(); // Verificar tipo
            virtual void criarInimigos() = 0;
            virtual void criarObstaculo() = 0;
            void criarCenario();
            void setGerenciadorGrafico(Gerenciadores::Gerenciador_Grafico* pG);
            //FALTA COLOCAR ISSO EM ALGUM LUGAR
        };
    }
}


