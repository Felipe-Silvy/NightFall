#include "FasePrimeira.h"
#include "Esqueleto.h"
#include "Teia.h"
#include "Gerenciador_Grafico.h"

void NightFall::Fases::FasePrimeira::criarEsqueletos()
{
	NightFall::Entidades::Personagens::Esqueleto* alocadorEsqueleto = nullptr;
	int i;
	for (i = 0; i < numEsqueletos; i++) {
		alocadorEsqueleto = new NightFall::Entidades::Personagens::Esqueleto();
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorEsqueleto));	
		GC.incluirInimigo(alocadorEsqueleto);
	}
}

void NightFall::Fases::FasePrimeira::criarTeias()
{
	NightFall::Entidades::Obstaculos::Teia* alocadorTeia = nullptr;
	int i;
	for (i = 0; i < numTeias; i++) {
		alocadorTeia = new NightFall::Entidades::Obstaculos::Teia(false, 100.f, 100.f); // VALORES DE TESTE
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

NightFall::Fases::FasePrimeira::FasePrimeira() : maxEsqueletos(6) , maxTeias(6), numEsqueletos(maxEsqueletos - rand() % 4), numTeias(maxTeias - rand()%4)
{
}

NightFall::Fases::FasePrimeira::~FasePrimeira()
{
}

void NightFall::Fases::FasePrimeira::executar()
{
	criarInimigos();
	criarObstaculo();
	criarCenario();

	while (pGG->verificaAbertura())
	{
		//pEvento->executar();
		pGG->limpaJanela();
		lista_ents.percorrer();
		pGG->mostraElementos();
	}

	//caso singleton seja completamente implementado
	// 
	//trecho similar ao codigo do ex-monitor Giovane Limas Salvi
	/*while (pGrafico->verificaAbertura())
	{
		pEvento->executar();
		pGrafico->limpaJanela();
		listaEntidades.executar(pGrafico->getGerGrafico());
		pGrafico->mostraElementos();
	}*/
}