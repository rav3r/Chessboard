#if !defined _FIGURE_H_
#define _FIGURE_H_
 
class Figure
{
private:
	int x;
	int y;
	int type; //0-krol  1-krolowa  2-wieza  3-laufer  4-kon  5-pionek
public:
	Figure(int _type, int _x, int _y);

	bool moveFigure(int xx, int yy);

	int getX();
	int getY();
	void setXY(int xx, int yy);
	int getType();

private:
	bool isKingMovePossible(int xx, int yy);
	bool isQueenMovePossible(int xx, int yy);
	bool isRookMovePossible(int xx, int yy);
	bool isKnightMovePossible(int xx, int yy);
	bool isBishopMovePossible(int xx, int yy);
	bool isPawnMovePossible(int xx, int yy);
};
 
#endif