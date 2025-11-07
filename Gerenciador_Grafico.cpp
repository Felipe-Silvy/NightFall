#include "Gerenciador_Grafico.h"

NightFall::Gerenciadores::Gerenciador_Grafico::Gerenciador_Grafico() : window(sf::VideoMode(1280, 720), "NightFall") { // VERIFICAR INICIALIZÇÃO WINDOW
    executar();
}

NightFall::Gerenciadores::Gerenciador_Grafico::~Gerenciador_Grafico() {
    // Liberar memória
}

void NightFall::Gerenciadores::Gerenciador_Grafico::desenharEnte(Ente* e) {
    if (e != nullptr)
        window.draw(e->getCorpo());
}

void NightFall::Gerenciadores::Gerenciador_Grafico::carregarTextura(const std::string& id, const std::string& caminho)
{
    try {
        sf::Texture textura;
        if (!textura.loadFromFile(caminho)) {
            throw std::runtime_error("Falha ao carregar o arquivo: " + caminho);
        }

        // Move a textura carregada para o mapa
        texturas[id] = std::move(textura);
        std::cout << "Textura carregada com sucesso: " << id << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao carregar textura [" << id << "]: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Erro desconhecido ao carregar textura [" << id << "]." << std::endl;
    }
}

const sf::Texture& NightFall::Gerenciadores::Gerenciador_Grafico::getTextura(const std::string& id) const
{
    auto it = texturas.find(id);
    if (it != texturas.end()) {
        return it->second;
    }

    std::cerr << "Textura nao encontrada: " << id << std::endl;
    // Cuidado: precisamos retornar alguma coisa
    // Retorna uma textura vazia 
    static sf::Texture texturaVazia;
    return texturaVazia;
}

sf::RenderWindow* NightFall::Gerenciadores::Gerenciador_Grafico::getWindow()
{
    return &window;
}

void NightFall::Gerenciadores::Gerenciador_Grafico::limpaJanela()
{
    window.clear();
}

void NightFall::Gerenciadores::Gerenciador_Grafico::mostraElementos()
{
    window.display();
}

void NightFall::Gerenciadores::Gerenciador_Grafico::fecharJanela()
{
    window.close();
}

bool NightFall::Gerenciadores::Gerenciador_Grafico::verificaAbertura() const
{
    return window.isOpen();
}

void NightFall::Gerenciadores::Gerenciador_Grafico::setGerColisoes(Gerenciador_Colisoes* pC)
{
    if (pC != nullptr)
        pColisoes = pC;
}

NightFall::Gerenciadores::Gerenciador_Grafico* NightFall::Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico()
{
    return (this);
    //Idealmente é alterado para se adequar ao singleton
}

void NightFall::Gerenciadores::Gerenciador_Grafico::executar() {
    carregarTextura("Jogador", "Assets/Imagens/jogador2.png");
    carregarTextura("Esqueleto", "Assets/Imagens/esqueleto.png");
}