#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Ente.h"

namespace NightFall {
    namespace Gerenciadores {

        // Foward Declaration
        class Gerenciador_Colisoes;

        class Gerenciador_Grafico {
        private:
            sf::RenderWindow window;
            std::map<std::string, sf::Texture> texturas;
            // outros atributos se necessário
            Gerenciador_Colisoes* pColisoes;

        public:
            // Construtor
            Gerenciador_Grafico();

            // Destrutor
            ~Gerenciador_Grafico();

            void executar();

            // Método para desenhar um ente
            void desenharEnte(Ente* e);

            // Gerenciando Texturas
            void carregarTextura(const std::string& id, const std::string& caminho);
            const sf::Texture& getTextura(const std::string& id) const;

            // Gerenciando a Window
            sf::RenderWindow* getWindow();
            void limpaJanela();
            void mostraElementos();
            void fecharJanela();
            bool verificaAbertura() const;
            
            // Conhecendo o Gerenciador de Colisões
            void setGerColisoes(Gerenciador_Colisoes* pC);
        };

    } // namespace Gerenciadores
} // namespace NightFall
