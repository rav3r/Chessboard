using namespace std;

#include <iostream>
#include <cstdlib>
#include "Figure.h"

int main(int argc, char *argv[])
{
	Figure* figura = new Figure(0, 2, 2);
	Figure* figura2 = new Figure(0, 2, 2);
	bool lol = figura -> moveFigure(1,1);
	cout << figura -> getX() << "  " << lol << "\n";
	cout << (figura == figura2) << "  lol\n";

	system("PAUSE");
	return EXIT_SUCCESS;
}