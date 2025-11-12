#include "ListaEntidades.h"
#include "Entidade.h"
#include "Inimigo.h"
#include "Gerenciador_Colisoes.h"

NightFall::Listas::ListaEntidades::ListaEntidades() : pColisao(nullptr)
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

    auto* pElemento = LEs.getPrimeiro();

    while (pElemento != nullptr)
    {
        auto* pProximo = pElemento->getProximo();
        Entidades::Entidade* navegador = pElemento->getApontado();

        if (navegador == nullptr) {
            pElemento = pProximo; 
            continue;
        }

        Entidades::Personagens::Inimigo* pInimigo = dynamic_cast<Entidades::Personagens::Inimigo*>(navegador);

        bool foiRemovido = false;

        if (pInimigo != nullptr && pInimigo->getVida() <= 0)
        {

            if (pColisao != nullptr) {

                pColisao->removeInimigo(pInimigo);

            }

            LEs.removerElemento(navegador);

            foiRemovido = true;
        }

        if (!foiRemovido)
        {
            navegador->executar();
            navegador->desenhar();
        }

        pElemento = pProximo;
    }
}

void NightFall::Listas::ListaEntidades::setGerColisao(Gerenciadores::Gerenciador_Colisoes* pGC)
{
    if (pGC != nullptr)
        pColisao = pGC;
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
