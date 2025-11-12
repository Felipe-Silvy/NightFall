#include "Gerenciador_Grafico.h"

NightFall::Gerenciadores::Gerenciador_Grafico::Gerenciador_Grafico() :
    window(sf::VideoMode(1280, 720), "NightFall") ,
    alturaChao(600.0f)
{ // VERIFICAR INICIALIZÇÃO WINDOW
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

sf::Font* NightFall::Gerenciadores::Gerenciador_Grafico::getFonte()
{
    if (fonteCarregada)
        return &fontePrincipal;
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

void NightFall::Gerenciadores::Gerenciador_Grafico::setAlturaChao(const float alt)
{
    alturaChao = alt;
}

const float NightFall::Gerenciadores::Gerenciador_Grafico::getAlturaChao() const
{
    return alturaChao;
}

void NightFall::Gerenciadores::Gerenciador_Grafico::executar() {
    carregarTextura("Jogador", "Assets/Imagens/jogador1.png");
    carregarTextura("Esqueleto", "Assets/Imagens/esqueleto.png");
    carregarTextura("Morcego", "Assets/Imagens/morcego.png");
    carregarTextura("FundoMenu", "Assets/Imagens/fundomenu.png");
    carregarTextura("FundoFase1", "Assets/Imagens/fundofase1.png");
    carregarTextura("Plataforma", "Assets/Imagens/plataforma.png");
    carregarTextura("Parede", "Assets/Imagens/parede.png");
    carregarTextura("PontoFinal", "Assets/Imagens/pontoFinal.png");
    carregarTextura("Teia", "Assets/Imagens/teia.png");

    if (!fontePrincipal.loadFromFile("Assets/Fontes/minecraft.ttf"))
    {
        std::cout << "ERRO: Nao foi possivel carregar a fonte em: Assets/Fontes/minecraft.ttf" << std::endl;
        fonteCarregada = false;
        return;
    }
    std::cout << "Fonte principal carregada." << std::endl;
    fonteCarregada = true;
}