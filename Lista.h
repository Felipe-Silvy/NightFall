#pragma once

#include <cstddef> // nullptr

namespace NightFall
{
    namespace Listas
    {
        template<class TL>
        class Lista
        {
        public:
            // forward-declare a classe aninhada template
            template<class TE>
            class Elemento;

        private:
            Elemento<TL>* pPrimeiro;
            Elemento<TL>* pUltimo;

        public:
            // definição da classe aninhada
            template<class TE>
            class Elemento
            {
            private:
                Elemento<TE>* pProx;
                TE* pinfo;
            public:
                Elemento()
                    : pProx(nullptr)
                    , pinfo(nullptr)
                {
                }
                ~Elemento() {}

                void incluir(TE* p)
                {
                    pinfo = p;
                }

                void setProx(Elemento<TE>* pE)
                {
                    pProx = pE;
                }

                Elemento<TE>* getProximo() const
                {
                    return pProx;
                }

                TE* getApontado() const
                {
                    return pinfo;
                }
            };

            // Lista
            Lista()
                : pPrimeiro(nullptr)
                , pUltimo(nullptr)
            {
            }

            ~Lista()
            {
                limpar();
            }

            Elemento<TL>* getPrimeiro() const
            {
                return pPrimeiro;
            }

            void incluir(TL* p)
            {
                Elemento<TL>* elemento = new Elemento<TL>();
                elemento->incluir(p);

                if (pPrimeiro == nullptr) // lista vazia
                {
                    pPrimeiro = elemento;
                    pUltimo = elemento;
                }
                else
                {
                    pUltimo->setProx(elemento);
                    pUltimo = elemento;
                }
            }

            void limpar()
            {
                Elemento<TL>* atual = pPrimeiro;
                while (atual != nullptr)
                {
                    Elemento<TL>* proximo = atual->getProximo();
                    delete atual;
                    atual = proximo;
                }
                pPrimeiro = nullptr;
                pUltimo = nullptr;
            }

            void removerElemento(TL* removido)
            {
                if (pPrimeiro == nullptr)
                {
                    return;
                }

                Elemento<TL>* atual = pPrimeiro;
                Elemento<TL>* anterior = nullptr;

                while (atual != nullptr && atual->getApontado() != removido)
                {
                    anterior = atual;
                    atual = atual->getProximo();
                }

                if (atual == nullptr)
                    return;

                if (anterior == nullptr)
                {
                    // removendo o primeiro
                    pPrimeiro = atual->getProximo();
                }
                else
                {
                    anterior->setProx(atual->getProximo());
                }

                if (atual == pUltimo)
                    pUltimo = anterior;

                
                delete atual->getApontado(); // Deleta o dado (Entidade*)

                // Deleta o nó da lista
                delete atual;
            }

            const int getTam() const
            {
                int i = 0;
                Elemento<TL>* navegador = pPrimeiro;
                while (navegador != nullptr)
                {
                    ++i;
                    navegador = navegador->getProximo();
                }
                return i;
            }

            TL* operator[](int posicao)
            {
                Elemento<TL>* elemento = pPrimeiro;
                for (int i = 0; i < posicao && elemento != nullptr; ++i)
                    elemento = elemento->getProximo();

                if (elemento != nullptr)
                    return elemento->getApontado();
                return nullptr; 
            }
        };
    }
}
