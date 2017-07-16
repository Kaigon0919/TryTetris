#include "Title.h"

void Title::Initialization()
{
}

void Title::Update(float dt)
{
}

void Title::Draw(HWND hWnd, HDC hdc)
{
	HDC MemDC;
	HBITMAP MyBit, OldBit;
	RECT rect;
	GetClientRect(hWnd, &rect);

	MemDC = CreateCompatibleDC(hdc);
	MyBit = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	OldBit = (HBITMAP)SelectObject(MemDC, MyBit);
	FillRect(MemDC, &rect, (HBRUSH)GetStockObject(GRAY_BRUSH));

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBit);
	DeleteObject(MyBit);
	DeleteDC(MemDC);
}

void Title::Shutdown()
{
}

void Title::KeyEvent(WPARAM wParam)
{
}
