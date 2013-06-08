#if !defined _BOARD_H_
#define _BOARD_H_

#include <vector>

class Figure;

class Board
{
private:
	std::vector <Figure*> white;
	std::vector <Figure*> black;
	std::vector <Figure*> szachFigures;
	bool whiteSzachowany;
	bool blackSzachowany;
	bool whiteMatowany;
	bool blackMatowany;

public:
	Board();  //done
	Figure* getFigure(int xx, int yy);  //done
	bool moveTo (int xx, int yy, Figure* fig);  //-----started-----
	bool isWhiteSzachowany();  //done
	bool isBlackSzachowany();  //done
	bool isWhiteMatowany();  //done
	bool isBlackMatowany();  //done
	std::vector<Figure*>* getWhite();  //done
	std::vector<Figure*>* getBlack();  //done
	void removeFigure(int xx, int yy);  //done

	void printFigures(); //done

	bool checkSzach(int color);  //done     //kolor szachujacy
	

private:
	void createFigures();  //done
	bool isFigureOnField(int xx, int yy);  //done
	bool isBlackOnField(int xx, int yy);  //done
	bool isWhiteOnField(int xx, int yy);  //done
	bool fieldExists(int xx, int yy);  //done


	//te do szacha
	
	bool checkSzachOn(int color, int xx, int yy);  //done
	Figure* findKing(int color);  //done  //o podanym kolorze
	

	//te nizej to do mata
	bool checkMat(int color);
	std::vector<Figure*>* getSzachFigures(int xx, int yy, int color);  //xx,yy-pozycja szachowanego krola  color-kolor szachujacych figur
	bool canFigureBeCaptured(int xx, int yy, int color);  //xx,yy-pozycja szachujacej figury  color-kolor szachowanego krola
	bool canKingBeHidden(int xx1, int yy1, int xx2, int yy2, int color);
};

#endif