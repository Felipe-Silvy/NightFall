#include "Gerenciador_Grafico.h"

Gerenciador_Grafico::Gerenciador_Grafico() {
    // Inicialização do objeto gráfico
    // ...
    // inicialize outros atributos se necessário
}

Gerenciador_Grafico::~Gerenciador_Grafico() {
    // Liberar memória
}

void Gerenciador_Grafico::desenharEnte(Ente* e) {
    if (e == nullptr) return;

    // Aqui você chamaria métodos da BiblioGrafica para desenhar o ente
    // Exemplo genérico:
    // obj->desenhar(e->getFigura());

}