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

int Figure :: getColor() {return color;}
int Figure :: getX() {return x;}
int Figure :: getY() {return y;}
void Figure :: setXY(int xx, int yy) {x=xx; y=yy;}
int Figure :: getType() {return type;}

bool Figure :: isFigureBeetweenPoints(int xx1, int yy1, int xx2, int yy2)
{
	int* tab;
	std::vector <int*> figures;
	
	if (xx1==xx2 && yy1!=yy2)  //pionowo  yy rozne
	{
		int miny = yy1<yy2 ? yy1 : yy2;
		int maxy = yy1<yy2 ? yy2 : yy1;
		for (int i=miny;i<maxy;i++)
		{
			tab = new int[2];
			tab[0] = xx1;
			tab[1] = i;
			figures.push_back(tab);
		}
	}

	if (xx1!=xx2 && yy1==yy2)  //poziomo  xx rozne
	{
		int minx = xx1<xx2 ? xx1 : xx2;
		int maxx = xx1<xx2 ? xx2 : xx1;
		for (int i=minx;i<maxx;i++)
		{
			tab = new int[2];
			tab[0] = i;
			tab[1] = yy1;
			figures.push_back(tab);
		}
	}

	if(xx1!=xx2 && yy1!=yy2)  //skosnie
	{
		int minx = xx1<xx2 ? xx1 : xx2;
		int maxx = xx1<xx2 ? xx2 : xx1;
		int miny = yy1<yy2 ? yy1 : yy2;
		int maxy = yy1<yy2 ? yy2 : yy1;
		for (int i=0;i<maxx-minx;i++)
		{
			tab = new int[2];
			tab[0] = minx+i;
			tab[1] = miny+i;
			figures.push_back(tab);
		}
	}

	if(figures.size()>0)
		figures.erase(figures.begin());

	/*
	for (int i=0;i<figures.size();i++)
	{
		cout << figures[i][0] << " " << figures[i][1] <<"\n";
	}
	*/

	for (int i=0;i<figures.size();i++)
	{
		if(board->getFigure(figures[i][0], figures[i][1])!=NULL)
			return true;
	}

	return false;
}

bool Figure :: moveFigure(int xx, int yy)
{
	bool moveOk = false;
	switch(type)
	{
		case 0: {cout << "Krol\n";  moveOk = isKingMovePossible(xx, yy);  break;}
		case 1: {cout << "Krolowa\n";  moveOk = isQueenMovePossible(xx, yy);  break;}
		case 2: {cout << "Wieza\n";  moveOk = isRookMovePossible(xx, yy);  break;}
		case 3: {cout << "Laufer\n";  moveOk = isBishopMovePossible(xx, yy);  break;}
		case 4: {cout << "Kon\n";  moveOk = isKnightMovePossible(xx, yy);  break;}
		case 5: {cout << "Pionek\n";  moveOk = isPawnMovePossible(xx, yy);  break;}
	}
	if (moveOk)
	{
		cout << "Mozna ruszyc\n";
		if(board->getFigure(xx,yy)!=NULL)
		{
			cout << "FIGHT!!!!\n";
			board->removeFigure(xx,yy);
		}
		x = xx;
		y = yy;
	}
	else
	{
		cout << "Nie mozna ruszyc\n";
	}
	return moveOk;
}


bool Figure :: isColorOfTheFigureTheSame(int xx, int yy)
{
	Figure* fig = board->getFigure(xx,yy);
	if(fig!=NULL)
		if(fig->getColor()==color)
			return true;
	return false;
}

bool Figure :: isFigureWithOppositeColor(int xx, int yy, int color)
{
	Figure* fig = board->getFigure(xx,yy);
	if(fig!=NULL)
		if(abs(fig->getColor()-color)==1)
			return true;
	return false;
}

bool Figure :: isKingMovePossible(int xx, int yy)
{//krol
	std::cout << "Test koloru krola\n";
	if(isColorOfTheFigureTheSame(xx,yy))
			return false;
	std::cout << "Test koncowego polozenia krola\n";
	if(abs(x-xx)>1 || abs(y-yy)>1)
		return false;
	std::cout << "Ruch mozliwy\n";
	return true;
}

bool Figure :: isQueenMovePossible(int xx, int yy)
{//krolowa
	if(isColorOfTheFigureTheSame(xx,yy))
			return false;
	if(!(x==xx ||y==yy || abs(x-xx)==abs(y-yy)))
		return false;
	if(isFigureBeetweenPoints(x,y,xx,yy))
		return false;
	return true;
}

bool Figure :: isRookMovePossible(int xx, int yy)
{//wieza
	if(isColorOfTheFigureTheSame(xx,yy))
			return false;
	if(!(x==xx ||y==yy))
		return false;
	if(isFigureBeetweenPoints(x,y,xx,yy))
		return false;
	return true;
}

bool Figure :: isKnightMovePossible(int xx, int yy)
{//kon
	cout << "Test koloru dla konia\n";
	if(isColorOfTheFigureTheSame(xx,yy))
			return false;
	cout << "Test krotszych x dla konia\n";
	if (abs(xx-x)==1 && abs(yy-y)==2)
		return true;
	cout << "Test dluzszych x dla konia\n";
	if (abs(xx-x)==2 && abs(yy-y)==1)
		return true;
	cout << "Ruch niemozliwy\n";
	return false;
}

bool Figure :: isBishopMovePossible(int xx, int yy)
{//laufer
	if(isColorOfTheFigureTheSame(xx,yy))
			return false;
	if(!(abs(x-xx)==abs(y-yy)))
		return false;
	if(isFigureBeetweenPoints(x,y,xx,yy))
		return false;
	return true;
}

bool Figure :: isPawnMovePossible(int xx, int yy)
{//pawno
	if(isColorOfTheFigureTheSame(xx,yy))
			return false;
	switch(color)
	{
		case 0:
			{
				if (xx==x && yy==y+1 && board->getFigure(xx,yy)==NULL)
					return true;
				if ((xx==x-1 || xx==x+1) && yy==y+1 && isFigureWithOppositeColor(xx,yy,getColor()))
					return true;
			}
		case 1:
			{
				if (xx==x && yy==y-1 && board->getFigure(xx,yy)==NULL)
					return true;
				if ((xx==x-1 || xx==x+1) && yy==y-1 && isFigureWithOppositeColor(xx,yy,getColor()))
					return true;
			}
		default:{cout << "Error\n"; return false;}
	}
	return true;
}


void Figure::print()
{
	cout << "Typ:" << type << "   x:" << x << "  y:" << y << "   kolor:" << color << "\n";
};