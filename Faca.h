#pragma once
#include "Entidade.h"

namespace NightFall
{
	namespace Entidades
	{
		namespace Personagens
		{
			class Jogador;
		}

		class Faca : public Entidade
		{
		protected:
			bool ativo;
			unsigned int danoProjetil;
			// . . .

		public:
			Faca();
			~Faca();
			void executar();
			void salvar();
			void projDanificar(NightFall::Entidades::Personagens::Jogador* pJogador);
		};
	}
}

