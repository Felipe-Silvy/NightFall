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
                bool danoso; // Atributo protegido conforme o UML
                float cooldownInteracao;
                int estado;
                // ...

            public:
                Obstaculo();
                // Obstaculo(int x = 0, int y = 0, bool dan = false); Construtor, recebendo posição e se é danoso
                virtual ~Obstaculo(); // Destrutor virtual

                

                // Métodos virtuais puros (abstratos) de Entidade, que Obstaculo também possui como abstratos
                virtual void executar() = 0; // Método virtual puro (abstrato)
                
                virtual void salvar() = 0;   // Método virtual puro (abstrato)
                void salvarDataBuffer(); // Implementação específica de salvamento (se houver)
                void carregarObstaculo(int estado);

                // Método virtual puro (abstrato) específico de Obstaculo
                virtual void obstaculizar(Personagens::Jogador* p) = 0;
                
                const int getEstado() const;

                //static virtual void resetPosicoes() = 0;
            };
        }
    }
}

       

        

