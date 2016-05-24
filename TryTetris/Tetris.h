#pragma once
#ifndef __TETRIS_H_
#define __TETRIS_H_

#pragma comment(lib,"winmm.lib")
#include<time.h>
#include<Windows.h>
#include<iostream>
#include<conio.h>
#include"Brick.h"
using namespace std;
//Keyboard
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACEBAR 32
//Board
#define BOARD_M 20
#define BOARD_N 15
#define BOARD_WIDTH 2
#define BOARD_HEIGHT 2
//BrickStart
#define BRICK_START_X (BOARD_N/2-2)
#define BRICK_START_Y -3
class Tetris
{
private:
	int x, y;
	char board[BOARD_M][BOARD_N];
	Brick brick;
	float gameSpeed;
private:
	void gotoxy(int x, int y);
	void drawBoard();
	void drawBrick(char (*brick)[5]);
	bool IsColision(char(*brick)[5]);
	void CursorView(char show);
public:
	Tetris();
	void Init();
	void Run();
	~Tetris();
};

#endif