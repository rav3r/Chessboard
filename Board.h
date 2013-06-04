#if !defined _BOARD_H_
#define _BOARD_H_

#include <vector>

class Figure;

class Board
{
private:
	std::vector <Figure*> white;
	std::vector <Figure*> black;
	bool szach;
	bool mat;

public:
	Board();  //done
	Figure* getFigure(int xx, int yy);  //done
	void moveTo (int xx, int yy, Figure* fig);
	bool isSzach();
	bool isMat();
	std::vector<Figure*>* getWhite();  //done
	std::vector<Figure*>* getBlack();  //done

private:
	void createFigures();  //done
	bool isFigureOnField(int xx, int yy);  //done
	bool isBlackOnField(int xx, int yy);  //done
	bool isWhiteOnField(int xx, int yy);  //done
	bool fieldExists(int xx, int yy);  //done
	bool checkSzach();
	bool checkMat();
	Figure* findKing();
	bool checkSzachOn(int xx, int yy);
	std::vector<Figure*> getSzachFigures();
	bool canFighPreventFromMat();
	bool canKingBeHidden();
};

#endif