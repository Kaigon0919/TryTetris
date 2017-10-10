#include "Title.h"

void Title::Initialization()
{
	titleBitmap = LoadBitmap(GethInstance(), MAKEINTRESOURCE(IDB_BITMAP1));

	HWND hWnd = GetHWnd();
	RECT rect;
	GetClientRect(hWnd, &rect);
	StartButton = CreateWindow(TEXT("button"), TEXT("Start"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (rect.right - rect.left)/2 - (300/2) , (rect.bottom - rect.top)*0.6, 300, 50, hWnd, (HMENU)0, GethInstance(), NULL);
	EndButton = CreateWindow(TEXT("button"), TEXT("Exit"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, (rect.right - rect.left) / 2 - (300 / 2), (rect.bottom - rect.top)*0.6 + 70, 300, 50, hWnd, (HMENU)1, GethInstance(), NULL);
}

void Title::Update(float dt)
{
}

void Title::Draw(HDC hdc)
{
	HDC MemDC, BackDC;
	HBITMAP MyBit, OldBit;
	RECT rect;
	HWND hWnd = GetHWnd();

	GetClientRect(hWnd, &rect);


	MemDC = CreateCompatibleDC(hdc);
	//백버퍼 클리어.
	MyBit = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	OldBit = (HBITMAP)SelectObject(MemDC, MyBit);
	FillRect(MemDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	//백버퍼에 그림.
	DrawImage(MemDC, (rect.right - rect.left)*0.125, (rect.bottom - rect.top)/100 * 10, titleBitmap);


	//프론트에 복사.
	BitBlt(hdc, 0, 0, rect.right, rect.bottom, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBit);
	DeleteObject(MyBit);
	DeleteDC(MemDC);
}

void Title::Shutdown()
{
	DeleteObject(titleBitmap);
	DestroyWindow(StartButton);
	DestroyWindow(EndButton);
}

void Title::KeyEvent(WPARAM wParam)
{
	switch (wParam)
	{
	case 'R':
		ChangeState(1);
		break;
	}
}

void Title::CommandEvent(WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case 0:
		ChangeState(1);
		break;
	case 1: case ID_FILE_40002:
		SendMessage(GetHWnd(), WM_DESTROY, 0, 0);
		break;
	}
}

