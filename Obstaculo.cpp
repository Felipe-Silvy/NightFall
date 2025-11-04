#include "Obstaculo.h"


// Construtor com parametros
// Obstaculo::Obstaculo(int x, int y, bool dan) :
// Entidade(x, y), Chama o construtor de Entidade para x e y
// danoso(dan) Inicializa o atributo danoso
// {}

NightFall::Entidades::Obstaculos::Obstaculo::Obstaculo() : Entidade(), danoso(false)
{
}

NightFall::Entidades::Obstaculos::Obstaculo::~Obstaculo()
{
}

// Implementação do método salvarDataBuffer
// Este é um método concreto, então pode ter uma implementação padrão ou vazia.
void NightFall::Entidades::Obstaculos::Obstaculo::salvarDataBuffer()
{
}
