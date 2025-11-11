#include "ListaEntidades.h"
#include "Entidade.h"
#include "Inimigo.h"
#include "Gerenciador_Colisoes.h"

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
    // Para iterar com segurança, precisamos de 'getPrimeiro()'
    auto* pElemento = LEs.getPrimeiro();

    while (pElemento != nullptr)
    {
        // --- ETAPA 1: Salvar o próximo ---
        // Salva o próximo nó ANTES de processar.
        // Isso é CRUCIAL, pois 'pElemento' pode ser deletado
        // e não poderíamos mais acessar 'pElemento->getProximo()'.
        auto* pProximo = pElemento->getProximo();

        // Pega o dado (a Entidade) de dentro do nó
        Entidades::Entidade* navegador = pElemento->getApontado();

        if (navegador == nullptr) {
            pElemento = pProximo; // Se o dado for nulo, apenas pule
            continue;
        }

        // --- ETAPA 2: Lógica de Morte e Remoção ---

        // Tenta converter para Inimigo
        Entidades::Personagens::Inimigo* pInimigo = dynamic_cast<Entidades::Personagens::Inimigo*>(navegador);

        bool foiRemovido = false;

        // Verifica se é um inimigo E se está morto
        if (pInimigo != nullptr && pInimigo->getVida() <= 0)
        {
            // Inimigo morto. Precisamos removê-lo.

            // 1. Remove da lista de Colisões (não-proprietária) PRIMEIRO.
            //    Temos que fazer isso ANTES que o ponteiro seja deletado.
            if (pColisao != nullptr) {

                pColisao->removeInimigo(pInimigo);

            }

            // 2. AGORA remove da lista principal (proprietária).
            //    Esta função 'removerElemento' (da sua classe Lista)
            //    DEVE deletar o ponteiro 'navegador'.
            LEs.removerElemento(navegador);

            foiRemovido = true;
        }

        // --- ETAPA 3: Executar e Desenhar ---
        // Só executa e desenha se a entidade NÃO foi removida.
        // Chamar executar() em um ponteiro deletado causaria um crash.
        if (!foiRemovido)
        {
            navegador->executar();
            navegador->desenhar();
        }

        // --- ETAPA 4: Avançar para o próximo nó ---
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
    // 1. Usa a nova função que acabamos de criar em Lista.h
    //    para pegar o primeiro NÓ.
    auto* pPrimeiroElemento = LEs.getPrimeiro();

    // 2. Verifica se a lista não está vazia
    if (pPrimeiroElemento != nullptr)
    {
        // 3. Retorna o DADO (a Entidade*) dentro do nó
        return pPrimeiroElemento->getApontado();
    }

    // 4. Se a lista estiver vazia, retorna nulo
    return nullptr;
}
