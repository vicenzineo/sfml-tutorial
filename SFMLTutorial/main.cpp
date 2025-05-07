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

void PollEvents(sf::RenderWindow &window)
{
	while (const std::optional event = window.pollEvent())
	{
		//se a janela for fechada(via clicar no X)
		if (event->is<sf::Event::Closed>())
		{
			//fecha a janela
			window.close();
		}
		//se o evento for usar o teclado(pega a tecla)
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			//ve se a tecla pressionada é Esc
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
			{
				window.close();
			}
		}
	}
}

int main()
{
	//tamanho da janela
	unsigned int width = 640; 
	unsigned int height = 360;

	//Cria a janela e da um nome a ela
	sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Tutorials");
	window->setFramerateLimit(60); //limita os frames para 60

	sf::Texture texture;

	if (!texture.loadFromFile("Sprites/AnimationExample.png"))
	{
		std::cerr << "COULD NOT LOAD FILE::Sprites/AnimationExample.png!!!" << std::endl;
		return -1;
	}

	sf::Sprite sprite(texture);

	//Para lidar com a animacao
	int texWidth = 0;

	sprite.setTextureRect({ {0,0}, {32, 32} });
	sprite.setOrigin({ sprite.getTextureRect().size.x / 2.0f,  sprite.getTextureRect().size.y / 2.0f });
	sprite.setPosition({ width / 2.0f, height / 2.0f });
	sprite.setScale({ 4.0f, 4.0f });

	float timer = 0.0f;
	float timerMax = 0.25f;
	float waitTimerMax = 2.25f;
	float waitTimer = waitTimerMax;

	//enquanto a janela estiver aberta
	while (window->isOpen())
	{
		PollEvents(*window);

		//Para fazer a animacao parar por um tempo
		if (waitTimer >= waitTimerMax)
		{
			timer += 0.1f;
			if (timer >= timerMax)
			{
				texWidth += 32;

				//Quando chegar ao final, volta ao comeco
				if (texWidth >= texture.getSize().x)
				{
					texWidth = 0.0f;
				}

				//Animacao continuara movendo para a direita
				if (texWidth < texture.getSize().x)
				{
					sprite.setTextureRect({ {texWidth, 0}, {32, 32} });
				}
			}
			//Para a animacao no meio
			if (texWidth == texture.getSize().x / 2.0f)
			{
				waitTimer = 0.0f;
			}
		}
		if (waitTimer < waitTimerMax)
		{
			waitTimer += 0.1f;
		}
		
		//Render
		window->clear();

		//Drawing
		window->draw(sprite);

		window->display();
	}

	//Libera memoria alocada
	delete window;

	return 0;
}