#pragma once
#include "Obstaculo.h"
namespace NightFall
{
    namespace Entidades
    {
        namespace Personagens
        {
            class Jogador;
        }
        namespace Obstaculos
        {
            class Teia :
                public Obstaculo
            {
            private:
                float largura;
                float desaceleracao;
                static std::vector<float> posicoesXTeia;

            public:
                Teia();
                Teia(const bool danosidade, const float desacel, const float larg);
                ~Teia();
                void executar();
                void obstaculizar(Personagens::Jogador* p);
                static void resetPosicoes();

                void salvarDataBuffer();
                void salvar();
                void carregarTeia(float larg, float desacel);
            };
        }
    }
}


