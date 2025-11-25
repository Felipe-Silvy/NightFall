#pragma once
#include "Ente.h"

#include <SFML/Graphics.hpp>
#include <sstream>

namespace NightFall {
	namespace Entidades {
		class Entidade : public Ente
		{
		protected:
			std::ostream buffer;
			std::stringbuf bufferInterno;

			float deltaTempo;
			sf::Clock relogioMovimento;
			float cooldownDano;

			void salvarDataBuffer(); 
		public:
			Entidade();
			~Entidade();
			virtual void executar() = 0;
			virtual void salvar() = 0;
			const bool podeDanificar();
			void relogioMovimentoResetar();
			const std::string getBufferString() const;

			virtual void gravitar() = 0;
		};
	}
}
