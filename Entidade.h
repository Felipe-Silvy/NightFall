#pragma once
#include "Ente.h"

#include <SFML/Graphics.hpp>

class Entidade : public Ente
{
protected:
	int x;
	int y;
	sf::RectangleShape body;
	sf::Texture texturaEsquerda;
	sf::Texture texturaDireita;
	sf::RenderWindow* window;
	// ostream "buffer" tirar aspas depois;
	void salvarDataBuffer(); // Impementar depois
public:
	Entidade();
	~Entidade();
	virtual void executar() = 0;
	virtual void salvar () = 0;
	void setWindow(sf::RenderWindow* w);
	void draw();
	sf::RectangleShape getBody();
};

