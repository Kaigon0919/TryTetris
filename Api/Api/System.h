#pragma once

#ifndef __SYSTEMCLASS_H_
#define __SYSTEMCLASS_H_
#include <Windows.h>
#include <sstream>
#include<string>
#include<iostream>
#include<time.h>
#include<vector>
using namespace std;

#include"resource.h"
#include"Tetris.h"
#include"Title.h"

#pragma comment(lib,"winmm.lib")
class SystemClass
{
private:
	HWND m_hwnd;
	LPCTSTR m_applicationName;
	HINSTANCE m_hInstance;

	vector<Mode*> m_Mode;
	int stateNum;
private:
	float curTime;
	float oldTime;
	bool isPause;
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

};
static SystemClass * ApplicationHandle = 0;
#endif