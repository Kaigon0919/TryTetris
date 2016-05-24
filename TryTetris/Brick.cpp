#include "Brick.h"

void Brick::SetBrick(int typeNum)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			for (int k = 0; k < 5; ++k)
			{
				shape[i][j][k] = ShapeBase[typeNum][i][j][k];
			}
		}
	}
}

