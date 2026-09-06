#include "FaseSegunda.h"
#include "../Vampiro.h"
#include "../Plataforma.h"
#include "../Gerenciadores/Gerenciador_Grafico.h"
#include "../Gerenciadores/Gerenciador_Eventos.h"
#include <iostream>
#include "../Jogo.h"
#include "../Inimigo.h"
#include "../Cristal.h"
#include "../Faca.h"

#include <fstream>


NightFall::Fases::FaseSegunda::FaseSegunda() : 
	Fase(), 
	maxVampiros(4), 
	numVampiros(maxVampiros - rand() % 2),
	maxCristais(6),
	numCristais(maxCristais - rand() % 4)
{
	id = 2; //ID DA CLASSE FASESEGUNDA EH 2
}

NightFall::Fases::FaseSegunda::~FaseSegunda()
{
}

void NightFall::Fases::FaseSegunda::criarVampiros()
{
	NightFall::Entidades::Personagens::Vampiro* alocadorVampiro = nullptr;
	std::set<NightFall::Entidades::Faca*>* Lista_projeteis = GC.getListaProjeteis();

	std::set<NightFall::Entidades::Faca*>::iterator itFaca = Lista_projeteis->begin();

	int i;
	for (i = 0; i < numVampiros; i++) {
		alocadorVampiro = new NightFall::Entidades::Personagens::Vampiro();
		alocadorVampiro->setTextura("Vampiro");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorVampiro));
		//std::cout << "Criou um Vampiro" << std::endl;
		GC.incluirInimigo(alocadorVampiro);

		alocadorVampiro->setFaca((*itFaca));
		itFaca++;
	}
	alocadorVampiro->resetarUltimaPosicao();
}

void NightFall::Fases::FaseSegunda::criarProjeteis()
{
	NightFall::Entidades::Faca* alocadorFaca = nullptr;
	int i;
	for (i = 0; i < numVampiros; i++) {
		alocadorFaca = new NightFall::Entidades::Faca();
		alocadorFaca->setTextura("Faca");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorFaca));
		//std::cout << "Criou um Faca" << std::endl;
		GC.incluirProjetil(alocadorFaca);
	}
}

void NightFall::Fases::FaseSegunda::criarCristais()
{
	NightFall::Entidades::Obstaculos::Cristal* alocadorCristal = nullptr;
	int i;
	for (i = 0; i < numCristais; i++) {
		alocadorCristal = new NightFall::Entidades::Obstaculos::Cristal(); // VALORES DE TESTE
		alocadorCristal->setTextura("Cristal");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorCristal));
		//alocadorCristal->setPosicao(alocadorCristal->getPosicao().x, pGG->getAlturaChao() - alocadorCristal->getTamanho().y);
		GC.incluirObstaculo(alocadorCristal);
	}
}


void NightFall::Fases::FaseSegunda::executar()
{
	NightFall::Fases::Fase::executar();
		//precisa ser antes para o funcionamento dos cristais

	//trecho similar ao codigo do ex-monitor Giovane Limas Salvi

	if (!(pJog->getDoisJogadores()))
	{
		while (pGG->verificaAbertura() && pJog1->getVida() > 0 && (pJog1->getCorpo().getPosition().x < posFinal.x || pJog1->getCorpo().getPosition().y < posFinal.y)) // && pos_jog != pos_final && jogador->getvidas()
		{
			fluir();
		}
		resetarFase();
		if (!(pJog1->getCorpo().getPosition().x < posFinal.x 
			|| pJog1->getCorpo().getPosition().y < posFinal.y))
		{
			std::vector<int> valores;
			valores.push_back(pJog1->getPontos());
			pJog->mudarRanking(valores);

			pJog1->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog1->getTamanho().y));
		}
		else
		{
			pJog1->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog1->getTamanho().y));
		}
	}
	else
	{
		while (pGG->verificaAbertura() && pJog1->getVida() > 0 && pJog2->getVida() > 0 && ((pJog1->getCorpo().getPosition().x < posFinal.x || pJog1->getCorpo().getPosition().y < posFinal.y) || (pJog2->getCorpo().getPosition().x < posFinal.x || pJog1->getCorpo().getPosition().y < posFinal.y)))
		{
			fluir();
		}
		resetarFase();
		if (!(pJog1->getCorpo().getPosition().x < posFinal.x 
			|| pJog1->getCorpo().getPosition().y < posFinal.y))
		{
			std::vector<int> valores;
			valores.push_back(pJog1->getPontos());
			valores.push_back(pJog2->getPontos());
			pJog->mudarRanking(valores);

			pJog1->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog1->getTamanho().y));
			pJog2->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog2->getTamanho().y));
		}
		else
		{
			pJog1->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog1->getTamanho().y));
			pJog2->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog2->getTamanho().y));
		}
	}
}


void NightFall::Fases::FaseSegunda::resetarFase()
{
	NightFall::Entidades::Obstaculos::Cristal::resetPosicoes();
	numVampiros = maxVampiros - rand() % 2;
	numCristais = maxCristais - rand() % 4;
	Fase::resetarFase(); 
}

void NightFall::Fases::FaseSegunda::criarObstaculo()
{
	criarCristais();
	criarPlataformas();
}


void NightFall::Fases::FaseSegunda::criarInimigos()
{
	criarProjeteis();
	criarVampiros();
	criarMorcegos();
}

NightFall::Entidades::Entidade* NightFall::Fases::FaseSegunda::instanciarEntidadeExclusiva(int id, std::ifstream& arq)
{
	NightFall::Entidades::Obstaculos::Cristal* alocadorCristal = nullptr;
	NightFall::Entidades::Personagens::Vampiro* alocadorVampiro = nullptr;
	NightFall::Entidades::Faca* alocadorFaca = nullptr;

	//personagem
	int vidas = -1, velMax = -1;
	sf::Vector2f velAtual;
	int pulo = -1;
	bool chao = false;
	float tempoCor = 0.0f;

	//inimigo
	int direcao;
	float tempovagar;

	//ListaDeFacas para refazer a relacao entre as facas e os vampiros
	std::set<NightFall::Entidades::Faca*>* Lista_projeteis = GC.getListaProjeteis();
	std::set<NightFall::Entidades::Faca*>::iterator itFaca = Lista_projeteis->begin();

	switch (id) {
	case 8: // Cristal
		short int dan;
		arq  >> dan;
		alocadorCristal = new NightFall::Entidades::Obstaculos::Cristal();
		alocadorCristal->carregarCristal(dan);
		alocadorCristal->setTextura("Cristal");
		return alocadorCristal;

	case 9: // Vampiro
		int forca, atirou, indVampFaca;
		arq >> direcao >> tempovagar >> forca >> atirou >> indVampFaca;
		alocadorVampiro = new NightFall::Entidades::Personagens::Vampiro();

		alocadorVampiro->carregarInimigo(direcao, tempovagar);
		alocadorVampiro->carregarVampiro(forca, atirou, indVampFaca);

		alocadorVampiro->setTextura("Vampiro");
		GC.incluirInimigo(alocadorVampiro);
		alocadorVampiro->resetarUltimaPosicao();

		while (itFaca != Lista_projeteis->end())
		{
			if ((*itFaca)->getIndiceFaca() == indVampFaca)
			{
				alocadorVampiro->setFaca((*itFaca));
				std::cout << "Faca foi reassociada!" << std::endl;
			}
				
			itFaca++;
		}

		return alocadorVampiro;

	case 10: // Faca
		bool ativ; 
		int dano; 
		bool esq;
		int indFacaVamp;
		arq >> ativ >> dano >> esq >> indFacaVamp;
		alocadorFaca = new NightFall::Entidades::Faca();
		alocadorFaca->carregarFaca(ativ, dano, esq, indFacaVamp);
		alocadorFaca->setTextura("Faca");
		GC.incluirProjetil(alocadorFaca);

		return alocadorFaca;
	}
	return nullptr;
}