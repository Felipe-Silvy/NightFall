#pragma once
#include <vector>
#include <list>
#include <set>

// Declarações (Forward declarations) das classes 

namespace NightFall {
    namespace Entidades {
        class Projetil;
        class Entidade;

        namespace Personagens {
            class Jogador;
            class Inimigo;
        }

        namespace Obstaculos {
            class Obstaculo;
        }
    }

    namespace Gerenciadores {
        class Gerenciador_Colisoes {
        private:
            std::vector<Entidades::Personagens::Inimigo*> LIs;
            std::list<Entidades::Obstaculos::Obstaculo*> LOs;
            std::set<Entidades::Projetil*> LPs;
            Entidades::Personagens::Jogador* pJog1;
            // ...

        public:
            const bool VerificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const;
            void tratarColisoesJogsObstacs();
            void tratarColisoesJogsInimigs();
            void tratarColisoesJogsProjeteis();
            void incluirInimigo(Entidades::Personagens::Inimigo* pi);
            void incluirObstaculo(Entidades::Obstaculos::Obstaculo* po);
            void incluirProjetil(Entidades::Projetil* pj);
            void executar();
            // ...
        };
    } // namespace Gerenciadores
} // namespace NightFall
