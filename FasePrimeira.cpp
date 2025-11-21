#include "FasePrimeira.h"
#include "Esqueleto.h"
#include "Teia.h"
#include "Plataforma.h"
#include "Gerenciador_Grafico.h"
#include "Gerenciador_Eventos.h"
#include <iostream>
#include "Jogo.h"


void NightFall::Fases::FasePrimeira::criarEsqueletos()
{
	NightFall::Entidades::Personagens::Esqueleto* alocadorEsqueleto = nullptr;
	int i;
	for (i = 0; i < numEsqueletos; i++) {
		alocadorEsqueleto = new NightFall::Entidades::Personagens::Esqueleto();
		alocadorEsqueleto->setTextura("Esqueleto");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorEsqueleto));
		//std::cout << "Criou um Esqueleto" << std::endl;
		GC.incluirInimigo(alocadorEsqueleto);
	}
	alocadorEsqueleto->resetarUltimaPosicao();
}

void NightFall::Fases::FasePrimeira::criarTeias()
{
	NightFall::Entidades::Obstaculos::Teia* alocadorTeia = nullptr;
	int i;
	for (i = 0; i < numTeias; i++) {
		alocadorTeia = new NightFall::Entidades::Obstaculos::Teia(false, 0.90, 0.8f); // VALORES DE TESTE
		alocadorTeia->setTextura("Teia");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorTeia));
		GC.incluirObstaculo(alocadorTeia);
	}
}
	
void NightFall::Fases::FasePrimeira::criarInimigos()
{
	criarEsqueletos();
	criarMorcegos();
	NightFall::Entidades::Personagens::Inimigo::setJogador(pJog1);
}

void NightFall::Fases::FasePrimeira::criarObstaculo()
{
	criarTeias();
	criarPlataformas();
}

NightFall::Fases::FasePrimeira::FasePrimeira() : 
	Fase(),
	maxEsqueletos(6),
	maxTeias(6),
	numEsqueletos(maxEsqueletos - rand() % 4),
	numTeias(maxTeias - rand() % 4)
{
	numeroDaFase = 1;
}

NightFall::Fases::FasePrimeira::~FasePrimeira()
{
}

void NightFall::Fases::FasePrimeira::executar()
{
	NightFall::Fases::Fase::executar();
	pGG->setAlturaChao(575.0f);
	pJog1->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog1->getTamanho().y) );
	if (pJog2 != nullptr && pJog->getDoisJogadores())
		pJog2->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog2->getTamanho().y));

	criarInimigos();
	criarObstaculo();
	criarCenario();

	//trecho similar ao codigo do ex-monitor Giovane Limas Salvi
	if (!(pJog->getDoisJogadores()))
	{
		while (pGG->verificaAbertura() && pJog1->getVida() > 0 && (pJog1->getCorpo().getPosition().x < posFinal.x || pJog1->getCorpo().getPosition().y < posFinal.y)) 
		{
			pGE->executar();
			pGG->limpaJanela();
			(this)->desenhar();
			pGG->getWindow()->draw(pontoFinal);
			lista_ents.percorrer();
			GC.executar();
			pGG->mostraElementos();
		}
		resetarFase();
		if (!(pJog1->getCorpo().getPosition().x < posFinal.x || pJog1->getCorpo().getPosition().y < posFinal.y))
		{
			pJog->iniciarFase2();
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
			pGE->executar();
			pGG->limpaJanela();
			(this)->desenhar();
			pGG->getWindow()->draw(pontoFinal);
			lista_ents.percorrer();
			GC.executar();
			pGG->mostraElementos();
		}
		resetarFase();
		if (!(pJog1->getCorpo().getPosition().x < posFinal.x || pJog1->getCorpo().getPosition().y < posFinal.y))
		{
			pJog->iniciarFase2();
		}
		else
		{
			pJog1->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog1->getTamanho().y));
			pJog2->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog2->getTamanho().y));
		}
	}
	
}

void NightFall::Fases::FasePrimeira::resetarFase()
{
	NightFall::Entidades::Obstaculos::Teia::resetPosicoes();
	numEsqueletos = maxEsqueletos - rand() % 4;
	numTeias = maxTeias - rand() % 4;
	Fase::resetarFase();
}
