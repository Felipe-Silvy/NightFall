#include "Gerenciador_Colisoes.h"
#include "Projetil.h"
#include "Inimigo.h"
#include "Jogador.h"
#include "Obstaculo.h"

NightFall::Gerenciadores::Gerenciador_Colisoes* NightFall::Gerenciadores::Gerenciador_Colisoes::pColisao = nullptr;

NightFall::Gerenciadores::Gerenciador_Colisoes::Gerenciador_Colisoes() :
	LIs(),
	LOs(),
	LPs(),
	pJog1(nullptr),
	pJog2(nullptr)
{
	LIs.clear();
	LOs.clear();
	LPs.clear();
}

NightFall::Gerenciadores::Gerenciador_Colisoes* NightFall::Gerenciadores::Gerenciador_Colisoes::getGerenciador_Colisoes()
{
	if (pColisao == nullptr)
	{
		pColisao = new Gerenciador_Colisoes();
	}
	return pColisao;
}

const bool NightFall::Gerenciadores::Gerenciador_Colisoes::VerificarColisao(Entidades::Entidade* pe1, Entidades::Entidade* pe2) const
{
	//para verificar a sobreposicao, deve-se encontrar a distancia entre os centros dos objetos, em x e y

	// calcula os centros (posicao + tamanho/2)
	sf::Vector2f centro1 = pe1->getPosicao() + (pe1->getTamanho() * 0.5f);
	sf::Vector2f centro2 = pe2->getPosicao() + (pe2->getTamanho() * 0.5f);

	sf::Vector2f sobreposicao;

	// distancia entre centros em x e y
	sobreposicao.x = fabs(centro1.x - centro2.x);
	// reduz pela metade das larguras somadas
	sobreposicao.x -= (pe1->getTamanho().x + pe2->getTamanho().x) * 0.5f;

	sobreposicao.y = fabs(centro1.y - centro2.y);
	sobreposicao.y -= (pe1->getTamanho().y + pe2->getTamanho().y) * 0.5f;

	if (sobreposicao.x < 0.0f && sobreposicao.y < 0.0f)
		return true;

	return false;
}

void NightFall::Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsObstacs()
{
	//LOs eh um list de Obstaculo*

	if (LOs.empty())
		return;

	int i = 0;

	Entidades::Entidade* obstaculosEntidade = nullptr;

	//ira se transformar no obstaculo em cada iteracao

	std::list<Entidades::Obstaculos::Obstaculo*>::iterator it;

	bool colisaoObstaculo = false;

	for (i = 0; i < LJs.size(); i++)
	{
		for (it = LOs.begin(); it != LOs.end(); it++)
		{
			obstaculosEntidade = static_cast<Entidades::Entidade*>(*it);
			colisaoObstaculo = VerificarColisao(LJs[i], obstaculosEntidade);

			//verifica a colisao de cada jogador com todos os objetos
			//nesse caso obstaculos

			if (colisaoObstaculo)
				(*it)->obstaculizar(static_cast<Entidades::Personagens::Jogador*>(LJs[i]));
			//ativa o metodo do obstaculo que ativa ao colidir
		}
	}
}

void NightFall::Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsInimigs()
{
	//LIs eh um vector de inimigo*

	if (LIs.empty())
		return;

	int i = 0;
	Entidades::Entidade* inimigosEntidade = nullptr;

	//inimigosEntidade vai assumir o valor de cada inimigo para comparar no
	//verificar colisao

	std::vector<Entidades::Personagens::Inimigo*>::iterator it;

	bool colisaoInimigos = false;

	for (i = 0; i < LJs.size(); i++)
	{
		for (it = LIs.begin(); it != LIs.end(); it++)
		{
			inimigosEntidade = static_cast<Entidades::Entidade*>(*it);
			colisaoInimigos = VerificarColisao(LJs[i], inimigosEntidade);
			//verifica a colisao de cada jogador com todos os objetos
			//nesse caso inimigos

			if (colisaoInimigos)
				(*it)->danificar(static_cast<Entidades::Personagens::Jogador*>(LJs[i]));
			//ativa o dano que o inimigo causa ao ser encostado
		}
	}
}

void NightFall::Gerenciadores::Gerenciador_Colisoes::tratarColisoesJogsProjeteis()
{
	//LPs eh um set de inimigo*

	if (LPs.empty())
		return;

	int i = 0;
	Entidades::Entidade* projeteisEntidade = nullptr;

	//inimigosEntidade vai assumir o valor de cada inimigo para comparar no
	//verificar colisao

	std::set<Entidades::Projetil*>::iterator it;

	bool colisaoProjeteis = false;

	for (i = 0; i < LJs.size(); i++)
	{
		for (it = LPs.begin(); it != LPs.end(); it++)
		{
			projeteisEntidade = static_cast<Entidades::Entidade*>(*it);
			colisaoProjeteis = VerificarColisao(LJs[i], projeteisEntidade);
			//verifica a colisao de cada jogador com todos os objetos
			//nesse caso objetos que sao projeteis

			if (colisaoProjeteis)
				(*it)->projDanificar(static_cast<Entidades::Personagens::Jogador*>(LJs[i]));
				//ativa o dano que o projetil causa ao ser encostado
		}
	}
}

void NightFall::Gerenciadores::Gerenciador_Colisoes::incluirInimigo(Entidades::Personagens::Inimigo* pi)
{
	if (pi)
		LIs.push_back(pi);
}

void NightFall::Gerenciadores::Gerenciador_Colisoes::incluirObstaculo(Entidades::Obstaculos::Obstaculo* po)
{
	if (po)
		LOs.push_back(po);
}

void NightFall::Gerenciadores::Gerenciador_Colisoes::incluirProjetil(Entidades::Projetil* pj)
{
	if (pj)
		LPs.insert(pj);
}

void NightFall::Gerenciadores::Gerenciador_Colisoes::executar()
{
	tratarColisoesJogsObstacs();
	tratarColisoesJogsInimigs();
	tratarColisoesJogsProjeteis();
}

void NightFall::Gerenciadores::Gerenciador_Colisoes::setJogador(Entidades::Personagens::Jogador* pJogador)
{
	if (pJogador == nullptr)
		return;

	if (pJog1 == nullptr)
	{
		pJog1 = pJogador;
		LJs.push_back(static_cast<Entidades::Entidade*>(pJog1));
	}
	else if (pJog2 == nullptr)
	{
		pJog2 = pJogador;
		LJs.push_back(static_cast<Entidades::Entidade*>(pJog2));
	}
	else
		std::cout << "Alem do limite de jogadores" << std::endl;

}
