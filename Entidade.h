#pragma once
#include "Ente.h"

#include <SFML/Graphics.hpp>

namespace NightFall {
	namespace Entidades {
		class Entidade : public Ente
		{
		protected:
			int x;
			int y;
			// ostream "buffer" tirar aspas depois;
			void salvarDataBuffer(); // Impementar depois
		public:
			Entidade();
			~Entidade();
			virtual void executar() = 0;
			virtual void salvar() = 0;
		};
	}
}
