#include "ListaEntidades.h"
#include "Entidade.h"
#include "Inimigo.h"
#include "Gerenciador_Colisoes.h"

NightFall::Listas::ListaEntidades::ListaEntidades() :
    pColisao(nullptr),
    pJog1(nullptr),
    pJog2(nullptr),
    LEs()
{
}

NightFall::Listas::ListaEntidades::~ListaEntidades()
{
}

void NightFall::Listas::ListaEntidades::incluir(Entidades::Entidade* pE)
{
	if (pE != nullptr)
		LEs.incluir(pE);
}

void NightFall::Listas::ListaEntidades::percorrer()
{
    const int tam = LEs.getTam();

    for (int i = 0; i < tam; i++)
    {
        Entidades::Entidade* navegador = LEs[i];

        if (navegador == nullptr)
            continue;

        Entidades::Personagens::Inimigo* pInimigo =
            dynamic_cast<Entidades::Personagens::Inimigo*>(navegador);

        bool foiRemovido = false;

        if (pInimigo != nullptr && pInimigo->getVida() <= 0)
        {
            if (pColisao != nullptr)
                pColisao->removeInimigo(pInimigo);

            LEs.removerElemento(navegador);
            foiRemovido = true;
        }

        if (!foiRemovido)
        {
            navegador->executar();
            navegador->desenhar();
        }
    }
}




void NightFall::Listas::ListaEntidades::setGerColisao(Gerenciadores::Gerenciador_Colisoes* pGC)
{
    if (pGC != nullptr)
        pColisao = pGC;
}

NightFall::Entidades::Entidade* NightFall::Listas::ListaEntidades::operator[](int indice)
{
    return LEs.operator[](indice);
}

NightFall::Entidades::Entidade* NightFall::Listas::ListaEntidades::getPrimeiro() const
{
    auto* pPrimeiroElemento = LEs.getPrimeiro();

    if (pPrimeiroElemento != nullptr)
    {
        return pPrimeiroElemento->getApontado();
    }
    return nullptr;
}
