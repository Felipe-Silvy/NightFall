#include "ListaEntidades.h"
#include "Entidade.h"
#include "Inimigo.h"
#include "Gerenciador_Colisoes.h"
#include "Jogador.h"


NightFall::Listas::ListaEntidades::ListaEntidades() :
    pColisao(nullptr),
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

void NightFall::Listas::ListaEntidades::deletarElementos()
{
    // Usamos 'removido' para saber se a lista foi alterada.
    // Se foi, reiniciamos a verificação do início.
    bool removido = true;
    while (removido)
    {
        removido = false;

        // Pega o primeiro nó da lista interna 
        // Usamos Elemento* para poder navegar (getProximo)

        auto* pAtualNode = LEs.getPrimeiro();

        while (pAtualNode != nullptr)
        {
            Entidades::Entidade* pEntidade = pAtualNode->getApontado();

            // Salva o ponteiro para o próximo nó ANTES de (potencialmente) deletar o nó atual
            auto* pProximoNode = pAtualNode->getProximo();

            // Verifica se é um jogador
            Entidades::Personagens::Jogador* pJog =
                dynamic_cast<Entidades::Personagens::Jogador*>(pEntidade);

            if (pJog != nullptr)
            {
                pAtualNode = pProximoNode;
            }
            else
            {
                LEs.removerElemento(pEntidade); // Isso vai deletar o nó E a entidade
                removido = true; // Sinaliza que a lista foi modificada

                // Quebra o loop 'while(pAtualNode != nullptr)'
                // O loop 'while(removido)' vai garantir que a verificação recomece
                break;
            }
        }
        // Se 'removido' for true, o loop 'while(removido)' repete,
        // pegando LEs.getPrimeiro() novamente.
        // Se for false (percorreu tudo e não removeu ninguém), o loop termina.
    }
}
