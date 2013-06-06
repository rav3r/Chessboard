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
	void moveTo (int xx, int yy, Figure* fig);  //-----started-----
	bool isSzach();  //done
	bool isMat();  //done
	std::vector<Figure*>* getWhite();  //done
	std::vector<Figure*>* getBlack();  //done
	void removeFigure(int xx, int yy);  //done

	void printFigures(); //done

	
	

private:
	void createFigures();  //done
	bool isFigureOnField(int xx, int yy);  //done
	bool isBlackOnField(int xx, int yy);  //done
	bool isWhiteOnField(int xx, int yy);  //done
	bool fieldExists(int xx, int yy);  //done


	//te do szacha
	bool checkSzach(int color);  //done     //kolor szachujacy
	bool checkSzachOn(int color, int xx, int yy);  //done
	Figure* findKing(int color);  //done
	

	//te nizej to do mata
	bool checkMat(int color);
	std::vector<Figure*>* getSzachFigures();
	bool canFighPreventFromMat();
	bool canKingBeHidden();
};

#endif