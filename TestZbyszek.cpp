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
	std::cout << "Test Zbyszka\n";
	
	Board* b = new Board();

	Figure* fig = b->getFigure(3,7);  //bialy krol
	//Figure* fig = b->getFigure(4,7);  //biala krolowa
	//Figure* fig = b->getFigure(5,7);  //bialy prawy laufer
	//Figure* fig = b->getFigure(6,7);  //bialy prawy kon
	//Figure* fig = b->getFigure(7,7);  //biala prawa wieza
	//Figure* fig = b->getFigure(7,6);  //bialy pionek max od prawej
	fig->moveFigure(3,6);


	/*
	lol = b->getWhite();
	wek = *lol;
	wek[0] -> print();
	*/

	/*
	std::cout << "Field 1,1 exists: " << b->fieldExists(1,1) << "\n";
	std::cout << "Field 7,7 exists: " << b->fieldExists(7,7) << "\n";
	std::cout << "Field -2,6 exists: " << b->fieldExists(-2,6) << "\n";
	*/

	/*
	Figure* figura = new Figure(0, 2, 2);
	Figure* figura2 = new Figure(0, 2, 2);
	bool lol = figura -> moveFigure(1,1);
	cout << figura -> getX() << "  " << lol << "\n";
	cout << (figura == figura2) << "  lol\n";
	*/


	/*
	std::cout << "Is black on field 0,0: " << b->isBlackOnField(0,0) << "\n";
	std::cout << "Is black on field 3,0: " << b->isBlackOnField(3,0) << "\n";
	std::cout << "Is black on field 0,3: " << b->isBlackOnField(0,3) << "\n";
	std::cout << "Is black on field 0,6: " << b->isBlackOnField(0,6) << "\n";

	std::cout << "Is white on field 0,0: " << b->isWhiteOnField(0,0) << "\n";
	std::cout << "Is white on field 3,0: " << b->isWhiteOnField(3,0) << "\n";
	std::cout << "Is white on field 0,3: " << b->isWhiteOnField(0,3) << "\n";
	std::cout << "Is white on field 0,6: " << b->isWhiteOnField(0,6) << "\n";

	std::cout << "Is field free 0,0: " << b->isFigureOnField(0,0) << "\n";
	std::cout << "Is field free 3,0: " << b->isFigureOnField(3,0) << "\n";
	std::cout << "Is field free 0,3: " << b->isFigureOnField(0,3) << "\n";
	std::cout << "Is field free 0,6: " << b->isFigureOnField(0,6) << "\n";
	*/


	system("PAUSE");
	return EXIT_SUCCESS;
}

#endif