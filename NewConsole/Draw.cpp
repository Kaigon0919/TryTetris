#include "Draw.h"

void Draw::Paint(char ** const ref, const Point &pos)
{
	int row, col;
	col = _msize(ref) / sizeof(char*); //���� ũ�⸦ üũ.
	row = _msize(ref[0])/ sizeof(char); //���� ũ�⸦ üũ.

	//�迭�� ��� ���� Ȯ���Ͽ�, ���� ���� �׸��� �׸���. ��, ���� �� :3 , ��� :1;
	for (int i = 0; i < col; ++i)
	{
		for (int j = 0; j < row; ++j)
		{
			if (i + pos.xpos < 0 || j + pos.ypos < 0)
				continue;
			if (ref[i][j] == 3)
			{
				gotoxy((i+pos.xpos)*iMarginX, (j+pos.ypos) * iMarginY);
				cout << "��";
			}
			else if (ref[i][j] > 0)
			{
				gotoxy((i + pos.xpos)*iMarginX, (j + pos.ypos) * iMarginY);
				cout << "��";
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
