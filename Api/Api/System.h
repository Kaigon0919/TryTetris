#pragma once

#ifndef __SYSTEMCLASS_H_
#define __SYSTEMCLASS_H_
#include <Windows.h>
#include <sstream>
#include<string>
#include<iostream>
#include<time.h>
using namespace std;

#include"resource.h"
#include"Draw.h"
#include"Board.h"
#include"Brick.h"

#pragma comment(lib,"winmm.lib")
class SystemClass
{
private:
	HWND m_hwnd;
	LPCTSTR m_applicationName;
	HINSTANCE m_hInstance;
private:
	Board *m_board;
	Brick *m_brick;
	Draw *m_draw;
	float curTime;
	float oldTime;
	float waitingTime;
	WPARAM inputState;
public:
	SystemClass();
	SystemClass(const SystemClass &ref);
	~SystemClass();

	bool Initialize();
	void Run();
	void Shutdown();
	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	bool InitializeWindows();
	bool Frame();
private:
	void MessageProc(WPARAM wParam);
	void Coliision();
	void CollisionSolve(WPARAM wParam);
	void TetrisDraw(HDC hdc);

};
static SystemClass * ApplicationHandle = 0;
#endif