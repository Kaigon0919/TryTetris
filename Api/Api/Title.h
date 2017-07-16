#pragma once
#include"Mode.h"
class Title : public Mode {
public:
	virtual void Initialization();
	virtual void Update(float dt);
	virtual void Draw(HWND hWnd, HDC hdc);
	virtual void Shutdown();
	virtual void KeyEvent(WPARAM wParam);
};