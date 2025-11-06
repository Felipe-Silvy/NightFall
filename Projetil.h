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

		class Projetil : public Entidade
		{
		protected:
			bool ativo;
			unsigned int danoProjetil;
			// . . .

		public:
			Projetil();
			~Projetil();
			void executar();
			void salvar();
			void projDanificar(NightFall::Entidades::Personagens::Jogador* pJogador);
		};
	}
}