#include <iostream>
#include <SFML/Graphics.hpp> //biblioteca usada para gerar a janela
#include <random>
#include <chrono>
#include <string>
#include <sstream>

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

//Funcao para carregar fontes
void LoadFont(sf::Font& font, std::string str)
{
	if (!font.openFromFile(str)) 
	{
		std::cerr << "ERROR: COULD NOT LOAD FILE::" << str << "!!!" << std::endl;
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

	//Outra janela
	sf::RenderWindow *window2 = new sf::RenderWindow(sf::VideoMode({ width / 3, height / 2 }), "Tutorials2");
	window2->setFramerateLimit(60);

	sf::CircleShape circle(64.0f);
	circle.setOrigin(circle.getGeometricCenter());
	circle.setPosition({ width / 2.0f, height / 2.0f });
	circle.setFillColor(sf::Color(0x6495EDFF));

	sf::CircleShape circle2(32.0f);
	circle2.setOrigin(circle2.getGeometricCenter());
	circle2.setPosition({ window2->getSize().x / 2.0f, window2->getSize().x / 2.0f });
	circle2.setFillColor(sf::Color(0x6495EDFF));

	window2->setPosition(window->getPosition());
	
	//enquanto a janela estiver aberta
	while (window->isOpen())
	{
		window2->setPosition(window->getPosition());
		

		//Faz seguir o mouse quando a janela for selecionada
		if (window->hasFocus())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sf::Vector2i pos = sf::Mouse::getPosition(*window);
				circle.setPosition(sf::Vector2f(pos));
			}
		}

		if (window2->hasFocus())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				sf::Vector2i pos = sf::Mouse::getPosition(*window2);
				circle2.setPosition(sf::Vector2f(pos));
			}
		}

		if (window2->isOpen() == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
			{
				window2 = new sf::RenderWindow(sf::VideoMode({ width / 3, height / 2 }), "Tutorials2");
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			window2->close();
		}

		std::cout << "X: " << sf::Mouse::getPosition(*window).x << std::endl;
		std::cout << "Y: " << sf::Mouse::getPosition(*window).y << std::endl << std::endl;

		PollEvents(*window);
		PollEvents(*window2);
		
		//Render
		window->clear();
		window2->clear();

		//Drawing
		window->draw(circle);
		window2->draw(circle2);

		window->display();
		window2->display();
	}

	//Libera memoria alocada
	delete window;
	delete window2;

	return 0;
}