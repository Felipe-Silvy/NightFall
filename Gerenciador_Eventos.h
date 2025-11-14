#pragma once
#include "Gerenciador_Grafico.h"
#include "Jogador.h"

namespace NightFall
{
	namespace Gerenciadores
	{
		class Gerenciador_Eventos
		{
		private:
			Gerenciadores::Gerenciador_Grafico* pGrafico;
			Gerenciadores::Gerenciador_Colisoes* pColisao;
			Entidades::Personagens::Jogador* pJogador1;
			Entidades::Personagens::Jogador* pJogador2;

			static Gerenciador_Eventos* pEventos;
			Gerenciador_Eventos();
		public:
			~Gerenciador_Eventos();

			void setGerenciador_Grafico(Gerenciadores::Gerenciador_Grafico* pGraf);
			void setGerenciador_Colisoes(Gerenciadores::Gerenciador_Colisoes* pCol);
			//O IDEAL É TRANSFORMAR O GERENCIADOR GRAFICO EM SINGLETON
			//ENTAO ESSA  TORNA-SE DESNECESSARIA

			static Gerenciador_Eventos* getGerenciador_Eventos();
			void setjogador(Entidades::Personagens::Jogador* pJog);
			void resetJogadores();
			void verificaTeclaPressionada(sf::Keyboard::Key tecla);
			void executar();
			void verificaTeclasSeguradas();
		};
	}
}


