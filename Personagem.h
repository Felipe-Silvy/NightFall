#pragma once
#include "Entidade.h"

namespace NightFall {
    namespace Entidades {
        namespace Personagens {
            class Personagem :
                public Entidade
            {
            protected:
                int num_vidas;
                float velocidade;
            public:
                Personagem();
                ~Personagem();
                void salvarDataBuffer(); // Implementar depois
                virtual void executar() = 0;
                virtual void salvar() = 0;
                virtual void mover() = 0; 
                void setVelocidade(float vel);

                //Fora do UML
                void receberDano(unsigned int dano);
            };
        }
    }
}


