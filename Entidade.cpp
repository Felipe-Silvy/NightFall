#include "Entidade.h"

Entidade::Entidade() :
	Ente(), x(0) , y(0) , body(sf::Vector2f(100.f, 100.f))
{
	window = nullptr;
}

Entidade::~Entidade() {}

void Entidade::salvarDataBuffer() 
{ 
	// Implementar depois
};

void Entidade::setWindow(sf::RenderWindow* w) { if (w != nullptr) { window = w; } }

void Entidade::draw() 
{
	if ( window != nullptr) 
	{
		window->draw(body);
	}
}

sf::RectangleShape Entidade::getBody()
{
	return body;
}
