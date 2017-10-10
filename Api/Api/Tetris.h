#pragma once
#include"Mode.h"
#include"Board.h"
#include"Brick.h"
class Tetris : public Mode {
private:
	Board *m_board;
	Brick *m_brick;
	Brick *m_afterBrick;
	int beforeBrick;

	float watingTime;
	float nextFrameTime;
	float playTime;
	MyTime beforePlayTime;

	WPARAM inputState;
	bool isPause;

	enum Margin { x = 20, y = 20 };
	Point startPos;

	HWND ReGameButton;
	HWND EndButton;
	HWND PauseButton;
	HWND PlayTimeStatic;
	
	HBITMAP GameOverBitmap;
public:
	Tetris(HINSTANCE hInstance,HWND hWnd) :Mode(hInstance,hWnd) {}
	virtual void Initialization();
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);
	virtual void Shutdown();
	virtual void KeyEvent(WPARAM wParam);
	virtual void CommandEvent(WPARAM wParam);
private:
	void Coliision();
	void CollisionSolve(WPARAM wParam);
	void AfterBrick(HDC hdc, const Point& position);

	void DrawPlayTime();
};