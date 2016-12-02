#pragma once
#ifndef __BOARD_H_
#define __BOARD_H_

#include "MyUtil.h"

class Board
{
private:
	char **board;
	size_t row, col;
	Point collisionPos;
public:
	Board(int row, int col);
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
};
#endif