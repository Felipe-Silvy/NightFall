#include "Teia.h"


NightFall::Entidades::Obstaculos::Teia::Teia() : Obstaculo(), largura(-1), desaceleracao(-1)
{
}

NightFall::Entidades::Obstaculos::Teia::Teia(const bool danosidade, const float desacel, const float larg) : Obstaculo()
{
	danoso = danosidade;
	desaceleracao = desacel;
	largura = larg;
}

NightFall::Entidades::Obstaculos::Teia::~Teia()
{
}

void NightFall::Entidades::Obstaculos::Teia::executar()
{
}

void NightFall::Entidades::Obstaculos::Teia::obstaculizar(Personagens::Jogador* p)
{

}

void NightFall::Entidades::Obstaculos::Teia::salvar()
{

}
