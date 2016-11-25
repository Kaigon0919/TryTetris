#pragma once
#ifndef __TETRISSYSTEM_H_
#define __TETRISSYSTEM_H_

#pragma comment(lib,"winmm.lib")

//std header include
#include<time.h>
#include<Windows.h>
#include<iostream>
#include<conio.h>
//user header include
#include"Draw.h"
#include"Board.h"
#include"Brick.h"
using namespace std;

class TetrisSystem
{
private:
	//ASCII, KeyBoard Number.
	enum KeyBoard { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, SPACEBAR = 32 };
private:
	Board *m_board;
	Brick *m_brick;
	Draw *m_draw;

	KeyBoard input;
	size_t oldTime;

	size_t waitingTime;
private:
	int iMarginX, iMarginY;
	int boardCol, boardRow;
public:
	TetrisSystem();
	~TetrisSystem();
	void Run();
private:
	void MessageProc();
	void Coliision();
	void CollisionSolve();
	void TetrisDraw();
};

#endif