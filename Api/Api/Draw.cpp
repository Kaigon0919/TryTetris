#include "Draw.h"

void Draw::Paint(char ** const ref, const Point &pos ,HDC hdc)
{
	int row, col;
	col = _msize(ref) / sizeof(char*); //행의 크기를 체크.
	row = _msize(ref[0])/ sizeof(char); //열의 크기를 체크.
	RECT rect;
	HBRUSH boardBrush, brickBrush, stackBrush, oldBrush;

	//Brush Setting
	oldBrush = 0;
	boardBrush = CreateSolidBrush(RGB(0, 0, 0));
	stackBrush = CreateSolidBrush(RGB(100, 100, 100));
	brickBrush = CreateSolidBrush(RGB(255, 255, 255));

	//Brush Selet
	for (int i = 0; i < col; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			if (ref[i][j] == 3)
			{
				oldBrush = (HBRUSH)SelectObject(hdc, boardBrush);
				break;
			}
			if(ref[i][j] == 1)
			{
				oldBrush = (HBRUSH)SelectObject(hdc, brickBrush);
				break;
			}
		}
		if (oldBrush != 0)
			break;
	}
	//배열의 모든 값을 확인하여, 값에 따라 그림을 그린다. 벽, 쌓인 블럭 :3 , 블록 :1;
	for (int i = 0; i < col; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			if (i + pos.xpos < 0 || j + pos.ypos < 0)
				continue;
			if (ref[i][j] == 3)
			{
				if (i == 0 || i == col - 1 || j == row - 1)
					(HBRUSH)SelectObject(hdc, boardBrush);
				else
					(HBRUSH)SelectObject(hdc, stackBrush);

				rect.left = (i + pos.xpos)*iMarginX + startPos.xpos;
				rect.top = (j + pos.ypos)*iMarginY + startPos.ypos;
				rect.right = (i + pos.xpos)*iMarginX + iMarginX *0.9 + startPos.xpos;
				rect.bottom = (j + pos.ypos)*iMarginY + iMarginY *0.9 + startPos.ypos;
				Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom);

			}
			else if (ref[i][j] > 0)
			{
				rect.left = (i + pos.xpos)*iMarginX + startPos.xpos;
				rect.top = (j + pos.ypos)*iMarginY + startPos.ypos;
				rect.right = (i + pos.xpos)*iMarginX + iMarginX *0.9 + startPos.xpos;
				rect.bottom = (j + pos.ypos)*iMarginY + iMarginY *0.9 + startPos.ypos;
				Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			}
			
		}

	}
	//예전의 펜값을 다시 dc에 지정해준다. 
	SelectObject(hdc, oldBrush);
	//쓰고난 펜을 삭제해준다.
	DeleteObject(boardBrush);
	DeleteObject(stackBrush);
	DeleteObject(brickBrush);
	DeleteObject(oldBrush);
}

void Draw::PaintBackGround(Point pos, HDC hdc)
{
	Rectangle(hdc, startPos.xpos - iMarginX*0.2, startPos.ypos - iMarginY*0.2, startPos.xpos+iMarginX*pos.xpos + iMarginX*0.1, startPos.ypos+iMarginY*pos.ypos + iMarginY*0.1);
}


void Draw::Clear()
{
}
