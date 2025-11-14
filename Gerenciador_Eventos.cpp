#include "Gerenciador_Eventos.h"
#include "Gerenciador_Colisoes.h"
#include "Jogador.h"
#include "Inimigo.h"
#include <iostream>

NightFall::Gerenciadores::Gerenciador_Eventos* NightFall::Gerenciadores::Gerenciador_Eventos::pEventos = nullptr;

NightFall::Gerenciadores::Gerenciador_Eventos::Gerenciador_Eventos() :
	pGrafico(nullptr),
	pColisao(nullptr),
	pJogador1(nullptr),
	pJogador2(nullptr)
{}

NightFall::Gerenciadores::Gerenciador_Eventos::~Gerenciador_Eventos()
{
}

void NightFall::Gerenciadores::Gerenciador_Eventos::setGerenciador_Grafico(Gerenciadores::Gerenciador_Grafico* pGraf)
{
	if (pGraf != nullptr)
		pGrafico = pGraf;
}

void NightFall::Gerenciadores::Gerenciador_Eventos::setGerenciador_Colisoes(Gerenciadores::Gerenciador_Colisoes* pCol)
{
	if (pCol != nullptr)
		pColisao = pCol;
}

NightFall::Gerenciadores::Gerenciador_Eventos* NightFall::Gerenciadores::Gerenciador_Eventos::getGerenciador_Eventos()
{
	if (pEventos == nullptr)
	{
		pEventos = new Gerenciador_Eventos();
	}
	return pEventos;
}

void NightFall::Gerenciadores::Gerenciador_Eventos::setjogador(Entidades::Personagens::Jogador* pJog)
{
	if (pJogador1 == nullptr)
		pJogador1 = pJog;
	else if (pJogador2 == nullptr)
		pJogador2 = pJog;
	else
		std::cout << "Numero maximo de jogadores ja alocado" << std::endl;
}

void NightFall::Gerenciadores::Gerenciador_Eventos::resetJogadores()
{
	pJogador1 = nullptr;
	pJogador2 = nullptr;
}

void NightFall::Gerenciadores::Gerenciador_Eventos::verificaTeclaPressionada(sf::Keyboard::Key tecla)
{

	//estrutura de codigo parecida com o do ex-monitor Giovane Limas Salvi

	if (tecla == sf::Keyboard::Escape)
	{
		pGrafico->fecharJanela();
	}
	else if (pJogador1 != nullptr)
	{
		if (tecla == sf::Keyboard::A)
		{
			pJogador1->aplicarForca(sf::Vector2f(-2000.f, 0.f));
		}
		if (tecla == sf::Keyboard::D)
		{
			pJogador1->aplicarForca(sf::Vector2f(2000.f, 0.f));
		}
		if (tecla == sf::Keyboard::W)
		{
			pJogador1->pular();
		}
		if (tecla == sf::Keyboard::F)
		{
			std::vector<Entidades::Personagens::Inimigo*>* lista = pColisao->getListaInimigos();

			sf::Vector2f posJogador = pJogador1->getCorpo().getPosition();
			float alcanceAtaque = 100.f; // definir funcao

			for (int i = 0; i < lista->size(); i++)
			{
				Entidades::Personagens::Inimigo* inimigo = lista->at(i);
				if (inimigo == nullptr)
					continue;

				sf::Vector2f posInimigo = inimigo->getCorpo().getPosition();

				float distX = std::abs(posInimigo.x - posJogador.x);
				float distY = std::abs(posInimigo.y - posJogador.y);
				float distancia = std::sqrt(distX * distX + distY * distY);

				if (distancia <= alcanceAtaque)
				{
					std::cout << "Acertou ataque!!" << std::endl;
					// pJogador1->atacar();
					inimigo->receberDano(pJogador1->getDano());
					pJogador1->operator++();
				}
			}
		}
	}
	else if (pJogador2 != nullptr)
	{
		if (tecla == sf::Keyboard::Right)
		{
			pJogador2->aplicarForca(sf::Vector2f(-2000.f, 0.f));
		}
		if (tecla == sf::Keyboard::Left)
		{
			pJogador2->aplicarForca(sf::Vector2f(2000.f, 0.f));
		}
		if (tecla == sf::Keyboard::Up)
		{
			pJogador2->pular();
		}
		if (tecla == sf::Keyboard::Numpad0)
		{
			pJogador2->atacar();
		}
	}
}

void NightFall::Gerenciadores::Gerenciador_Eventos::executar()
{
	sf::Event evento;

	//trecho similar ao codigo do ex-monitor Giovane Limas Salvi

	while (pGrafico->getWindow()->pollEvent(evento))
	{
		if (evento.type == sf::Event::Closed)
		{
			pGrafico->fecharJanela();
		}
		else if (evento.type == sf::Event::KeyPressed)
		{
			verificaTeclaPressionada(evento.key.code);
		}
	}
	verificaTeclasSeguradas();
}

void NightFall::Gerenciadores::Gerenciador_Eventos::verificaTeclasSeguradas()
{
	if (pJogador1 != nullptr)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			pJogador1->aplicarForca(sf::Vector2f(-2000.f, 0.f));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			pJogador1->aplicarForca(sf::Vector2f(2000.f, 0.f));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			pJogador1->pular();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			pJogador1->atacar();
	}

	// mesmo para pJogador2 se quiser
}
