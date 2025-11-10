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
        sf::Sprite corpo;
    private:
        static int cont_id;
    public:
        // Construtor e destrutor
        Ente();
        // Ente(int uid, )
        virtual ~Ente();

        // Métodos virtuais
        virtual void executar() = 0; // método puramente virtual (classe abstrata)
        void desenhar();

        // Setter estático para o gerenciador gráfico
        static void setGG(Gerenciadores::Gerenciador_Grafico* pG);
        const sf::Sprite& getCorpo() const;
        void setTextura(const std::string& id);

        const sf::Vector2f getTamanho() const;
        const sf::Vector2f getPosicao() const;
    
        void setTamanho(float x, float y);
        void setPosicao(float x, float y);
        void setPosicao(sf::Vector2f pos);
        void moverCorpo(sf::Vector2f deslocamento);
    };
}
