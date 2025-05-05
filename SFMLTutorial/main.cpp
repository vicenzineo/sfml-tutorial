#include <iostream>
#include <SFML/Graphics.hpp> //biblioteca usada para gerar a janela

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

//Cria um enum para saber facilmente qual textura esta sendo acessada
enum directions { down, right, up, left };

int main()
{
	//tamanho da janela
	unsigned int width = 640; 
	unsigned int height = 360;

	//Cria a janela e da um nome a ela
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Tutorials");
	window->setFramerateLimit(60); //limita os frames para 60

	int n = 24;//Precisa ser par
	
	//Cria um array de um tipo primitivo(pontos, linhas, triangulos) e depois define qual o tipo
	sf::VertexArray lines;
	lines.setPrimitiveType(sf::PrimitiveType::Lines);
	lines.resize(n);//Ajusta o tamanho do vetor

	//Este tipo faz com que o ultimo ponto de uma linha torne-se o ponto de partida de outra
	sf::VertexArray lineStripes;
	lineStripes.setPrimitiveType(sf::PrimitiveType::LineStrip);
	lineStripes.resize(n);

	//Triangulo 
	sf::VertexArray triangles;
	triangles.setPrimitiveType(sf::PrimitiveType::Triangles);
	triangles.resize(6);
	triangles.resize(width * height * 6);

	float size = 48.0f;
	
	//Aqui se faz o quadrado
	//sf::Vector2f v0 = { 0.0f, 0.0f };
	//sf::Vector2f v1 = { size, 0.0f };
	//sf::Vector2f v2 = { 0.0f, size };
	//sf::Vector2f v3 = { size, size };
	//
	//triangles[0].position = v0;
	//triangles[1].position = v1;
	//triangles[2].position = v2;
	//triangles[3].position = v3;
	//triangles[4].position = v2;
	//triangles[5].position = v1;

	//for (int i = 0; i < 6; i++)
	//{
	//	triangles[i].position += {width / 1.5f, height / 1.5f};
	//
	//	triangles[i].color = HSVToRGB(60.0f * i, 1.0f, 1.0f);
	//}

	//Cobre toda a tela em triangulos
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			const int index = 6 * (i * height + j);

			sf::Vector2f v0 = { size * i, size * j };
			sf::Vector2f v1 = { size * i, size * (j + 1) };
			sf::Vector2f v2 = { size * (i + 1), size * j };
			sf::Vector2f v3 = { size * (i + 1), size * (j + 1) };

			triangles[index + 0].position = v0;
			triangles[index + 1].position = v1;
			triangles[index + 2].position = v2;
			triangles[index + 3].position = v3;
			triangles[index + 4].position = v2;
			triangles[index + 5].position = v1;

			triangles[index + 0].color = HSVToRGB(0.0f, 1.0f, 1.0f);
			triangles[index + 1].color = HSVToRGB(60.0f, 1.0f, 1.0f);
			triangles[index + 2].color = HSVToRGB(120.0f, 1.0f, 1.0f);
			triangles[index + 3].color = HSVToRGB(180.0f, 1.0f, 1.0f);
			triangles[index + 4].color = HSVToRGB(240.0f, 1.0f, 1.0f);
			triangles[index + 5].color = HSVToRGB(300.0f, 1.0f, 1.0f);
		}
	}

	//Espiral
	for (int i = 0; i < n; i++)
	{
		sf::Vector2f pos = { float(i * cos(i)), float(i * sin(i)) };
		float hue = i * (360.0f / n);

		lines[i].position = pos;
		lines[i].position += {width / 4.0f, height / 4.0f};
		lines[i].color = HSVToRGB(hue, 1.0f, 1.0f);

		lineStripes[i].position = pos;
		lineStripes[i].position += {width / 2.0f, height / 2.0f};
		lineStripes[i].color = HSVToRGB(hue, 1.0f, 1.0f);
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

		
		//Render
		window->clear();

		//Drawing
		window->draw(lines);
		window->draw(lineStripes);
		window->draw(triangles);

		window->display();
	}

	delete window;
	return 0;
}