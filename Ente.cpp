#include "Ente.h"

NightFall::Gerenciadores::Gerenciador_Grafico* NightFall::Ente::pGG = nullptr;

NightFall::Ente::Ente() : id(0) // , pFig(nullptr) 
{}

NightFall::Ente::~Ente() {}

void NightFall::Ente::desenhar() {
   // if (pFig != nullptr && pGG != nullptr)
      //  pGG->desenhar(pFig);
}

void NightFall::Ente::setGG(Gerenciadores::Gerenciador_Grafico* pG)
{
}

