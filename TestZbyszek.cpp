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

	//b->printFigures();

	/*
	//test zbijania biala prawa wieza czarnego pionka i szachowania biala wieza posrodku planszy czarnego krola na pierwotnym miejscu
	Figure* fig = b->getFigure(7,7);
	std :: cout << "Ruch mozliwy?:" << b-> moveTo(7,1,fig) << "\n";
	std :: cout << "Is white szachowany?: " << b->isWhiteSzachowany() << "\n";
	std :: cout << "Is black szachowany?: " << b->isBlackSzachowany() << "\n";
	std :: cout << "Is white matowany?: " << b->isWhiteMatowany() << "\n";
	std :: cout << "Is black matowany?: " << b->isBlackMatowany() << "\n";
	*/

	/*
	//Test dopuszczenia do ruchu laufra - po tym ruchu bedzie szach
	Figure* fig = b->getFigure(3,1);
	std :: cout << "Przed ruchem: " << fig->getX() << ":" << fig->getY() << "\n";
	std :: cout << "Ruch mozliwy?:" << b-> moveTo(4,2,fig) << "\n";
	std :: cout << "Po ruchu: " << fig->getX() << ":" << fig->getY() << "\n";
	std :: cout << "Is white szachowany?: " << b->isWhiteSzachowany() << "\n";
	std :: cout << "Is black szachowany?: " << b->isBlackSzachowany() << "\n";
	std :: cout << "Is white matowany?: " << b->isWhiteMatowany() << "\n";
	std :: cout << "Is black matowany?: " << b->isBlackMatowany() << "\n";
	*/

	//b->printFigures();

	//b->printFigures();
	Figure* f = b->getFigure(3,4);
	std::cout << "Ruch wiezy" << b->moveTo(3,1,f) << "\n";
	 f = b->getFigure(3,0);
	std::cout << "Ruch krola" << b->moveTo(3,1,f) << "\n";



	std::cout << "\n\n";
	system("PAUSE");
	return EXIT_SUCCESS;
}

#endif