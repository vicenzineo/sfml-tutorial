#include <iostream>
#include <SFML/Graphics.hpp> //biblioteca usada para gerar a janela

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

	//Cria uma textura
	sf::Texture texture;

	//Carrega a textura de um arquivo
	if (!texture.loadFromFile("Sprites/ExampleSprite.png"))
	{
		//Caso não abra, retorna -1
		std::cerr << "ERROR::COULD NOT NOT FILE::Sprites/ExampleSprite.png" << std::endl;
		return -1;
	}

	//Carrega a textura no sprite
	sf::Sprite sprite(texture);

	//Cria um vetor para armazenar as texturas
	sf::IntRect dir[4];

	//Separa a textura em outras mini texturas
	for (int i = 0; i < 4; i++)
	{
		dir[i] = sf::IntRect({ {32 * i, 0}, {32, 32} });
	}
	//Inicia a textura
	sprite.setTextureRect(dir[down]);
	sprite.setOrigin({ 16, 16 });
	sprite.setPosition({ width / 2.0f, height / 2.0f });
	sprite.setColor(sf::Color(0x6495EDFF));

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

		//É possivel rotacionar sprites
		sprite.rotate(sf::degrees(1));

		//O bloco de ifs ira identificar caso wasd estão pressionados para mudar para a textura apropriada e mover
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S))
		{
			sprite.move({ 0.0f, 1.0f });
			sprite.setTextureRect(dir[down]);
		} 
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W))
		{
			sprite.move({ 0.0f, -1.0f });
			sprite.setTextureRect(dir[up]);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D))
		{
			sprite.move({ 1.0f, 0.0f });
			sprite.setTextureRect(dir[right]);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A))
		{
			sprite.move({ -1.0f, 0.0f });
			sprite.setTextureRect(dir[left]);
		}
		
		//Render
		window->clear();

		//Drawing
		window->draw(sprite);

		window->display();
	}

	delete window;
	return 0;
}