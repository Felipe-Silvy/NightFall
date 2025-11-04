#include "Gerenciador_Grafico.h"

NightFall::Gerenciadores::Gerenciador_Grafico::Gerenciador_Grafico() {
    // Inicialização do objeto gráfico
    // ...
    // inicialize outros atributos se necessário
}

NightFall::Gerenciadores::Gerenciador_Grafico::~Gerenciador_Grafico() {
    // Liberar memória
}

void NightFall::Gerenciadores::Gerenciador_Grafico::desenharEnte(Ente* e) {
    if (e == nullptr) return;

    // Aqui você chamaria métodos da BiblioGrafica para desenhar o ente
    // Exemplo genérico:
    // obj->desenhar(e->getFigura());
}
