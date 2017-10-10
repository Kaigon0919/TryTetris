#pragma once
#include<Windows.h>
#include"resource.h"

class Mode {
private:
	bool isNewState;
	int afterState;
	HINSTANCE hInstance;
	HWND hWnd;
protected:
	const HINSTANCE GetHInstance()const {
		return hInstance;
	}
	const HWND GetHWnd()const {
		return hWnd;
	}
public:
	Mode(HINSTANCE hInstance, HWND hWnd) :hInstance(hInstance), hWnd(hWnd), isNewState(false) {	}
	virtual void Initialization() = 0;
	virtual void Update(float dt) = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Shutdown() = 0;
	virtual void CommandEvent(WPARAM wParam) {};
	virtual void KeyEvent(WPARAM wParam) { /*empty*/ };

	inline int GetNewState() {
		if (isNewState) {
			return afterState;
		}
		return -1;
	}
	inline void SetNewState(bool bValue) {
		isNewState = false;
	}
	inline void ChangeState(int idx) {
		isNewState = true;
		afterState = idx;
	}
	void DrawImage(HDC hdc, int x, int y, HBITMAP bitmap){
		HBITMAP oldBitmap;
		HDC MemDC = CreateCompatibleDC(hdc);
		oldBitmap = (HBITMAP)SelectObject(MemDC, bitmap);

		BITMAP bit;
		GetObject(bitmap, sizeof(BITMAP), &bit);
		int bx = bit.bmWidth;
		int by = bit.bmHeight;

		BitBlt(hdc, x, y, bx, by, MemDC, 0, 0, SRCCOPY);

		SelectObject(MemDC, oldBitmap);
		DeleteDC(MemDC);
	}
};