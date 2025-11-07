#include "ListaEntidades.h"
#include"Entidade.h"

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
    int tamanho = LEs.getTam();
    NightFall::Entidades::Entidade* navegador = nullptr;

    for (int i = 0; i < tamanho; i++)
    {
        navegador = LEs[i];
        if (navegador != nullptr)
        {
            navegador->executar();
            navegador->desenhar();
        }
    }
}
