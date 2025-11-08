#include "Fase.h"
#include "Morcego.h"

NightFall::Fases::Fase::Fase() : 
	lista_ents(), GC(), pGE(nullptr), 
	pGG(NightFall::Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico()),
	pJog1(nullptr), pJog2(nullptr),
	maxMorcegos(10), maxPlataformas(4), 
	numMorcegos(maxMorcegos - rand() % 8), numPlataformas(0)
{
}

NightFall::Fases::Fase::~Fase()
{
}

void NightFall::Fases::Fase::criarMorcegos()
{
	NightFall::Entidades::Personagens::Morcego* alocadorMorcego = nullptr;
	int i;
	for (i = 0; i < numMorcegos; i++) {
		alocadorMorcego = new NightFall::Entidades::Personagens::Morcego();
		alocadorMorcego->setTextura("Morcego");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorMorcego));
		GC.incluirInimigo(alocadorMorcego);
	}
}

void NightFall::Fases::Fase::criarPlataformas()
{
}

void NightFall::Fases::Fase::criarCenario()
{
}

void NightFall::Fases::Fase::setGerenciadorGrafico(Gerenciadores::Gerenciador_Grafico* pG)
{
	if (pG != nullptr)
		pGG = pG;
}

void NightFall::Fases::Fase::setJogador(Entidades::Personagens::Jogador* pJog)
{
	if (pJog != nullptr)
		if (pJog1 == nullptr)
			pJog1 = pJog;
		else
			pJog2 = pJog;
}

void NightFall::Fases::Fase::executar()
{
}