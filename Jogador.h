#pragma once
#include "Personagem.h"
class Jogador :
    public Personagem
{
protected:
    int pontos;
    // #...
public:
    Jogador();
    ~Jogador();
   // void colidir(Inimigo* pIn);
    void executar();
    void salvar();
    void mover(int direc); // TEM QUE RETIRAR O PARAMETRO DPS
    void setTextura(sf::Texture* text);
    // ...
};
