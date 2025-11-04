#pragma once
#include <vector>
#include <list>
#include <set>

class Inimigo;
class Obstaculo;
class Projetil;
class Jogador;
class Entidade;

class Gerenciador_Colisoes
{
private:
	std::vector<Inimigo*> LIs;
	std::list<Obstaculo*> LOs;
	std::set<Projetil*> LPs;
	Jogador* pJog1;
	// ...

public:
	const bool VerificarColisao(Entidade* pe1, Entidade* pe2) const;
	void tratarColisoesJogsObstacs();
	void tratarColisoesJogsInimigs();
	void tratarColisoesJogsProjeteis();
	void incluirInimigo(Inimigo* pi);
	void incluirObstaculo(Obstaculo* po);
	void incluirProjetil(Projetil* pj);
	void executar();
	//...
};

