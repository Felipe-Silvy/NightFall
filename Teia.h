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

            public:
                Teia();
                Teia(const bool danosidade, const float desacel, const float larg);
                ~Teia();
                void executar();
                void obstaculizar(Personagens::Jogador* p);
                void salvar();
            };
        }
    }
}


