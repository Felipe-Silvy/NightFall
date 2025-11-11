#include "Fase.h"
#include "Morcego.h"
#include "Gerenciador_Eventos.h"
#include "Plataforma.h"

NightFall::Fases::Fase::Fase() :
	lista_ents(), GC(),
	pGG(NightFall::Gerenciadores::Gerenciador_Grafico::getGerenciador_Grafico()),
	pGE(NightFall::Gerenciadores::Gerenciador_Eventos::getGerenciador_Eventos()),
	pJog1(nullptr), pJog2(nullptr),
	maxMorcegos(10), maxPlataformas(6),
	numMorcegos(maxMorcegos - rand() % 8), numPlataformas(maxPlataformas - rand() % 4),
	numeroDaFase(0),
	pontoFinal(),
	posFinal(),
	hitboxPosFinal(10)
{
	pontoFinal.setTexture(pGG->getTextura("PontoFinal"));
	pontoFinal.setScale(0.1f, 0.1f);

	// Obter tamanho da textura para posicionar corretamente
	sf::Vector2u tamanhoTextura = pGG->getTextura("PontoFinal").getSize();
	sf::Vector2f tamanhoEscalado(
		tamanhoTextura.x * pontoFinal.getScale().x,
		tamanhoTextura.y * pontoFinal.getScale().y
	);

	// Define posição no canto inferior direito da tela (VideoMode 1280x720)
	posFinal.x = 1280.0f - tamanhoEscalado.x;
	posFinal.y = 600.0f - tamanhoEscalado.y;

	pontoFinal.setPosition(posFinal);
}

NightFall::Fases::Fase::~Fase()
{
}

void NightFall::Fases::Fase::criarMorcegos()
{
	NightFall::Entidades::Personagens::Morcego* alocadorMorcego = nullptr;
	int i;
	for (i = 0; i < numMorcegos; i++) {
		alocadorMorcego = new NightFall::Entidades::Personagens::Morcego();
		alocadorMorcego->setTextura("Morcego");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorMorcego));
		GC.incluirInimigo(alocadorMorcego);
	}
}

void NightFall::Fases::Fase::criarPlataformas()
{	
	NightFall::Entidades::Obstaculos::Plataforma* alocadorPlataforma = nullptr;
	
	alocadorPlataforma = new NightFall::Entidades::Obstaculos::Plataforma(true);
	lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorPlataforma));
	GC.incluirObstaculo(alocadorPlataforma);

	int i;
	for (i = 0; i < numPlataformas; i++) {
		alocadorPlataforma = new NightFall::Entidades::Obstaculos::Plataforma();
		alocadorPlataforma->setTextura("Plataforma");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorPlataforma));
		GC.incluirObstaculo(alocadorPlataforma);
	}
}

void NightFall::Fases::Fase::criarCenario()
{
	sf::Vector2f tamJanela = static_cast<sf::Vector2f>(pGG->getWindow()->getSize());
	if (numeroDaFase == 1)
	{
		// Centralizando e escalando Imagem de Fundo 
		setTextura("FundoFase1");
        const sf::Texture* pTextura = corpo.getTexture();
        // Verificação de segurança (impede crash)
        if (pTextura == nullptr) {
            std::cout << "ERRO: Sprite 'corpo' (Menu) sem textura!" << std::endl;
            return;
        }
        sf::Vector2f tamTextura = static_cast<sf::Vector2f>(pTextura->getSize());
        // Calcula e aplica a escala
        corpo.setScale(tamJanela.x / tamTextura.x, tamJanela.y / tamTextura.y);
        // Opcional: Alinha o fundo no canto
        corpo.setPosition(0.f, 0.f);
	}
}

void NightFall::Fases::Fase::setGerenciadorGrafico(Gerenciadores::Gerenciador_Grafico* pG)
{
	if (pG != nullptr)
		pGG = pG;
}

void NightFall::Fases::Fase::setJogador(Entidades::Personagens::Jogador* pJog)
{
	if (pJog != nullptr) {
		if (pJog1 == nullptr)
			pJog1 = pJog;
		else
			pJog2 = pJog;

		pGE->setjogador(pJog);
		lista_ents.incluir(pJog);
		GC.setJogador(pJog);
	}
}

void NightFall::Fases::Fase::executar()
{
}