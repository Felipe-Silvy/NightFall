#include "Fase.h"

NightFall::Fases::Fase::Fase() : lista_ents(), GC(), pGE(nullptr), pGG(nullptr), pJog1(nullptr), pJog2(nullptr)
{
}

NightFall::Fases::Fase::~Fase()
{
}

void NightFall::Fases::Fase::criarMorcegos()
{
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