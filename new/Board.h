#pragma once
#ifndef __BOARD_H_
#define __BOARD_H_

#include "MyUtil.h"

class Board
{
private:
	char **board;
	size_t row, col;
public:
	Board(int row, int col);
	~Board();
	bool IsCollision(char** const brick, const Point pos);
	bool IsGameOver();
	bool IsLineFull();
	void StackBrick(char** const brick, const Point pos);
	char** GetBoardArray() const {
		return board;
	}
};
#endif