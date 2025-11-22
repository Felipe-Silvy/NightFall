#pragma once
#include "Entidade.h"

namespace NightFall
{
	namespace Entidades
	{
		namespace Personagens
		{
			class Jogador;
			class Vampiro;
		}

		class Faca : public Entidade
		{
		protected:
			bool ativo;
			unsigned int danoFaca;
			// . . .

			Entidades::Personagens::Vampiro* pVampiro;
			bool esquerda;

		public:
			Faca();
			~Faca();
			void executar();
			
			void projDanificar(NightFall::Entidades::Personagens::Jogador* pJogador);
			void setVampiro(Personagens::Vampiro* vamps);
			const bool getAtivo() const;
			void setAtivo(const bool novaAtividade);
			void setDirecao(bool esq);

			void salvar();
			void salvarDataBuffer();
			void carregarFaca(bool atividade, int dano, bool esq);
		};
	}
}

