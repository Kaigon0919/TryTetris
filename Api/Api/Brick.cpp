#include "Brick.h"
#include<iostream>
Brick::Brick() : rotate(0), typeNumber(0)
{
	shape = new char*[5];
	for (int i = 0; i < 5; ++i)
	{
		shape[i] = new char[5];
	}
	SettingArray();
}
Brick::~Brick()
{
	for (int i = 0; i < _msize(shape) / sizeof(char*); ++i)
	{
		delete[] (shape[i]);
	}
	delete[] shape;
}

void Brick::SetRotate(int rotate)
{
	this->rotate= rotate%4;
	SettingArray();
}

void Brick::SetType(int typeNumber)
{
	this->typeNumber = typeNumber;
	SettingArray();
}

void Brick::SetPosition(const Point & position)
{
	this->position.xpos = position.xpos;
	this->position.ypos = position.ypos;
}

void Brick::Move(int xpos, int ypos)
{
	position.xpos += xpos;
	position.ypos += ypos;
}

void Brick::Rotate(bool clockwise)
{
	if (clockwise) ++rotate;
	else
	{
		--rotate;
		if (rotate < 0)
		{
			rotate = 4 - rotate;
		}
	}
	rotate %= 4;
	SettingArray();

}

void Brick::Reset(const int TypeNumber, const Point & pos, const int rot)
{
	SetType(TypeNumber);
	SetPosition(pos);
	SetRotate(rot);
}

void Brick::Draw(HDC hdc, Point startPos, float fMarginX, float fMarginY)
{
	RECT rect;
	HBRUSH brickBrush, oldBrush;

	//Brush Setting
	oldBrush = 0;
	brickBrush = CreateSolidBrush(RGB(255, 255, 255));
	oldBrush = (HBRUSH)SelectObject(hdc, brickBrush);

	//Draw
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i + position.xpos < 0 || j + position.ypos-1 < 0)
				continue;
			if (shape[i][j] > 0)
			{
				rect.left = (i + position.xpos)*fMarginX + startPos.xpos;
				rect.top = (j + position.ypos-1)*fMarginY + startPos.ypos;
				rect.right = (i + position.xpos)*fMarginX + fMarginX *0.9 + startPos.xpos;
				rect.bottom = (j + position.ypos-1)*fMarginY + fMarginY *0.9 + startPos.ypos;
				Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			}
		}
	}
	//예전의 펜값을 다시 dc에 지정해준다. 
	SelectObject(hdc, oldBrush);
	//쓰고난 펜을 삭제해준다.
	DeleteObject(brickBrush);
	DeleteObject(oldBrush);
}

Point Brick::GetPosition() const
{
	return position;
}

void Brick::SettingArray()
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			shape[i][j] = ShapeBase[typeNumber][rotate][i][j];
	}
}