#include "Board.h"
#include "Figure.h"

#include <iostream>
#include <cmath>

using namespace std;

Board::Board()
{
	createFigures();
	whiteSzachowany = false;
	blackSzachowany = false;
	whiteMatowany = false;
	blackMatowany = false;
};

Figure* Board::getFigure(int xx, int yy)
{
	for (int i=0; i<black.size(); i++)
		if (black[i]->getX()==xx && black[i]->getY()==yy)
			return black[i];
	for (int i=0; i<white.size(); i++)
		if (white[i]->getX()==xx && white[i]->getY()==yy)
			return white[i];
	return NULL;
}

bool Board::moveTo (int xx, int yy, Figure* fig)
{
	bool movePossible = false;
	if(fieldExists(xx,yy))
		if(fig!=NULL)
			movePossible = fig -> moveFigure(xx,yy);
	whiteSzachowany = checkSzach(0);
	if(whiteSzachowany)
		whiteMatowany = checkMat(0);

	blackSzachowany = checkSzach(1);
	if(blackSzachowany)
		blackMatowany = checkMat(1);
	return movePossible;
}

bool Board::isWhiteSzachowany(){return whiteSzachowany;}
bool Board::isBlackSzachowany(){return blackSzachowany;}
bool Board::isWhiteMatowany(){return whiteMatowany;}
bool Board::isBlackMatowany(){return blackMatowany;}
std::vector<Figure*>* Board::getWhite(){return &white;}
std::vector<Figure*>* Board::getBlack(){return &black;}

void Board::removeFigure(int xx, int yy)
{
	for (int i=0;i<white.size();i++)
		if(white[i]->getX()==xx && white[i]->getY()==yy)
			white.erase(white.begin()+i);
	for (int i=0;i<black.size();i++)
		if(black[i]->getX()==xx && black[i]->getY()==yy)
			black.erase(black.begin()+i);
}

void Board::printFigures()
{
	cout <<"\n\n";
	for (int i=0;i<white.size();i++)
		cout << white[i]->getX() << ":" << white[i]->getY() << "  " << white[i]->getColor() << "   " << white[i]->getType() << "\n";
	cout <<"\n";
	for (int i=0;i<black.size();i++)
		cout << black[i]->getX() << ":" << black[i]->getY() << "  " << black[i]->getColor() << "   " << black[i]->getType() << "\n";
	cout <<"\n\n";
}






void Board::createFigures()
{
	white.push_back(new Figure(0,3,7,1,this));
	white.push_back(new Figure(1,4,7,1,this));
	white.push_back(new Figure(2,3,4,1,this));  //wsp 0,7 - ta wieza szachuje
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
	//white.push_back(new Figure(5,7,6,1,this));

	black.push_back(new Figure(0,3,0,0,this));
	black.push_back(new Figure(1,3,1,0,this)); //wsp 4,0
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

bool Board::isFigureOnField(int xx, int yy)
{
	if (isBlackOnField(xx,yy) || isWhiteOnField(xx,yy))
		return true;
	return false;
}

bool Board::isBlackOnField(int xx, int yy)
{
	for (int i=0; i<black.size(); i++)
		if (black[i]->getX()==xx && black[i]->getY()==yy)
			return true;
	return false;
}

bool Board::isWhiteOnField(int xx, int yy)
{
	for (int i=0; i<white.size(); i++)
		if (white[i]->getX()==xx && white[i]->getY()==yy)
			return true;
	return false;
}

bool Board::fieldExists(int xx, int yy)
{
	if (xx>=0 && xx<=7 && yy>=0 && yy<=7)
		return true;
	return false;
}


bool Board::checkSzach(int color)
{
	int kolorSzachowanegoKrola = std::abs(color-1);
	Figure* szachowanyKrol = findKing(kolorSzachowanegoKrola);
	bool czySzach = checkSzachOn(color, szachowanyKrol->getX(), szachowanyKrol->getY());
	return czySzach;
}

bool Board::checkSzachOn(int color, int xx, int yy)
{
	if (color==1)
		for (int i=0;i<white.size(); i++)
			if(white[i]->isMovePossible(xx,yy))
				return true;
	if (color==0)
		for (int i=0;i<black.size(); i++)
			if(black[i]->isMovePossible(xx,yy))
				return true;
	return false;
}

Figure* Board::findKing(int color)
{
	if (color==1)
		for (int i=0; i<white.size(); i++)
			if(white[i]->getType()==0)
				return white[i];	
	if (color==0)
		for (int i=0;i<black.size();i++)
			if(black[i]->getType()==0)
				return black[i];
	return NULL;
}



bool Board::checkMat(int color)
{
	int kolorSzachowanegoKrola = std::abs(color-1);
	Figure* szachowanyKrol = findKing(kolorSzachowanegoKrola);

	for (int i=szachowanyKrol->getY()-1;i<szachowanyKrol->getY()+2;i++)
		for (int j=szachowanyKrol->getX()-1;j<szachowanyKrol->getX()+2;j++)
		{
			if(i==szachowanyKrol->getY() && j==szachowanyKrol->getX())
				continue;
			if(fieldExists(j,i))
				if(!checkSzachOn(color,j,i))
					if(szachowanyKrol->isMovePossible(j,i))
						return false;
		}
		vector<Figure*> figures = *(getSzachFigures(szachowanyKrol->getX(), szachowanyKrol->getY(), color));
		if(figures.size()==1)
		{
			int szachX = figures[0]->getX();
			int szachY = figures[0]->getY();
			if(canFigureBeCaptured(szachX, szachY, kolorSzachowanegoKrola))
				return false;
			if(figures[0]->getType()!=4)
			{
				//nie kon, mozna probowac zaslaniania
				if (canKingBeHidden(szachowanyKrol->getX(), szachowanyKrol->getY(), szachX, szachY, kolorSzachowanegoKrola))
					return false;
				else
					return true;
			}
			else
				return true;
		}
		if(figures.size()>1)
		{
			cout << "Mat\n";
			return true;
		}
}

std::vector<Figure*>* Board::getSzachFigures(int xx, int yy, int color)  //xx,yy-pozycja szachowanego krola  color-kolor szachujacych figur
{
	szachFigures.clear();
	if (color==0)  //czarne
	{
		for (int i=0;i<black.size();i++)
			if(black[i]->isMovePossible(xx,yy))
				szachFigures.push_back(black[i]);
	}
	if(color==1)  //biale
	{
		for (int i=0;i<white.size();i++)
			if(white[i]->isMovePossible(xx,yy))
				szachFigures.push_back(white[i]);
	}
	return &szachFigures;
}

bool Board::canFigureBeCaptured(int xx, int yy, int color)  //xx,yy-pozycja szachujacej figury  color-kolor szachowanego krola
{
	if(color ==0)
	{
		for (int i=0;i<black.size();i++)
			if(black[i]->isMovePossible(xx,yy))
				return true;
	}
	if(color==1)
	{
		for (int i=0;i<white.size();i++)
			if(white[i]->isMovePossible(xx,yy))
				return true;
	}
	return false;
}

bool Board::canKingBeHidden(int xx1, int yy1, int xx2, int yy2, int color)
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
		cout << figures[i][0] << ":" << figures[i][1] << "\n";
	*/

	//tu sprawdzac, czy mozna jakas figura ruszyc na ktores z pol
	if(color==0) //czarne
	{
		for (int i=0;i<black.size();i++)
			for (int j=0;j<figures.size();j++)
				if(black[i]->isMovePossible(figures[j][0], figures[j][1]))
					return true;
	}
	if(color==1)//biale
	{
		for (int i=0;i<white.size();i++)
			for (int j=0;j<figures.size();j++)
				if(white[i]->isMovePossible(figures[j][0], figures[j][1]))
					return true;
	}
	return false;
}