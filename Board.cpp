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

void Board::moveTo (int xx, int yy, Figure* fig)
{
	if(fieldExists(xx,yy))
		if(fig!=NULL)
			fig -> moveFigure(xx,yy);
}

void Board::removeFigure(int xx, int yy)
{
	for (int i=0;i<white.size();i++)
		if(white[i]->getX()==xx && white[i]->getY()==yy)
			white.erase(white.begin()+i);
	for (int i=0;i<black.size();i++)
		if(black[i]->getX()==xx && black[i]->getY()==yy)
			black.erase(black.begin()+i);
}


Figure* Board::findKing(int color)
{
	if (color==1)
	{
		for (int i=0; i<white.size(); i++)
			if(white[i]->getType()==0)
				return white[i];
	}
	
	if (color==0)
	{
		for (int i=0;i<black.size();i++)
			if(black[i]->getType()==0)
				return black[i];
	}
	return NULL;


}

bool Board::checkSzachOn(int color, int xx, int yy)
{
	if (color==1)
	{
		for (int i=0;i<white.size(); i++)
		{
			if(white[i]->isMovePossible(xx,yy))
			{
				white[i]-> print();
				return true;
			}
		}
	}
	if (color==0)
	{
		for (int i=0;i<black.size(); i++)
		{
			if(black[i]->isMovePossible(xx,yy))
			{
				black[i] -> print();
				return true;
			}
		}
	}
	return false;
}

bool Board::checkSzach(int color)
{
	int kolorSzachowanegoKrola = abs(color-1);
	cout << "Error check\n";
	Figure* szachowanyKrol = findKing(kolorSzachowanegoKrola);
	szachowanyKrol->print();
	bool czySzach = checkSzachOn(color, szachowanyKrol->getX(), szachowanyKrol->getY());
	return czySzach;
}


void Board::printFigures()
{
	cout <<"\n\n\n";
	for (int i=0;i<white.size();i++)
		cout << white[i]->getX() << ":" << white[i]->getY() << "  " << white[i]->getColor() << "   " << white[i]->getType() << "\n";
	cout <<"\n";
	for (int i=0;i<black.size();i++)
		cout << black[i]->getX() << ":" << black[i]->getY() << "  " << black[i]->getColor() << "   " << black[i]->getType() << "\n";
	cout <<"\n\n\n";
}

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

bool Board::isSzach(){return szach;}
bool Board::isMat(){return mat;}

void Board::createFigures()
{
	white.push_back(new Figure(0,3,7,1,this));
	white.push_back(new Figure(1,4,7,1,this));
	white.push_back(new Figure(2,3,4,1,this));  //wsp 0,7
	white.push_back(new Figure(2,7,7,1,this));
	white.push_back(new Figure(3,2,7,1,this));
	white.push_back(new Figure(3,5,7,1,this));
	white.push_back(new Figure(4,1,7,1,this));
	white.push_back(new Figure(4,6,7,1,this));

	white.push_back(new Figure(5,0,6,1,this));
	white.push_back(new Figure(5,1,6,1,this));
	white.push_back(new Figure(5,2,6,1,this));
	white.push_back(new Figure(5,3,6,1,this));
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
	//black.push_back(new Figure(5,3,1,0,this));
	black.push_back(new Figure(5,4,1,0,this));
	black.push_back(new Figure(5,5,1,0,this));
	black.push_back(new Figure(5,6,1,0,this));
	black.push_back(new Figure(5,7,1,0,this));
};