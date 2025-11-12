#pragma once
#include "Lista.h"

namespace NightFall
{
	namespace Gerenciadores {
		class Gerenciador_Colisoes;
	}

	namespace Entidades
	{
		class Entidade;
		namespace Personagens {
			class Jogador;
		}
	}

	namespace Listas
	{	
		class ListaEntidades
		{
		private:
			NightFall::Listas::Lista<NightFall::Entidades::Entidade> LEs;
			Gerenciadores::Gerenciador_Colisoes* pColisao;
			Entidades::Personagens::Jogador* pJog1;
			Entidades::Personagens::Jogador* pJog2;
		public:
			ListaEntidades();
			~ListaEntidades();
			void incluir(Entidades::Entidade* pE);
			void percorrer();
			NightFall::Entidades::Entidade* operator[](int indice);
			void setGerColisao(Gerenciadores::Gerenciador_Colisoes* pGC);
			NightFall::Entidades::Entidade* getPrimeiro() const;
		};
	}
}


