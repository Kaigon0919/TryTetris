#pragma once
#include"Mode.h"
#include"Board.h"
#include"Brick.h"
class Tetris : public Mode {
private:
	Board *m_board;
	Brick *m_brick;
	int beforeBrick;
	float watingTime;
	float nextFrameTime;
	WPARAM inputState;
	bool isPause;
	enum Margin { x = 20, y = 20 };
	Point startPos;
public:
	virtual void Initialization();
	virtual void Update(float dt);
	virtual void Draw(HWND hWnd,HDC hdc);
	virtual void Shutdown();
	virtual void KeyEvent(WPARAM wParam);
private:
	void Coliision();
	void CollisionSolve(WPARAM wParam);
};