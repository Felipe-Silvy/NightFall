#include "ListaEntidades.h"

NightFall::Listas::ListaEntidades::ListaEntidades()
{
}

NightFall::Listas::ListaEntidades::~ListaEntidades()
{
}

void NightFall::Listas::ListaEntidades::incluir(Entidades::Entidade* pE)
{
	if (pE != nullptr)
		LEs.incluir(pE);
	//inclui a entidade pE na Lista parametrizada com Entidade
}

void NightFall::Listas::ListaEntidades::percorrer()
{
	Entidades::Entidade* percorredorDeEntidades = nullptr;
	int i;
	// for(i = 0; i < )
}
