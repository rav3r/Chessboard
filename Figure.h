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
	int getX();  //done
	int getY();  //done
	void setXY(int xx, int yy);  //done
	int getType();  //done
	void print();  //done
	int getColor();  //done
	bool isColorOfTheFigureTheSame(int xx, int yy);  //done

	

private:
	bool isKingMovePossible(int xx, int yy);  //done
	bool isQueenMovePossible(int xx, int yy);
	bool isRookMovePossible(int xx, int yy);
	bool isKnightMovePossible(int xx, int yy);
	bool isBishopMovePossible(int xx, int yy);
	bool isPawnMovePossible(int xx, int yy);
};
 
#endif