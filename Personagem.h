#pragma once
#include "Entidade.h"
class Personagem :
    public Entidade
{
protected:
    int num_vidas;
    float velocidade;
public:
    Personagem();
    ~Personagem();
    void salvarDataBuffer(); // Implementar depois
    virtual void executar() = 0;
    virtual void salvar() = 0;
    virtual void mover(int direc) = 0; // TEM QUE RETIRAR O PARAMETRO DPS
    void setVelocidade(float vel);
};

