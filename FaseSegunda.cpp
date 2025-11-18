#include "FaseSegunda.h"
// #include "Vampiro.h"
#include "Plataforma.h"
#include "Gerenciador_Grafico.h"
#include "Gerenciador_Eventos.h"
#include <iostream>
#include "Jogo.h"
#include "Inimigo.h"
#include "Cristal.h"


NightFall::Fases::FaseSegunda::FaseSegunda() : 
	Fase(), 
	maxVampiros(4), 
	numVampiros(maxVampiros - rand() % 2),
	maxCristais(6),
	numCristais(maxCristais - rand() % 4)
{
	numeroDaFase = 2;
}

NightFall::Fases::FaseSegunda::~FaseSegunda()
{
}

void NightFall::Fases::FaseSegunda::criarVampiros()
{
}

void NightFall::Fases::FaseSegunda::criarCristais()
{
	NightFall::Entidades::Obstaculos::Cristal* alocadorCristal = nullptr;
	int i;
	for (i = 0; i < numCristais; i++) {
		alocadorCristal = new NightFall::Entidades::Obstaculos::Cristal(); // VALORES DE TESTE
		alocadorCristal->setTextura("Cristal");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorCristal));
		alocadorCristal->setPosicao(alocadorCristal->getPosicao().x, pGG->getAlturaChao() - alocadorCristal->getTamanho().y);
		GC.incluirObstaculo(alocadorCristal);
	}
}

void NightFall::Fases::FaseSegunda::executar()
{
	NightFall::Fases::Fase::executar();
	pGG->setAlturaChao(600.0f);
	pJog1->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog1->getTamanho().y));
	criarInimigos();
	criarObstaculo();
	criarCenario();

	//trecho similar ao codigo do ex-monitor Giovane Limas Salvi

	while (pGG->verificaAbertura() && pJog1->getVida() > 0 && (pJog1->getCorpo().getPosition().x < posFinal.x || pJog1->getCorpo().getPosition().y < posFinal.y)) // && pos_jog != pos_final && jogador->getvidas()
	{
		//this para lembrar que é a fase se desenhando
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
	/* std::cout << "Jogador 1 fez " << pJog1->getPontos() << " pontos" << std::endl;
	if(pJog2)
		std::cout << "Jogador 2 fez " << pJog2->getPontos() << " pontos" << std::endl; */
}


void NightFall::Fases::FaseSegunda::resetarFase()
{
	NightFall::Entidades::Obstaculos::Cristal::resetPosicoes();
	//numEsqueletos = maxEsqueletos - rand() % 4;
	//numTeias = maxTeias - rand() % 4;
	Fase::resetarFase(); 
}

void NightFall::Fases::FaseSegunda::criarObstaculo()
{
	criarCristais();
	criarPlataformas();
}

void NightFall::Fases::FaseSegunda::criarInimigos()
{
	criarVampiros();
	criarMorcegos();
	NightFall::Entidades::Personagens::Inimigo::setJogador(pJog1);
}