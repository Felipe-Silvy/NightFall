#include "Menu.h"

NightFall::Menu::Menu()
{
	pJog = nullptr;
}

NightFall::Menu::~Menu()
{
}

void NightFall::Menu::executar () {}

void NightFall::Menu::setJogo(Jogo* pjogo)
{
	pJog = pjogo;
}
