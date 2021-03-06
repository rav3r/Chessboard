#if !defined _FIGURE_H_
#define _FIGURE_H_

class Board;

class Figure
{
private:
	int x;
	int y;
	int type; //0-krol  1-krolowa  2-wieza  3-laufer  4-kon  5-pionek
	int color; //0-czarne, 1-biale
	Board* board;

public:
	Figure(int _type, int _x, int _y, int c, Board* b); //done
	bool moveFigure(int xx, int yy);  //done
	bool isMovePossible(int xx, int yy);
	int getX();  //done
	int getY();  //done
	int getType();  //done
	int getColor();  //done
	
	void print();  //done

private:
	bool isKingMovePossible(int xx, int yy);  //done
	bool isQueenMovePossible(int xx, int yy);  //done
	bool isRookMovePossible(int xx, int yy);  //done
	bool isKnightMovePossible(int xx, int yy);  //done
	bool isBishopMovePossible(int xx, int yy);  //done
	bool isPawnMovePossible(int xx, int yy);  //done

	bool isColorOfTheFigureTheSame(int xx, int yy);  //done
	bool isFigureWithOppositeColor(int xx, int yy, int color);  //done    //color - podac kolor, do ktorego ma byc przeciwny
	bool isFigureBeetweenPoints(int xx1, int yy1, int xx2, int yy2);  //done  //tam pewnie trzeba usuwac pamiec na koniec...
	bool temporaryMove(int befX, int befY, int aftX, int aftY);
};
 
#endif