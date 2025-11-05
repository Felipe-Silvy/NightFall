#pragma once
#include <SFML/Graphics.hpp>

namespace NightFall {
    namespace Gerenciadores {
        class Gerenciador_Grafico;
    }

    class Ente {
    protected:
        int id;
        static Gerenciadores::Gerenciador_Grafico* pGG;
        sf::RectangleShape* corpo;

    public:
        // Construtor e destrutor
        Ente();
        virtual ~Ente();

        // Métodos virtuais
        virtual void executar() = 0; // método puramente virtual (classe abstrata)
        void desenhar();

        // Setter estático para o gerenciador gráfico
        static void setGG(Gerenciadores::Gerenciador_Grafico* pG);
    };
}
