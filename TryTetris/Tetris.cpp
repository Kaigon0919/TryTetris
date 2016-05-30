#include "Tetris.h"

void Tetris::gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Tetris::drawBoard()
{
	for (int i = 0; i < BOARD_M; ++i)
	{
		for (int j = 0; j < BOARD_N; ++j)
		{
			if (board[j][i] == 3)
			{
				gotoxy(j*BOARD_WIDTH, i);
				cout << "¡á";
			}
			else if(board[j][i] >0)
			{
				gotoxy(j*BOARD_WIDTH, i);
				cout << "¡à";
			}
		}
	}
	cout << endl << endl;
}

void Tetris::drawBrick(char(*brick)[5])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (brick[i][j] == 1 && !(y+j<0))
			{
				gotoxy((x + i)*BOARD_WIDTH, y + j);
				cout << "¡à";
			}
		}
	}
	gotoxy(0, BOARD_M + 2);
}

bool Tetris::IsColision(char(*brick)[5])
{
	for (int i = 0; i < 5; ++i)
	{
		if (i + x < 0)
			continue;
		for (int j = 0; j < 5; ++j)
		{
			if (j + y < 1)
				continue;
			if (brick[i][j] + board[i + x][j + y] > 3)
				return true;
		}
	}
	return false;
}

void Tetris::CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void Tetris::StackBrick(char(*brick)[5])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
			if(brick[i][j] !=0)
				board[x+i][j+y]= 3;
	}
}

void Tetris::LineFull()
{
	bool isLineFull;
	for (int i = BOARD_M-2; i > 0; i--)
	{
		isLineFull = true;
		for (int j = 1; j < BOARD_N - 1; j++)
		{
			if (board[j][i] != 3) {
				isLineFull = false;
				break;
			}
		}
		if (isLineFull)
		{
			for (int z = i; z > 0; z--)
				for (int j = 1; j < BOARD_N - 1; j++)
					board[j][z] = board[j][z - 1];
			i++;
		}
	}
}

Tetris::Tetris()
{
	for (int i = 0; i < BOARD_M ; ++i)
	{
		for (int j = 0; j < BOARD_N; ++j)
		{
			board[i][j] = 0;
		}
	}
	for (int i = 0; i < BOARD_M; ++i)
	{
		board[0][i] = 3;
		board[BOARD_N - 1][i] = 3;
	}
	for (int i = 0; i < BOARD_N; ++i)
		board[i][BOARD_M - 1] = 3;
	drawBoard();
}

void Tetris::Init()
{
	srand((unsigned)time(NULL));
	gameSpeed = 1000.0f;
	CursorView(0);
	x = BRICK_START_X;
	y = BRICK_START_Y;
}

void Tetris::Run()
{
	Init();
	unsigned int oldTime;
	unsigned int deltaTime;
	oldTime = timeGetTime();

	Brick test;
	test.SetBrick(rand()%7);
	int rot = 0;

	drawBrick(test.shape[rot]);
	while (1)
	{
		deltaTime = timeGetTime() - oldTime;
		if (_kbhit())
		{
			char ch = _getch();
			switch (ch) {
			case DOWN:
				++y;
				if (IsColision(test.shape[rot])) {
					//Æ¯¼ö
					--y;
					StackBrick(test.shape[rot]);
					LineFull();
					x = BRICK_START_X;
					y = BRICK_START_Y;
					test.SetBrick(rand() % 7);

				}
				break;
			case RIGHT:
				++x;
				if (IsColision(test.shape[rot])) {
					--x;
				}
				break;
			case LEFT:
				--x;
				if (IsColision(test.shape[rot]))
				{
					++x;
				}
				break;
			case SPACEBAR:
				break;
			case 'z':
				rot = ++rot % 4;
				while(IsColision(test.shape[rot]))
					rot = rot - 1 < 0 ? 4 : rot - 1;
				break;
			case 'd':
				x = BRICK_START_X;
				y = BRICK_START_Y;
				test.SetBrick(rand() % 7);
				break;
			}
			system("cls");
			drawBoard();
			drawBrick(test.shape[rot]);
		}
		if (deltaTime > gameSpeed)
		{
			y++;
			if (IsColision(test.shape[rot])) {
				--y;
				StackBrick(test.shape[rot]);
				LineFull();
				x = BRICK_START_X;
				y = BRICK_START_Y;
				test.SetBrick(rand() % 7);
			}
			oldTime = timeGetTime();
			system("cls");
			drawBoard();
			drawBrick(test.shape[rot]);
		}
	}

}

Tetris::~Tetris()
{
}
