#include "Draw.h"

void Draw::Paint(char ** const ref, const Point &pos ,HDC hdc)
{
	int row, col;
	col = _msize(ref) / sizeof(char*); //���� ũ�⸦ üũ.
	row = _msize(ref[0])/ sizeof(char); //���� ũ�⸦ üũ.
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
	//�迭�� ��� ���� Ȯ���Ͽ�, ���� ���� �׸��� �׸���. ��, ���� �� :3 , ��� :1;
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
	//������ �氪�� �ٽ� dc�� �������ش�. 
	SelectObject(hdc, oldBrush);
	//���� ���� �������ش�.
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
