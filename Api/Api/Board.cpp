#include "Board.h"
#include<iostream>
Board::Board(int row, int col) : row(row+1), col(col)
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
	for (int i = 0; i < col; ++i)
	{
		if (i < 1 || i >= col-1)
			continue;
		if (board[i][0] >= 3)
			return true;
	}
	return false;
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

void Board::Draw(HDC hdc, Point startPos, float fMarginX, float fMarginY)
{
	//BackGround
	Rectangle(hdc, startPos.xpos - fMarginX*0.2, startPos.ypos - fMarginY*0.2, startPos.xpos + fMarginX*col + fMarginX*0.1, startPos.ypos + fMarginY*(row-1) + fMarginY*0.1);

	RECT rect;
	HBRUSH boardBrush, stackBrush, oldBrush;

	//Brush Setting
	oldBrush = 0;
	boardBrush = CreateSolidBrush(RGB(0, 0, 0));
	stackBrush = CreateSolidBrush(RGB(100, 100, 100));

	//배열의 모든 값을 확인하여, 값에 따라 그림을 그린다. 벽, 쌓인 블럭 :3 , 블록 :1;
	for (int i = 0; i < col; ++i)
	{
		for (int j = 1; j < row; ++j)
		{
			if (i < 0 || j < 1)
				continue;
			if (board[i][j] == 3)
			{
				if (i == 0 || i == col - 1 || j == row - 1)
					(HBRUSH)SelectObject(hdc, boardBrush);
				else
					(HBRUSH)SelectObject(hdc, stackBrush);

				rect.left = i*fMarginX + startPos.xpos;
				rect.top = (j-1)*fMarginY + startPos.ypos;
				rect.right = i*fMarginX + fMarginX *0.9 + startPos.xpos;
				rect.bottom = (j-1)*fMarginY + fMarginY *0.9 + startPos.ypos;
				Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			}
			else if (board[i][j] > 0)
			{
				rect.left = i* fMarginX + startPos.xpos;
				rect.top = (j-1) * fMarginY + startPos.ypos;
				rect.right = i * fMarginX + fMarginX *0.9 + startPos.xpos;
				rect.bottom = (j-1) *fMarginY + fMarginY *0.9 + startPos.ypos;
				Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			}
		}

	}
	//예전의 펜값을 다시 dc에 지정해준다. 
	SelectObject(hdc, oldBrush);
	//쓰고난 펜을 삭제해준다.
	DeleteObject(boardBrush);
	DeleteObject(stackBrush);
	DeleteObject(oldBrush);
}
