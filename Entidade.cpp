#include "Entidade.h"

NightFall::Entidades::Entidade::Entidade() :
	Ente(), x(0) , y(0) , body(sf::Vector2f(100.f, 100.f))
{
	window = nullptr;
}

NightFall::Entidades::Entidade::~Entidade() {}

void NightFall::Entidades::Entidade::salvarDataBuffer()
{ 
	// Implementar depois
};

void NightFall::Entidades::Entidade::setWindow(sf::RenderWindow* w) { if (w != nullptr) { window = w; } }

void NightFall::Entidades::Entidade::draw()
{
	if ( window != nullptr) 
	{
		window->draw(body);
	}
}

sf::RectangleShape NightFall::Entidades::Entidade::getBody()
{
	return body;
}
