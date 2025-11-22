#pragma once
#include "Obstaculo.h"

namespace NightFall
{
    namespace Entidades
    {
        namespace Obstaculos
        {
            class Cristal :
                public Obstaculo
            {
            private:
                short int danosidade;
                static std::vector<float> posicoesXCristal;

            public:
                Cristal();
                ~Cristal();
                void salvarDataBuffer();
                void executar();
                void obstaculizar(Personagens::Jogador* p);

                static void resetPosicoes();
                void salvar();
                void carregarCristal(int danosi);
            };
        }
    }
}


