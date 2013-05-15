using namespace std;

#include "Figure.h"
#include <iostream>

Figure :: Figure(int _type, int _x, int _y)
{
	type = _type;
	x = _x;
	y = _y;
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

bool Figure :: isKingMovePossible(int xx, int yy){ return true;}
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
	cout << "Typ:" << type << "   x:" << x << "  y:" << y;
};