#pragma once
#include "Lista.h"

namespace NightFall
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
			NightFall::Listas::Lista<NightFall::Entidades::Entidade> LEs;
		public:
			ListaEntidades();
			~ListaEntidades();
			void incluir(Entidades::Entidade* pE);
			void percorrer();
		};
	}
}


