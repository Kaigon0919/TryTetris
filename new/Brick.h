#pragma once
#pragma once
#ifndef __BRICK_H_
#define __BRICK_H_

#include "MyUtil.h"

class Brick
{
private:
	char **shape;
	Point position;
	int typeNumber;
	int rotate;
public:
	Brick();
	~Brick();

	//Setter.
	void SetType(const int typeNumber);
	void SetPosition(const Point& position);
	void SetRotate(const int rotate);

	//Getter.
	Point GetPosition() const;
	char** GetShapeArray() const {
		return shape;
	}

	//Funsion.
	void Move(int xpos, int ypos);
	void Rotate();
	void Reset(const int TypeNumber, const Point& pos, const int rot);
private:
	//ShapeBase로부터 도형타입, 회전타입에 따라 값을 복사해오는 함수.
	void SettingArray();
};

const char ShapeBase[7 /*도형갯수*/][4/*회전모양*/][5][5]
{
	//막대 도형.
	{
		{
			{ 0,0,0,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 0,1,1,1,1 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 1,1,1,1,0 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		}
	},
	//ㄱ도형.
	{
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 1,1,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,1,1,0,0 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,1,1 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 0,0,1,1,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,0,0 }
		}
	},
	//ㄱ(반대)도형.
	{
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 0,0,1,1,1 },
			{ 0,0,1,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,1,0 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,1,0,0 },
			{ 1,1,1,0,0 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 0,1,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,0,0 }
		}
	},
	//ㄹ도형.
	{
		{
			{ 0,0,0,0,0 },
			{ 0,1,1,0,0 },
			{ 0,0,1,1,0 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,1,0 },
			{ 0,0,1,1,0 },
			{ 0,0,1,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 0,1,1,0,0 },
			{ 0,0,1,1,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,1,0,0 },
			{ 0,1,1,0,0 },
			{ 0,1,0,0,0 },
			{ 0,0,0,0,0 }
		}
	},
	//ㄹ(반대)도형.
	{
		{
			{ 0,0,0,0,0 },
			{ 0,0,1,1,0 },
			{ 0,1,1,0,0 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,1,0 },
			{ 0,0,0,1,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 0,0,1,1,0 },
			{ 0,1,1,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,1,0,0,0 },
			{ 0,1,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,0,0,0 }
		},
	},
	//ㅗ도형.
	{
		{
			{ 0,0,0,0,0 },
			{ 0,0,1,0,0 },
			{ 0,1,1,1,0 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,1,1,0 },
			{ 0,0,1,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 0,1,1,1,0 },
			{ 0,0,1,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,1,0,0 },
			{ 0,1,1,0,0 },
			{ 0,0,1,0,0 },
			{ 0,0,0,0,0 }
		}
	},
	//ㅁ도형.
	{
		{
			{ 0,0,0,0,0 },
			{ 0,1,1,0,0 },
			{ 0,1,1,0,0 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,1,1,0 },
			{ 0,0,1,1,0 },
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 0,0,1,1,0 },
			{ 0,0,1,1,0 },
			{ 0,0,0,0,0 }
		},
		{
			{ 0,0,0,0,0 },
			{ 0,0,0,0,0 },
			{ 0,1,1,0,0 },
			{ 0,1,1,0,0 },
			{ 0,0,0,0,0 }
		}
	},
};
#endif