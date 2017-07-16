#pragma once
#include "MyUtil.h"
#include<Windows.h>
class Board
{
private:
	char **board;
	size_t row, col;
	Point collisionPos;
public:
	Board::Board(int row, int col);
	~Board();
	bool Init();
	bool IsCollision(char** const brick, const Point pos);
	Point GetCollisionPos()const;
	bool IsGameOver();
	bool IsLineFull();
	void StackBrick(char** const brick, const Point pos);
	char** GetBoardArray() const {
		return board;
	}
	Point GetColRow() const { return Point(col, row); }

	void Draw(HDC hdc, Point startPos, float fMarginX, float fMarginY);
};