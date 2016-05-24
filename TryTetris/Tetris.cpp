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
			if (board[i][j] == 3)
			{
				gotoxy(j*BOARD_WIDTH, i);
				cout << "■";
			}
			else if(board[i][j] >0)
			{
				gotoxy(j*BOARD_WIDTH, i);
				cout << "□";
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
				cout << "□";
			}
		}
	}
	gotoxy(0, BOARD_M + 2);
}

bool Tetris::IsColision(char(*brick)[5])
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			cout << (int)board[i + x][j + y];
			if (i + x<0 || i + x>BOARD_N || j + y<0 || j + y>BOARD_M)
				continue;
			if(brick[i][j] + board[i+x][j+y] >3)
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

Tetris::Tetris()
{
	for (int i = 0; i < BOARD_M ; ++i)
	{
		for (int j = 0; j < BOARD_N; ++j)
		{
			board[i][j] = 0;
		}
	}
	for (int i = 0; i < BOARD_M-1; ++i)
	{
		board[i][0] = 3;
		board[i][BOARD_N - 1] = 3;
	}
	for (int i = 0; i < BOARD_N; ++i)
		board[BOARD_M - 1][i] = 3;
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
					//특수
					--y;
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
				//특수
				--y;
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
