#include "Config.h"
#ifdef COMPILE_TEST_ZBYSZEK

#include <iostream>

#include <iostream>
#include <cstdlib>
#include "Figure.h"
#include "Board.h"

std::vector<Figure*>* lol;
std::vector<Figure*> wek;

int main(int argc, char *argv[])
{
	std::cout << "Test Zbyszka\n";
	/*
	Figure* figura = new Figure(0, 2, 2);
	Figure* figura2 = new Figure(0, 2, 2);
	bool lol = figura -> moveFigure(1,1);
	cout << figura -> getX() << "  " << lol << "\n";
	cout << (figura == figura2) << "  lol\n";

	
	*/
	Board* b = new Board();
	
	lol = b->getWhite();
	wek = *lol;
	wek[0] -> print();




	system("PAUSE");
	return EXIT_SUCCESS;
}

#endif