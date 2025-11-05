#include "ListaEntidades.h"

Nightfall::Listas::ListaEntidades::ListaEntidades()
{
}

Nightfall::Listas::ListaEntidades::~ListaEntidades()
{
}

void Nightfall::Listas::ListaEntidades::incluir(Entidades::Entidade* pE)
{
	if (pE != nullptr)
		LEs.incluir(pE);
	//inclui a entidade pE na Lista parametrizada com Entidade
}

void Nightfall::Listas::ListaEntidades::percorrer()
{
}
