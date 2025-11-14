#include "FasePrimeira.h"
#include "Esqueleto.h"
#include "Teia.h"
#include "Plataforma.h"
#include "Gerenciador_Grafico.h"
#include "Gerenciador_Eventos.h"
#include <iostream>

void NightFall::Fases::FasePrimeira::criarEsqueletos()
{
	NightFall::Entidades::Personagens::Esqueleto* alocadorEsqueleto = nullptr;
	int i;
	for (i = 0; i < numEsqueletos; i++) {
		alocadorEsqueleto = new NightFall::Entidades::Personagens::Esqueleto();
		alocadorEsqueleto->setTextura("Esqueleto");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorEsqueleto));
		std::cout << "Criou um Esqueleto" << std::endl;
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
	pGG->setAlturaChao(575.0f);
	pJog1->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog1->getTamanho().y) );
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

	/* std::cout << "Jogador 1 fez " << pJog1->getPontos() << " pontos" << std::endl;
	if(pJog2)
		std::cout << "Jogador 2 fez " << pJog2->getPontos() << " pontos" << std::endl; */

	if (pJog1->getVida() <= 0)
		pJog1->setVida(200);
	lista_ents.deletarElementos();
	GC.limparColecoes();
	NightFall::Entidades::Obstaculos::Plataforma::resetPosicoes();
	NightFall::Entidades::Obstaculos::Teia::resetPosicoes();
	numEsqueletos = maxEsqueletos - rand() % 4;
	numMorcegos = maxMorcegos - rand() % 8;
	numPlataformas = maxPlataformas - rand() % 4;
	numTeias = maxTeias - rand() % 4;
}