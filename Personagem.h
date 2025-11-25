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

                sf::Vector2f velocidadeAtual;
				sf::Vector2f aceleracao;
				float forcaPulo;
				bool noChao;
				static const float FRICCAO;

                float tempoMudancaCor;
                
            public:
                Personagem();
                ~Personagem();
                
                virtual void executar() = 0;
                
                virtual void mover() = 0; 

                virtual void salvar() = 0;
                void salvarDataBuffer();
                void carregarPersonagem(int vidasSalvas, int velMax, sf::Vector2f velAtual, int pulo, bool chao, float cortempo);

                virtual void receberDano(unsigned int dano);
                void aplicarForca(sf::Vector2f forca);
                void gravitar();

                void setVelocidade(sf::Vector2f vel);
                void setNoChao(bool valor);
                const int getVida() const;
                void setVida(int vd);
                const sf::Vector2f getVelocidade() const;
                const bool getNoChao() const;
                void desenhar();

                void retornarCorNormal();
            };
        }
    }
}


