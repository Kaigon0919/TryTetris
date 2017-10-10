#include "Board.h"
Board::Board()
{

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

	/* ���� �Է� */
	ifstream fin;
	fin.open("stage1.txt");
	string tempStr;
	char tempChar;
	fin >> tempStr >> tempChar;
	fin >> row;
	fin >> tempStr >> tempChar;
	fin >> col;

	// ���� �Ҵ�.
	board = new char*[this->col];
	for (int i = 0; i < this->col; ++i)
	{
		board[i] = new char[this->row];
	}

	// ���� ����.
	char inputData = 0;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			fin >> inputData;
			board[j][i] = inputData-48;
		}
	}
	fin.close();
	return true;
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
				//�浹�� �� ��Ϲ迭�� ��ġ ����.
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
		if (i < 1 || i >= col - 1)
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
	Rectangle(hdc, startPos.xpos - fMarginX*0.2, startPos.ypos - fMarginY*0.2, startPos.xpos + fMarginX*col + fMarginX*0.1, startPos.ypos + fMarginY*(row - 1) + fMarginY*0.1);

	RECT rect;
	HBRUSH boardBrush, stackBrush, oldBrush;

	//Brush Setting
	oldBrush = 0;
	boardBrush = CreateSolidBrush(RGB(0, 0, 0));
	stackBrush = CreateSolidBrush(RGB(100, 100, 100));

	//�迭�� ��� ���� Ȯ���Ͽ�, ���� ���� �׸��� �׸���. ��, ���� �� :3 , ��� :1;
	for (int i = 0; i < col; ++i)
	{
		for (int j = 1; j < row; ++j)
		{
			if (i < 0 || j < 1)
				continue;
			if (board[i][j] == 3)
			{
				if (i == 0 || i == col - 1 || j == row - 1)
					oldBrush = (HBRUSH)SelectObject(hdc, boardBrush);
				else
					oldBrush = (HBRUSH)SelectObject(hdc, stackBrush);

				rect.left = i*fMarginX + startPos.xpos;
				rect.top = (j - 1)*fMarginY + startPos.ypos;
				rect.right = i*fMarginX + fMarginX *0.9 + startPos.xpos;
				rect.bottom = (j - 1)*fMarginY + fMarginY *0.9 + startPos.ypos;
				Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			}
			else if (board[i][j] > 0)
			{
				rect.left = i* fMarginX + startPos.xpos;
				rect.top = (j - 1) * fMarginY + startPos.ypos;
				rect.right = i * fMarginX + fMarginX *0.9 + startPos.xpos;
				rect.bottom = (j - 1) *fMarginY + fMarginY *0.9 + startPos.ypos;
				Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			}
		}

	}
	//������ �氪�� �ٽ� dc�� �������ش�. 
	SelectObject(hdc, oldBrush);
	//���� ���� �������ش�.
	DeleteObject(boardBrush);
	DeleteObject(stackBrush);
	DeleteObject(oldBrush);
}
