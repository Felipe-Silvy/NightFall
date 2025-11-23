#include "FasePrimeira.h"
#include "Esqueleto.h"
#include "Teia.h"
#include "Plataforma.h"
#include "Gerenciador_Grafico.h"
#include "Gerenciador_Eventos.h"
#include <iostream>
#include "Jogo.h"
#include <fstream>


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
		alocadorTeia = new NightFall::Entidades::Obstaculos::Teia(false, 0.90f, 0.8f); // VALORES DE TESTE
		alocadorTeia->setTextura("Teia");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorTeia));
		GC.incluirObstaculo(alocadorTeia);
	}
}
	
void NightFall::Fases::FasePrimeira::criarInimigos()
{
	criarEsqueletos();
	criarMorcegos();
	
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
	id = 1; //ID DA CLASSE FASEPRIMEIRA EH 1
}

NightFall::Fases::FasePrimeira::~FasePrimeira()
{
}

NightFall::Entidades::Entidade* NightFall::Fases::FasePrimeira::instanciarEntidadeExclusiva(int id, std::ifstream& arq)
{
	//personagem
	int vidas = -1, velMax = -1;
	sf::Vector2f velAtual;
	int pulo = -1;
	bool chao = false;
	float tempoCor = 0.0f;

	//inimigo
	int direcao;
	float tempovagar;

	float larg = -1.f, desac = -1.f;
	int tam = -1, rigidez = -1;

	NightFall::Entidades::Obstaculos::Teia* alocadorTeia = nullptr;

	switch (id) {
	case 6: // TEIA
		std::cout << "Teia" << std::endl;

		arq >>  larg >> desac;
		alocadorTeia = new NightFall::Entidades::Obstaculos::Teia();
		alocadorTeia->carregarTeia(larg, desac);

		alocadorTeia->setTextura("Teia");
		return alocadorTeia;

	case 7: // ESQUELETO
		std::cout << "Esqueleto" << std::endl;
		arq >> direcao >> tempovagar >> tam >> rigidez;
		NightFall::Entidades::Personagens::Esqueleto* alocadorEsqueleto = new NightFall::Entidades::Personagens::Esqueleto();
		
		alocadorEsqueleto->carregarInimigo(direcao, tempovagar);		
		alocadorEsqueleto->carregarEsqueleto(tam, rigidez);

		alocadorEsqueleto->setTextura("Esqueleto");
		GC.incluirInimigo(alocadorEsqueleto);
		alocadorEsqueleto->resetarUltimaPosicao();

		return alocadorEsqueleto;
	}
	return nullptr; 
}


void NightFall::Fases::FasePrimeira::executar()
{
	NightFall::Fases::Fase::executar();
	

	if (pJog->getDoisJogadores() == false)
	{
		//trecho similar ao codigo do ex-monitor Giovane Limas Salvi

		std::cout << "Parou logo apos pJog1->getVida()" << std::endl;

		while (pGG->verificaAbertura() && 
			pJog1->getVida() > 0 && 
			(pJog1->getCorpo().getPosition().x < posFinal.x || 
			pJog1->getCorpo().getPosition().y < posFinal.y)) 
		{
			pGE->executar();
			if (pGE->getPause())
			{
				pJog->jogoPausar();
				pGE->setPause(false);
				lista_ents.resetarClocks();
			}
			pGG->limpaJanela();
			(this)->desenhar();
			pGG->getWindow()->draw(pontoFinal);
			lista_ents.percorrer();
			GC.executar();
			pGG->mostraElementos();
		}
		resetarFase();
		fase_ativa = false;
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
		while (pGG->verificaAbertura() && 
			pJog1->getVida() > 0 && 
			pJog2->getVida() > 0 && 
			((pJog1->getCorpo().getPosition().x < posFinal.x || 
			pJog1->getCorpo().getPosition().y < posFinal.y) || 
			(pJog2->getCorpo().getPosition().x < posFinal.x || 
			pJog1->getCorpo().getPosition().y < posFinal.y)))
		{
			pGE->executar();
			if (pGE->getPause())
			{
				pJog->jogoPausar();
				pGE->setPause(false);
				lista_ents.resetarClocks();
			}
			pGG->limpaJanela();
			(this)->desenhar();
			pGG->getWindow()->draw(pontoFinal);
			lista_ents.percorrer();
			GC.executar();
			pGG->mostraElementos();
		}
		resetarFase();
		fase_ativa = false;
		if (!(pJog1->getCorpo().getPosition().x < posFinal.x ||	//Testa se nao esta a esquerda da bandeira
			pJog1->getCorpo().getPosition().y < posFinal.y))	//ou se nao esta a cima dela,
		{														//para ser verdadeiro, ambos devem ser falsos
			pJog->iniciarFase2();
		}
		else
		{
			pJog1->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog1->getTamanho().y));
			pJog2->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog2->getTamanho().y));
		}
	}
	fase_ativa = false;
}

void NightFall::Fases::FasePrimeira::resetarFase()
{
	NightFall::Entidades::Obstaculos::Teia::resetPosicoes();
	numEsqueletos = maxEsqueletos - rand() % 4;
	numTeias = maxTeias - rand() % 4;
	Fase::resetarFase();
}
