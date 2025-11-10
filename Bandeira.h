#pragma once
#include "Obstaculo.h"

namespace NightFall
{
    namespace Entidades
    {
        namespace Obstaculos
        {
            class Bandeira : public Obstaculo
            {
            private:
                bool chegouFinal;
            public:
                Bandeira();
                ~Bandeira();
                const bool getChegouFinal() const;
                void executar();
                void obstaculizar(Personagens::Jogador* p);
                void salvar();
            };
        }
    }
}


