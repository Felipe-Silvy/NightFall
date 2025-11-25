#pragma once
#include "Entidade.h"

namespace NightFall {
    namespace Entidades {
        namespace Personagens {
            class Jogador; // Declaração forward para evitar inclusão circular
        }

        namespace Obstaculos {
            class Obstaculo : public Entidade
            {
            protected:
                bool danoso; 
                float cooldownInteracao;
                int estado;

            public:
                Obstaculo();
                
                virtual ~Obstaculo(); 
                virtual void executar() = 0; 
                virtual void salvar() = 0;   
                void salvarDataBuffer(); 
                void carregarObstaculo(int estado);

                // Método virtual puro (abstrato) específico de Obstaculo
                virtual void obstaculizar(Personagens::Jogador* p) = 0;
                const int getEstado() const;

                void gravitar();
            };
        }
    }
}

       

        

