#include "Figure.h"
#include "Board.h"
#include <iostream>

using namespace std;

Figure :: Figure(int _type, int _x, int _y, int c, Board* b)
{
	type = _type;
	x = _x;
	y = _y;
	color = c;
	board = b;
}


bool Figure :: moveFigure(int xx, int yy)
{
	bool moveOk = false;
	switch(type)
	{
		case 0: {cout << "Krol\n";  moveOk = isKingMovePossible(xx, yy);  break;}
		case 1: {cout << "Krolowa\n";  moveOk = isQueenMovePossible(xx, yy);  break;}
		case 2: {cout << "Wieza\n";  moveOk = isRookMovePossible(xx, yy);  break;}
		case 3: {cout << "Laufer\n";  moveOk = isKnightMovePossible(xx, yy);  break;}
		case 4: {cout << "Kon\n";  moveOk = isBishopMovePossible(xx, yy);  break;}
		case 5: {cout << "Pionek\n";  moveOk = isPawnMovePossible(xx, yy);  break;}
	}
	if (moveOk)
	{
		cout << "Mozna ruszyc\n";
		x = xx;
		y = yy;
	}
	else
	{
		cout << "Nie mozna ruszyc\n";
	}
	return moveOk;
}

int Figure :: getColor() {return color;}

bool Figure :: isColorOfTheFigureTheSame(int xx, int yy)
{ //false - zgodne
	Figure* fig = board->getFigure(xx,yy);
	if(fig!=NULL)
		if(fig->getColor()==color)
			return true;
	return false;
}

bool Figure :: isKingMovePossible(int xx, int yy)
{
	std::cout << "Test koloru krola\n";
	if(isColorOfTheFigureTheSame(xx,yy))
			return false;
	std::cout << "Test koncowego polozenia krola\n";
	if(abs(x-xx)>1 || abs(y-yy)>1)
		return false;
	std::cout << "Ruch mozliwy\n";
	return true;
}
bool Figure :: isQueenMovePossible(int xx, int yy){ return false;}
bool Figure :: isRookMovePossible(int xx, int yy){return false;}
bool Figure :: isKnightMovePossible(int xx, int yy){ return false;}
bool Figure :: isBishopMovePossible(int xx, int yy){ return false;}
bool Figure :: isPawnMovePossible(int xx, int yy){ return false;}

int Figure :: getX() {return x;}
int Figure :: getY() {return y;}
void Figure :: setXY(int xx, int yy) {x=xx; y=yy;}
int Figure :: getType() {return type;}


void Figure::print()
{
	cout << "Typ:" << type << "   x:" << x << "  y:" << y << "   kolor:" << color << "\n";
};