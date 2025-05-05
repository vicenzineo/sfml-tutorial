#include <iostream>
#include <SFML/Graphics.hpp> //biblioteca usada para gerar a janela

int main()
{
	//tamanho da janela
	unsigned int width = 640; 
	unsigned int height = 360;

	//Cria a janela e da um nome a ela
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "Tutorials");
	window->setFramerateLimit(60); //limita os frames para 60

	/*sf::CircleShape circle(64.0f); //cria um circulo de raio 7
	circle.setOrigin(circle.getGeometricCenter()); //faz com que sempre que se desenhe o circulo, seu centro seja de fato seu centro
	circle.setPosition({ width / 4.0f, height / 4.0f }); //inicia o circulo no centro
	circle.setFillColor(sf::Color::Green); //define a cor do circulo
	circle.setOutlineThickness(3.0f); //define a grossura de seu contorno
	circle.setOutlineColor(sf::Color::Magenta); //define a cor de seu contorno
	circle.setPointCount(3); //define o numero de pontos, neste caso é um triangulo

	sf::RectangleShape rectangle({ 50.0f, 80.0f }); //Cria um retangulo com 50 de altura e 80 de largura
	rectangle.setOrigin(rectangle.getSize() / 2.0f);
	rectangle.setPosition({ width / 2.0f, height / 2.0f });
	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setOutlineThickness(5.0f);
	rectangle.setOutlineColor(sf::Color::Blue);*/

	sf::ConvexShape convex;
	convex.setPointCount(6);
	convex.setPoint(0, { 13.0f, 17.0f }); //fala onde será o ponto
	convex.setPoint(1, { 3.5f, 1.6f });
	convex.setPoint(2, { 0.25f, -12.0f });
	convex.setPoint(3, { -12.0f, -7.3f });
	convex.setPoint(4, { -12.5f, -1.6f });
	convex.setPoint(5, { -5.0f, 7.5f });
	convex.setOrigin(convex.getGeometricCenter());
	convex.setFillColor(sf::Color(0x3F00FFFF));//1-2(vermelho), 3-4(verde), 5-6(azul), 7-8(transparencia)
	convex.setOutlineThickness(2.4f);
	convex.setOutlineColor(sf::Color(0xFF8888FF));
	convex.setPosition({ width / 2.0f, height / 2.0f });


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

		//circle.rotate(sf::degrees(1)); //rotaciona o circulo em 1 grau a cada frame
		//circle.move({ 1.0f, -1.0f }); //move o circulo para direita e para cima

		//circle.move({ 1.0f, 1.0f });
		//rectangle.move({ -1.0f, -1.0f });

		//circle.setFillColor(sf::Color::Green);
		//rectangle.setFillColor(sf::Color::Yellow);

		//detecta se o circulo e o retangulo se encostaram
		/*if (circle.getGlobalBounds().findIntersection(rectangle.getGlobalBounds()))
		{
			circle.setFillColor(sf::Color::Red);
			rectangle.setFillColor(sf::Color::Red);
		}*/

		//Render
		window->clear();

		//Drawing
		//window->draw(circle);
		//window->draw(rectangle);
		window->draw(convex);

		window->display();
	}

	delete window;
	return 0;
}