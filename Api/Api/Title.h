#pragma once
#include"Mode.h"
class Title : public Mode {
public:
	Title(HINSTANCE hInstance, HWND hWnd) :Mode(hInstance,hWnd) {}
	virtual void Initialization();
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);
	virtual void Shutdown();
	virtual void KeyEvent(WPARAM wParam);
	virtual void CommandEvent(WPARAM wParam);
private:
	HBITMAP titleBitmap;
	HWND StartButton , EndButton;
};