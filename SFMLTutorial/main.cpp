#include <iostream>
#include <SFML/Graphics.hpp> //biblioteca usada para gerar a janela
#include <random>
#include <chrono>

//Converte cores HSV para RGB
sf::Color HSVToRGB(float h, float s, float v)
{
	float hPrime = h / 60.0f;
	unsigned int hIndex = unsigned int(hPrime) % 6;

	float chroma = s * v;
	float min = v - chroma;
	float x = chroma * (1.0f - abs(fmod(hPrime, 2.0f) - 1.0f));

	float outRGB[6][3] =
	{
		{chroma, x, 0.0f},
		{x, chroma, 0.0f},
		{0.0f, chroma, x},
		{0.0f, x, chroma},
		{x, 0.0f, chroma},
		{chroma, 0.0f, x}
	};

	float rF = outRGB[hIndex][0] + min;
	float gF = outRGB[hIndex][1] + min;
	float bF = outRGB[hIndex][2] + min;

	rF *= 255.0f;
	gF *= 255.0f;
	bF *= 255.0f;

	std::uint8_t rI = std::uint8_t(rF);
	std::uint8_t gI = std::uint8_t(gF);
	std::uint8_t bI = std::uint8_t(bF);

	return sf::Color(rI, gI, bI);
}

int main()
{
	//tamanho da janela
	unsigned int width = 640; 
	unsigned int height = 360;

	//Cria a janela e da um nome a ela
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Tutorials");
	window->setFramerateLimit(60); //limita os frames para 60

	//Imagem a ser utilizada na janela
	sf::Image image;
	image.resize({ width, height });

	sf::Texture texture(image.getSize());

	sf::Sprite sprite(texture);

	//Tamanho do tabuleiro
	unsigned int size = width * height;

	//Variavel do tabuleiro e vizinhos
	unsigned int* board = new unsigned int[size];
	unsigned int* neighbors = new unsigned int[size];

	//Direcoes possiveis
	int dir[8] = { 1, int(width) + 1, int(width), int(width) - 1 - 1, -int(width) - 1, -int(width), -int(width) + 1 };

	//Geracao de numeros aleatorios
	std::default_random_engine randEng;
	int seed = std::chrono::steady_clock::now().time_since_epoch().count();
	randEng.seed(seed);

	//Tabuleiro aleatorizado
	for (unsigned int i = 0; i < size; ++i)
	{
		std::uniform_int_distribution onOff(0, 1);
		board[i] = onOff(randEng);
		neighbors[i] = 0;
	}

	//enquanto a janela estiver aberta
	while (window->isOpen())
	{
		//pega o próximo evento
		while (const std::optional event = window->pollEvent())
		{
			//se a janela for fechada(via clicar no X)
			if (event->is<sf::Event::Closed>())
			{
				//fecha a janela
				window->close();
			}
			//se o evento for usar o teclado(pega a tecla)
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				//ve se a tecla pressionada é Esc
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				{
					window->close();
				}
			}
		}

		//Atualza o numero de vizinhos para cada celula ligada
		for (unsigned int i = 0; i < size; ++i)
		{
			if (board[i] == 0)
			{
				continue;
			}
			for (int j = 0; j < 8; ++j)
			{
				int index = i + dir[j];
				if (index < 0)
				{
					index += size;
				}
				else if (index > size - 1)
				{
					index -= size;
				}
				++neighbors[index];
			}
		}

		//Regras do Jogo da Vida de Conway
		for (unsigned int i = 0; i < size; ++i)
		{
			//if off && neighbors == 3 -> On
			//if on && neighbors < 2 || neighbors > 3 -> Off

			if (board[i] == 0 && neighbors[i] == 3)
			{
				board[i] = 1;
			}
			else if (board[i] == 1 && (neighbors[i] < 2 || neighbors[i] > 3))
			{
				board[i] = 0;
			}

			// Define a cor de cada celula
			sf::Color color = board[i] == 1 ? sf::Color::White : sf::Color::Black;

			unsigned int x = i % width;
			unsigned int y = floor(i / width);

			//Atualiza a cor da celula na posicao correspondente
			sf::Vector2u pos = sf::Vector2u(x, y);

			image.setPixel(pos, color);

			neighbors[i] = 0;
		}

		//Atualiza a textura
		texture.update(image);

		//Render
		window->clear();

		//Drawing
		window->draw(sprite);

		window->display();
	}

	//Libera memoria alocada
	delete[] board;
	delete[] neighbors;
	delete window;
	return 0;
}