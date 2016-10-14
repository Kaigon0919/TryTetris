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
				cout << "бс";
			}
			else if(board[j][i] >0)
			{
				gotoxy(j*BOARD_WIDTH, i);
				cout << "бр";
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
				cout << "бр";
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
			if (j + y < 0)
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

bool Tetris::IsGameOver()
{
	return board[BOARD_N / 2][0] == 3;
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

	Brick brick;
	brick.SetBrick(rand()%7);
	int rot = 0;

	drawBrick(brick.shape[rot]);
	while (!IsGameOver())
	{
		deltaTime = timeGetTime() - oldTime;
		if (_kbhit())
		{
			char ch = _getch();
			switch (ch) {
			
			case DOWN:
				++y;
				if (IsColision(brick.shape[rot])) {
					--y;
					StackBrick(brick.shape[rot]);
					LineFull();
					x = BRICK_START_X;
					y = BRICK_START_Y;
					brick.SetBrick(rand() % 7);

				}
				break;
			case RIGHT:
				++x;
				if (IsColision(brick.shape[rot])) {
					--x;
				}
				break;
			case LEFT:
				--x;
				if (IsColision(brick.shape[rot]))
				{
					++x;
				}
				break;
			case SPACEBAR:
				while (!IsColision(brick.shape[rot]))
				{
					++y;
				}
				y--;
				StackBrick(brick.shape[rot]);
				LineFull();
				x = BRICK_START_X;
				y = BRICK_START_Y;
				brick.SetBrick(rand() % 7);
				break;
			case UP:
				rot = ++rot % 4;
				while(IsColision(brick.shape[rot]))
					rot = rot - 1 < 0 ? 4 : rot - 1;
				break;
			case 'd':
				x = BRICK_START_X;
				y = BRICK_START_Y;
				brick.SetBrick(rand() % 7);
				break;
			}
			if (IsGameOver())
				return;
			system("cls");
			drawBoard();
			drawBrick(brick.shape[rot]);
		}
		if (deltaTime > gameSpeed)
		{
			y++;
			if (IsColision(brick.shape[rot])) {
				--y;
				StackBrick(brick.shape[rot]);
				LineFull();
				x = BRICK_START_X;
				y = BRICK_START_Y;
				brick.SetBrick(rand() % 7);
			}
			oldTime = timeGetTime();
			system("cls");
			drawBoard();
			drawBrick(brick.shape[rot]);
		}
	}

}

Tetris::~Tetris()
{
}
