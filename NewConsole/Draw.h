#pragma once
#ifndef __DRAW_H_
#define __DRAW_H_

#include <iostream>
#include<Windows.h>
#include"MyUtil.h"
class Draw {
private:
	const int iMarginX;
	const int iMarginY;
public:
	Draw(int marginX, int marginY) : iMarginX(marginX), iMarginY(marginY)
	{	}
	void Paint(char ** const ref, const Point &pos);
	void Clear(){ system("cls"); }
private:
	void gotoxy(int x, int y);
	void CursorView(char show);
};
#endif