#pragma once
#include "Ente.h"

#include <SFML/Graphics.hpp>

namespace NightFall {
	namespace Entidades {
		class Entidade : public Ente
		{
		protected:
			void salvarDataBuffer(); // Impementar depois

			float deltaTempo;
			sf::Clock relogioMovimento;
		public:
			Entidade();
			~Entidade();
			virtual void executar() = 0;
			virtual void salvar() = 0;
		};
	}
}
