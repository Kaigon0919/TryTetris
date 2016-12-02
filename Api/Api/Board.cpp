#include "Board.h"
#include<iostream>
Board::Board(int row, int col) : row(row), col(col)
{
	board = new char*[col];
	for (int i = 0; i < col; ++i)
	{
		board[i] = new char[row];
	}
	Init();
}

Board::~Board()
{
	for (int i = 0; i < _msize(board) / sizeof(char*); ++i)
	{
		delete[] board[i];
	}
	delete[] board;
}

bool Board::Init()
{
	// 모든 배열의 값을 0으로 초기화.
	for (int i = 0; i < col; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			board[i][j] = 0;
		}
	}
	// 벽을 표시.
	for (int i = 0; i < row; ++i)
	{
		board[0][i] = 3;
		board[col - 1][i] = 3;
	}
	for (int i = 0; i < col; ++i)
		board[i][row - 1] = 3;
	return false;
}

bool Board::IsCollision(char** const brick, const Point pos)
{
	for (int i = 0; i < 5; ++i)
	{
		if (i + pos.xpos < 0 || i + pos.xpos >= col)
			continue;
		for (int j = 0; j < 5; ++j)
		{
			if (j + pos.ypos < 0 || j + pos.ypos > row)
				continue;
			if (brick[i][j] + board[i + pos.xpos][j + pos.ypos] > 3)
			{
				//충돌이 난 블록배열의 위치 저장.
				collisionPos.Set(i, j);
				return true;
			}
		}
	}
	return false;
}

Point Board::GetCollisionPos() const
{
	return collisionPos;
}

bool Board::IsGameOver()
{
	return board[col / 2][0] >= 3;
}

bool Board::IsLineFull()
{
	bool isLineFull;
	for (int i = row - 2; i > 0; i--)
	{
		isLineFull = true;
		for (int j = 1; j < col - 1; j++)
		{
			if (board[j][i] != 3) {
				isLineFull = false;
				break;
			}
		}
		if (isLineFull)
		{
			for (int z = i; z > 0; z--)
				for (int j = 1; j < col - 1; j++)
					board[j][z] = board[j][z - 1];
			i++;
		}
	}
	return isLineFull;
}

void Board::StackBrick(char ** const brick, const Point pos)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i + pos.xpos < 0 || i + pos.xpos >= col || j + pos.ypos < 0 || j + pos.ypos >= row)
				continue;
			if (brick[i][j] != 0)
				board[i + pos.xpos][j + pos.ypos] = 3;
		}
	}
}
