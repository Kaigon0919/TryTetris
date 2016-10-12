#include "Draw.h"
using namespace std;

void Draw::Paint(char ** const ref)
{
	int row, col;
	col = _msize(ref) / sizeof(char*); //���� ũ�⸦ üũ.
	row = _msize(ref[0])/ sizeof(char); //���� ũ�⸦ üũ.

	//�迭�� ��� ���� Ȯ���Ͽ�, ���� ���� �׸��� �׸���. ��, ���� �� :3 , ��� :1;
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			if (ref[j][i] == 3)
			{
				gotoxy(j*iMarginX, i * iMarginY);
				cout << "��";
			}
			if (ref[j][i] > 0)
			{
				gotoxy(j*iMarginX, i * iMarginY);
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
