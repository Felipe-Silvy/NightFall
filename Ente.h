#pragma once
class Ente
{
protected:
    int id;
    //static Gerenciador_Grafico* pGG;
    //Figura* pFig;

public:
    // Construtor e destrutor
    Ente();
    virtual ~Ente();

    // Métodos virtuais
    virtual void executar() = 0; // método puramente virtual (classe abstrata)
    void desenhar();

    // Setter estático para o gerenciador gráfico
    //static void setGG(Gerenciador_Grafico* pG);
};

