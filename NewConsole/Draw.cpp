#include "Draw.h"

void Draw::Paint(char ** const ref, const Point &pos)
{
	int row, col;
	col = _msize(ref) / sizeof(char*); //행의 크기를 체크.
	row = _msize(ref[0])/ sizeof(char); //열의 크기를 체크.

	//배열의 모든 값을 확인하여, 값에 따라 그림을 그린다. 벽, 쌓인 블럭 :3 , 블록 :1;
	for (int i = 0; i < col; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			if (i + pos.xpos < 0 || j + pos.ypos < 0)
				continue;
			if (ref[i][j] == 3)
			{
				gotoxy((i+pos.xpos)*iMarginX, (j+pos.ypos) * iMarginY);
				cout << "■";
			}
			else if (ref[i][j] > 0)
			{
				gotoxy((i + pos.xpos)*iMarginX, (j + pos.ypos) * iMarginY);
				cout << "□";
			}
		}
	}
}

void Draw::gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Draw::CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
