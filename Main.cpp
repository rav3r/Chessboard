#include "Config.h"
#ifdef COMPILE_MAIN

#include <iostream>
#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include "Board.h"

int main()
{
	std::cout << "Main Module\n";
	
	// Ustawienia graficzne
	sf::RenderWindow renderWindow(sf::VideoMode(600, 600), "Chessboard", sf::Style::Close);
	sf::Event event;
	
	sf::Texture boardTexture;
	boardTexture.loadFromFile("data/board.png");
	sf::Sprite boardSprite(boardTexture);

	sf::Texture figuresTexture;
	figuresTexture.loadFromFile("data/figures.png");
	sf::Sprite figuresSprites[6*2];
	for(int color=0; color<2; color++)
	{
		for(int f=0; f<6; f++)
		{
			int id = color*6+f;
			figuresSprites[id].setTexture(figuresTexture);
			figuresSprites[id].setTextureRect(sf::IntRect(f*75, color*75, 75, 75));
		}
	}

	// Tworzenie planszy
	Board board;

	std::vector<Figure* >& black = *board.getBlack();
	std::vector<Figure* >& white = *board.getWhite();

	// G³ówna pêtla programu
	while(renderWindow.isOpen())
	{
		// Przejmowanie eventów
		sf::Event event;
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
		}

		// Rysowanie
		renderWindow.clear(sf::Color::Black);

		renderWindow.draw(boardSprite);

		for(int i=0; i<black.size(); i++)
		{
			Figure* figure = black[i];
			int type = figure->getType();
			int x = figure->getX();
			int y = figure->getY();
			figuresSprites[type].setPosition(x*75, y*75);
			renderWindow.draw(figuresSprites[type]);
		}

		for(int i=0; i<white.size(); i++)
		{
			Figure* figure = white[i];
			int type = figure->getType();
			int x = figure->getX();
			int y = figure->getY();
			figuresSprites[type+6].setPosition(x*75, y*75);
			renderWindow.draw(figuresSprites[type+6]);
		}

		renderWindow.display();
	}

	return 0;
}

#endif