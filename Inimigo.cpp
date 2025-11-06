#include "Inimigo.h"

NightFall::Entidades::Personagens::Inimigo::Inimigo() : Personagem(), nivel_maldade(0)
{
}

NightFall::Entidades::Personagens::Inimigo::~Inimigo()
{
	nivel_maldade = 0;
}

void NightFall::Entidades::Personagens::Inimigo::mover()
{
}