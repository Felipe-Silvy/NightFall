#pragma once

#include <SFML/Graphics.hpp>
#include "Ente.h"

class Gerenciador_Grafico {
private:
    sf::RenderWindow window;
    // outros atributos se necessário

public:
    // Construtor
    Gerenciador_Grafico();

    // Destrutor
    ~Gerenciador_Grafico();

    // Método para desenhar um ente
    void desenharEnte(Ente* e);
};

