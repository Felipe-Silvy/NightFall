#pragma once
#include "Entidade.h"

        class Jogador; // Declaração forward para evitar inclusão circular

        class Obstaculo : public Entidade 
        {
        protected:
            bool danoso; // Atributo protegido conforme o UML
            // ...

        public:
            Obstaculo();
           // Obstaculo(int x = 0, int y = 0, bool dan = false); Construtor, recebendo posição e se é danoso
            virtual ~Obstaculo(); // Destrutor virtual

            void salvarDataBuffer(); // Implementação específica de salvamento (se houver)

            // Métodos virtuais puros (abstratos) de Entidade, que Obstaculo também possui como abstratos
            virtual void executar() = 0; // Método virtual puro (abstrato)
            virtual void salvar() = 0;   // Método virtual puro (abstrato)

            // Método virtual puro (abstrato) específico de Obstaculo
            virtual void obstaculizar(Jogador* p) = 0;
        };  

