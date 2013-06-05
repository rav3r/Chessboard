#include "Config.h"
#ifdef COMPILE_TEST_ZBYSZEK

#include <iostream>
#include <cstdlib>
#include "Figure.h"
#include "Board.h"

std::vector<Figure*>* lol;
std::vector<Figure*> wek;

int main(int argc, char *argv[])
{
	std::cout << "Test Zbyszka\n\n\n";
	
	Board* b = new Board();

	//Figure* fig = b->getFigure(3,7);  //bialy krol
	//Figure* fig = b->getFigure(4,7);  //biala krolowa
	//Figure* fig = b->getFigure(5,7);  //bialy prawy laufer
	//Figure* fig = b->getFigure(6,7);  //bialy prawy kon
	//Figure* fig = b->getFigure(7,7);  //biala prawa wieza
	//Figure* fig = b->getFigure(7,6);  //bialy pionek max od prawej	
	
	b->printFigures();
	b-> moveTo(7,1,b->getFigure(7,7));
	b->printFigures();
	std :: cout << "Is szach?: " << b->isSzach();






	std::cout << "\n\n";
	system("PAUSE");
	return EXIT_SUCCESS;
}

#endif