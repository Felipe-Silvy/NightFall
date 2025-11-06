#include "Fase.h"

NightFall::Fases::Fase::Fase() : lista_ents(), GC(), pGG(nullptr)
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
	pGG = pG;
}

void NightFall::Fases::Fase::executar()
{
}