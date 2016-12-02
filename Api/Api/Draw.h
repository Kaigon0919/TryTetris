#pragma once
#ifndef __DRAW_H_
#define __DRAW_H_

#include <iostream>
#include<Windows.h>
#include"MyUtil.h"
using namespace std;

class Draw {
private:
	const int iMarginX;
	const int iMarginY;
	Point startPos;
public:
	Draw(Point StartPoint, int marginX, int marginY) :startPos(StartPoint), iMarginX(marginX), iMarginY(marginY)
	{	}
	void Paint(char ** const ref, const Point &pos, HDC hdc);
	void PaintBackGround(Point pos, HDC hdc);
	void Clear();
};
#endif