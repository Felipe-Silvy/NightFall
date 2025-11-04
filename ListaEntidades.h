#pragma once
#include "Lista.h"

namespace Nightfall
{
	namespace Entidades
	{
		class Entidade;
	}

	namespace Listas
	{	
		class ListaEntidades
		{
		private:
			NightFall::Listas::Lista<Nightfall::Entidades::Entidade> LEs;
		public:
			ListaEntidades();
			~ListaEntidades();
			void incluir(Entidades::Entidade* pE);
			void percorrer();

		};
	}
}


