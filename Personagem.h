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

                //Fora do UML
                
                sf::Vector2f velocidadeAtual;
				sf::Vector2f aceleracao;
				float forcaPulo;
				bool noChao;
				static const float FRICCAO;

				
                
            public:
                Personagem();
                ~Personagem();
                void salvarDataBuffer(); // Implementar depois
                virtual void executar() = 0;
                virtual void salvar() = 0;
                virtual void mover() = 0; 
                
                //Fora do UML
                void receberDano(unsigned int dano);
                void aplicarForca(sf::Vector2f forca);
                void setVelocidadeX(float vx);
                void setVelocidadeY(float vy);
                void setNoChao(bool valor);
                void setVelocidade(sf::Vector2f vel);
                const int getVida() const;
                void setVida(int vd);
                const sf::Vector2f getVelocidade() const;
                const bool getNoChao() const;
                void desenhar();
                //void knockback(float direcao);
            };
        }
    }
}


