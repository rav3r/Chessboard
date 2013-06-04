#include "Board.h"
#include "Figure.h"

#include <iostream>

using namespace std;

Board::Board()
{
	createFigures();
	szach = false;
	mat = false;
};

Figure* Board::getFigure(int xx, int yy)
{
	for (int i=0; i<black.size(); i++)
	{
		if (black[i]->getX()==xx && black[i]->getY()==yy)
			return black[i];
	}
	for (int i=0; i<white.size(); i++)
	{
		if (white[i]->getX()==xx && white[i]->getY()==yy)
			return white[i];
	}
	return NULL;
}


std::vector<Figure*>* Board::getWhite()
{
	return &white;
};

std::vector<Figure*>* Board::getBlack()
{
	return &black;
};

bool Board::isFigureOnField(int xx, int yy)
{
	if (isBlackOnField(xx,yy) || isWhiteOnField(xx,yy))
		return true;
	return false;
}


bool Board::isBlackOnField(int xx, int yy)
{
	for (int i=0; i<black.size(); i++)
	{
		if (black[i]->getX()==xx && black[i]->getY()==yy)
			return true;
	}
	return false;
}

bool Board::isWhiteOnField(int xx, int yy)
{
	for (int i=0; i<white.size(); i++)
	{
		if (white[i]->getX()==xx && white[i]->getY()==yy)
			return true;
	}
	return false;
}

bool Board::fieldExists(int xx, int yy)
{
	if (xx>=0 && xx<=7 && yy>=0 && yy<=7)
		return true;
	return false;
}


void Board::createFigures()
{
	cout << "Dziala\n";
	white.push_back(new Figure(0,3,7,1,this));
	white.push_back(new Figure(1,4,7,1,this));
	white.push_back(new Figure(2,0,7,1,this));
	white.push_back(new Figure(2,7,7,1,this));
	white.push_back(new Figure(3,2,7,1,this));
	white.push_back(new Figure(3,5,7,1,this));
	white.push_back(new Figure(4,1,7,1,this));
	white.push_back(new Figure(4,6,7,1,this));

	white.push_back(new Figure(5,0,6,1,this));
	white.push_back(new Figure(5,1,6,1,this));
	white.push_back(new Figure(5,2,6,1,this));
	//white.push_back(new Figure(5,3,6,1,this));
	white.push_back(new Figure(5,4,6,1,this));
	white.push_back(new Figure(5,5,6,1,this));
	white.push_back(new Figure(5,6,6,1,this));
	white.push_back(new Figure(5,7,6,1,this));

	black.push_back(new Figure(0,3,0,0,this));
	black.push_back(new Figure(1,4,0,0,this));
	black.push_back(new Figure(2,0,0,0,this));
	black.push_back(new Figure(2,7,0,0,this));
	black.push_back(new Figure(3,2,0,0,this));
	black.push_back(new Figure(3,5,0,0,this));
	black.push_back(new Figure(4,1,0,0,this));
	black.push_back(new Figure(4,6,0,0,this));

	black.push_back(new Figure(5,0,1,0,this));
	black.push_back(new Figure(5,1,1,0,this));
	black.push_back(new Figure(5,2,1,0,this));
	black.push_back(new Figure(5,3,1,0,this));
	black.push_back(new Figure(5,4,1,0,this));
	black.push_back(new Figure(5,5,1,0,this));
	black.push_back(new Figure(5,6,1,0,this));
	black.push_back(new Figure(5,7,1,0,this));
	cout << "Utworzono\n";
};