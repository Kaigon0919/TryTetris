#pragma once
#include<Windows.h>
class Mode {
public:
	virtual void Initialization() =0;
	virtual void Update(float dt) = 0;
	virtual void Draw(HWND hWnd,HDC hdc) = 0;
	virtual void Shutdown() = 0;
	virtual void KeyEvent(WPARAM wParam) { /*empty*/ };
};