#include "Fase.h"
#include "Morcego.h"
#include "Gerenciadores/Gerenciador_Eventos.h"
#include "Plataforma.h"
#include "Jogo.h"
#include <fstream>

NightFall::Fases::Fase::Fase() :
	lista_ents(), GC(),
	pGE(NightFall::Gerenciadores::Gerenciador_Eventos::getGerenciador_Eventos()),
	pJog1(nullptr), pJog2(nullptr),
	maxMorcegos(10), maxPlataformas(5),
	numMorcegos(maxMorcegos - rand() % 8), numPlataformas(maxPlataformas - rand() % 4),
	pontoFinal(),
	posFinal(),
	pJog(nullptr),
	fase_ativa(false)
{
	lista_ents.setGerColisao(&GC);
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

	alocadorMorcego->resetarUltimaPosicao();
}

void NightFall::Fases::Fase::criarPlataformas()
{	
	NightFall::Entidades::Obstaculos::Plataforma* alocadorPlataforma = nullptr;

	int i;
	for (i = 0; i < numPlataformas; i++) {
		alocadorPlataforma = new NightFall::Entidades::Obstaculos::Plataforma();
		if (i < 1)
		{
			alocadorPlataforma->setPosicao(450.0f, 400.0f);
			alocadorPlataforma->setPosicaoOriginalY(400.0f);
			std::cout << "Alterado para x = " << alocadorPlataforma->getPosicao().x << " y =" << alocadorPlataforma->getPosicao().y << std::endl;
		}
		alocadorPlataforma->setTextura("Plataforma");
		lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorPlataforma));
		GC.incluirObstaculo(alocadorPlataforma);
	}
}

void NightFall::Fases::Fase::criarCenario()
{
	sf::Vector2f tamJanela = static_cast<sf::Vector2f>(pGG->getWindow()->getSize());
	if (id == 1)
	{
		setTextura("FundoFase1");
		pGG->setAlturaChao(575.0f);
	}
	else if(id == 2)
	{
		setTextura("FundoFase2");
		pGG->setAlturaChao(600.0f);
	}

    const sf::Texture* pTextura = corpo.getTexture();

    if (pTextura == nullptr)
	{
		std::cout << "erro - textura da fase nao alocada" << std::endl;
        return;
    }
    sf::Vector2f tamTextura = static_cast<sf::Vector2f>(pTextura->getSize());

	//Adequa o tamanho da janela
    corpo.setScale(tamJanela.x / tamTextura.x, tamJanela.y / tamTextura.y);

    corpo.setPosition(0.f, 0.f);

	//Parede

	NightFall::Entidades::Obstaculos::Plataforma* alocadorPlataforma = nullptr;

	alocadorPlataforma = new NightFall::Entidades::Obstaculos::Plataforma(2);
	lista_ents.incluir(static_cast<NightFall::Entidades::Entidade*>(alocadorPlataforma));
	GC.incluirObstaculo(alocadorPlataforma);
}

// Reinicia estado da fase: reseta vida/pontos dos jogadores, limpa entidades e atualiza contadores de spawns.
void NightFall::Fases::Fase::resetarFase()
{
	std::cout << "Resetou" << std::endl;
	if (pJog1->getVida() <= 0)
	{
		pJog1->setVida(200);
		pJog1->setPontos(0);
	}
		

	if (pJog2 != nullptr && pJog->getDoisJogadores() && pJog2->getVida() <= 0)
	{
		pJog2->setVida(200);
		pJog2->setPontos(0);
	}

	lista_ents.deletarElementos();
	GC.limparColecoes();
	NightFall::Entidades::Obstaculos::Plataforma::resetPosicoes();
	pGE->resetJogadores();
	
	numMorcegos = maxMorcegos - rand() % 8;
	numPlataformas = maxPlataformas - rand() % 4;
	fase_ativa = false;
}

const bool NightFall::Fases::Fase::getAtiva() const
{
	return fase_ativa;
}

void NightFall::Fases::Fase::salvarFase()
{
	lista_ents.salvarEntidades(id, pJog->getDoisJogadores() );
}

// Carrega fase a partir do arquivo salvo, recria entidades e restaura seus estados.
void NightFall::Fases::Fase::recuperarFase()
{
	std::ifstream recuperadorEntidades("Salvamentos/Save.txt");

	if (!recuperadorEntidades.is_open())
	{
		std::cout << "Arquivo nao abriu" << std::endl;
	}

	criarCenario();

	//Apenas esvaziando essa parte do arquivo que nao sera usada agora
	int idFase;
	bool doisJogadores;
	recuperadorEntidades >> idFase >> doisJogadores;
	
	//Parte de codigo inspirada no codigo do professor Jeans Simão
	//E no codigo do ex-monitor Giovane Limas Salvi

	bool primeiroJogador = true;	//para so ter como acessar o jogador 1 uma vez

	//entidade e ente
	int idEntidade = -1;
	sf::Vector2f escala, posicao;

	//personagem
	int vidas = -1, velMax = -1;
	sf::Vector2f velAtual;
	int pulo = -1;
	bool chao = false;
	float tempoCor = 0.0f;

	//obstaculo
	int esta = -1;

	while ( recuperadorEntidades >> idEntidade >>
			escala.x >> escala.y >>
			posicao.x >> posicao.y )
	{
		std::cout << "Lendo ID = " << idEntidade << std::endl;

		if (!recuperadorEntidades.good())
			std::cout << "STREAM CORROMPIDO" << std::endl;

		Entidades::Entidade* novaEntidade = nullptr;

		if (idEntidade % 2 == 1)	//PERSONAGEM = resto 1
		{
			recuperadorEntidades >> vidas >> velMax >>
				velAtual.x >> velAtual.y >>
				pulo >> chao >> tempoCor;
			
			novaEntidade = instanciarEntidadeExclusiva(idEntidade, recuperadorEntidades);
			
			if (novaEntidade == nullptr)
				novaEntidade = instanciarEntidadeGenerica(idEntidade, recuperadorEntidades, &primeiroJogador, esta);

			Entidades::Personagens::Personagem* novoPersonagem = dynamic_cast<Entidades::Personagens::Personagem*>(novaEntidade);
			if (novoPersonagem)
				novoPersonagem->carregarPersonagem(vidas, velMax, velAtual, pulo, chao, tempoCor);

			std::cout << "Instanciou um personagem" << std::endl;
		}
		else if (idEntidade % 2 == 0 && idEntidade != 10) //OBSTACULO = resto 0 e id != 10
		{
			recuperadorEntidades >> esta;

			novaEntidade = instanciarEntidadeExclusiva(idEntidade, recuperadorEntidades);
			
			if (novaEntidade == nullptr)
				novaEntidade = instanciarEntidadeGenerica(idEntidade, recuperadorEntidades, &primeiroJogador, esta);

			Entidades::Obstaculos::Obstaculo* novoObstaculo = dynamic_cast<Entidades::Obstaculos::Obstaculo*>(novaEntidade);
			if (novoObstaculo)
				novoObstaculo->carregarObstaculo(esta);

			GC.incluirObstaculo(static_cast<Entidades::Obstaculos::Obstaculo*>(novaEntidade));

			std::cout << "Instanciou um obstaculo" << std::endl;
		}
		else //NESSE CASO O ID É 10 E É UMA FACA
		{
			novaEntidade = instanciarEntidadeExclusiva(idEntidade, recuperadorEntidades);
		}
		if (novaEntidade)
		{
			novaEntidade->setPosicao(posicao);
			novaEntidade->setTamanho(escala);
			if(idEntidade != 3)
				lista_ents.incluir(novaEntidade);
		}
		else
		{
			std::cout << "Deu merda no nova entidade" << std::endl;
		}
	}

	recuperadorEntidades.close();
	std::cout << "Deu close no recuperador" << std::endl;
	
	executar();			//Espero que chame o executar da classe filha
}

NightFall::Entidades::Entidade* NightFall::Fases::Fase::instanciarEntidadeGenerica(int id, std::ifstream& arq, bool* primeiroJogador, int estadoParede)
{
	//personagem
	int vidas = -1, velMax = -1;
	sf::Vector2f velAtual;
	int pulo = -1;
	bool chao = false;
	float tempoCor = 0.0f;

	//inimigo
	int direcao;
	float tempovagar;
	
	int pontos = -1, poder = -1;

	NightFall::Entidades::Obstaculos::Plataforma* alocadorPlataforma = nullptr;
	int altura = -1;
	float origposy = -1;
	bool mobil = false;
	int ampl = -1;

	NightFall::Entidades::Personagens::Morcego* alocadorMorcego = nullptr;
	float raio = -0.01f;

	switch (id) 
	{
	case 3: //JOGADOR
		
		arq >> pontos >> poder;
		if (*primeiroJogador == true)
		{
			pJog->setDoisJogadores(false);
			*primeiroJogador = false;
			pJog1->carregarJogador(pontos, poder);
			return pJog1;
		}
		else
		{
			pJog2->carregarJogador(pontos, poder);
			return pJog2;
		}
		return nullptr;

	case 4: //PLATAFORMA
		arq >> altura >> origposy
			>> mobil >> ampl;

		if (estadoParede != 2)	//NAO É PAREDE
		{
			std::cout << "Plataforma" << std::endl;

			alocadorPlataforma = new NightFall::Entidades::Obstaculos::Plataforma();

			alocadorPlataforma->carregarPlataforma(altura, origposy, mobil, ampl);
			alocadorPlataforma->setTextura("Plataforma");

			return alocadorPlataforma;
		}
		return nullptr;

	case 5:	//MORCEGO

		arq >> direcao >> tempovagar >> raio;

		std::cout << "Morcego" << std::endl;
		
		NightFall::Entidades::Personagens::Morcego* alocadorMorcego = new NightFall::Entidades::Personagens::Morcego();

		alocadorMorcego->carregarInimigo(direcao, tempovagar);
		alocadorMorcego->carregarMorcego(raio);

		alocadorMorcego->setTextura("Morcego");
		GC.incluirInimigo(alocadorMorcego);
		alocadorMorcego->resetarUltimaPosicao();

		return alocadorMorcego;
	}
	return nullptr;
	
}

// Atualiza eventos, trata pausa, desenha cenário e processa entidades e colisões a cada frame.
void NightFall::Fases::Fase::fluir()
{
	pGE->executar();
	if (pGE->getPause())
	{
		pJog->jogoPausar();
		pGE->setPause(false);
		lista_ents.resetarClocks();
	}
	pGG->limpaJanela();
	(this)->desenhar();
	pGG->getWindow()->draw(pontoFinal);
	lista_ents.percorrer();
	GC.executar();
	pGG->mostraElementos();
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

void NightFall::Fases::Fase::povoarFase()
{
	pJog1->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog1->getTamanho().y));
	if (pJog2 != nullptr && pJog->getDoisJogadores())
		pJog2->setPosicao(sf::Vector2f(0.0f, pGG->getAlturaChao() - pJog2->getTamanho().y));

	criarCenario();	//deve ser o primeiro para o set chao ser feito no momento correto
	criarInimigos();
	criarObstaculo();

	executar();
}

void NightFall::Fases::Fase::executar()
{
	lista_ents.resetarClocks();
	fase_ativa = true;
	std::cout << "EXECUTAR CHEGOU" << std::endl;

	GC.setGerGrafico(pGG);
	pGE->setGerenciador_Grafico(pGG);
	pGE->setGerenciador_Colisoes(&GC);

	//IMPORTANTE, DESLIGA O PAUSE
	pGE->setPause(false);

	//bandeira que representa o fim da fase
	pontoFinal.setTexture(pGG->getTextura("PontoFinal"));
	pontoFinal.setScale(0.1f, 0.1f);

	sf::Vector2u tamanhoTextura = pGG->getTextura("PontoFinal").getSize();
	sf::Vector2f tamanhoEscalado(
		tamanhoTextura.x * pontoFinal.getScale().x,
		tamanhoTextura.y * pontoFinal.getScale().y
	);

	// Colocando a bandeira no canto direito em baixo da tela
	posFinal.x = 1280.0f - tamanhoEscalado.x;
	posFinal.y = 600.0f - tamanhoEscalado.y;

	pontoFinal.setPosition(posFinal);


	NightFall::Entidades::Personagens::Inimigo::setJogador(pJog1);
	if(pJog2 != nullptr && pJog->getDoisJogadores())
		NightFall::Entidades::Personagens::Inimigo::setJogador(pJog2);
}

void NightFall::Fases::Fase::setJogo(Jogo* pjogo)
{
	pJog = pjogo;
}