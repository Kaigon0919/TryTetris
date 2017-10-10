#pragma once
#ifndef __MYUTIL_H_
#define __MYUTIL_H_
struct Point
{
	int xpos;
	int ypos;

	Point() : xpos(0), ypos(0) {}
	Point(int x, int y) : xpos(x), ypos(y) {}
	Point(const Point & ref) :xpos(ref.xpos), ypos(ref.ypos) {}

	inline void Set(int x, int y) { xpos = x; ypos = y; }
	Point& operator=(const Point& point)
	{
		xpos = point.xpos;
		ypos = point.ypos;
		return *this;
	}
	Point operator+(const Point& point)
	{
		Point temp(xpos + point.xpos, ypos + point.ypos);
		return temp;
	}
	Point operator-(const Point& point)
	{
		Point temp(xpos - point.xpos, ypos - point.ypos);
		return temp;
	}
};

struct MyTime {
	int h;
	int m;
	int s;
};
#endif