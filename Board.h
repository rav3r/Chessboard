#if !defined _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "Figure.h"

class Board
{
private:
	std::vector <Figure*> white;
	std::vector <Figure*> black;
	bool szach;
	bool mat;

public:
	Board();
	Figure* getFigure(int xx, int yy);
	void moveTo (int xx, int yy, Figure* fig);
	bool isSzach();
	bool isMat();
	std::vector<Figure*>* getWhite();
	std::vector<Figure*>* getBlack();


private:
	bool checkSzach();
	bool checkMat();
	Figure* findKing();
	bool checkSzachOn(int xx, int yy);
	std::vector<Figure*> getSzachFigures();
	bool canFighPreventFromMat();
	bool canKingBeHidden();
	void createFigures();

};

#endif