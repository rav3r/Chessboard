using namespace std;

#include "Board.h"
#include <iostream>

Board::Board()
{
	createFigures();
};


std::vector<Figure*>* Board::getWhite()
{
	return &white;
};

std::vector<Figure*>* Board::getBlack()
{
	return &black;
};


void Board::createFigures()
{
	cout << "Dziala\n";
	white.push_back(new Figure(0,3,7));
	white.push_back(new Figure(1,4,7));
	white.push_back(new Figure(2,0,7));
	white.push_back(new Figure(2,7,7));
	white.push_back(new Figure(3,2,7));
	white.push_back(new Figure(3,5,7));
	white.push_back(new Figure(4,1,7));
	white.push_back(new Figure(4,6,7));

	white.push_back(new Figure(5,0,6));
	white.push_back(new Figure(5,1,6));
	white.push_back(new Figure(5,2,6));
	white.push_back(new Figure(5,3,6));
	white.push_back(new Figure(5,4,6));
	white.push_back(new Figure(5,5,6));
	white.push_back(new Figure(5,6,6));
	white.push_back(new Figure(5,7,6));

	black.push_back(new Figure(0,3,0));
	black.push_back(new Figure(1,4,0));
	black.push_back(new Figure(2,0,0));
	black.push_back(new Figure(2,7,0));
	black.push_back(new Figure(3,2,0));
	black.push_back(new Figure(3,5,0));
	black.push_back(new Figure(4,1,0));
	black.push_back(new Figure(4,6,0));

	black.push_back(new Figure(5,0,1));
	black.push_back(new Figure(5,1,1));
	black.push_back(new Figure(5,2,1));
	black.push_back(new Figure(5,3,1));
	black.push_back(new Figure(5,4,1));
	black.push_back(new Figure(5,5,1));
	black.push_back(new Figure(5,6,1));
	black.push_back(new Figure(5,7,1));
	cout << "Utworzono\n";
};