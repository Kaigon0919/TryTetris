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