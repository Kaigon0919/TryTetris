#include "Tetris.h"
#include<time.h>
void Tetris::Initialization()
{
	m_board = new Board(20, 15);
	m_brick = new Brick();

	beforeBrick = rand() % 7;
	m_brick->Reset(rand() % 7, Point(15 / 2 - 2, -1), 0);
	startPos = Point(10, 10);
	//시간 초기화.
	watingTime = 0;
	nextFrameTime = 1;
	srand((unsigned)time(NULL));
}

void Tetris::Update(float dt)
{
	watingTime += dt;
	if (watingTime >= nextFrameTime && !m_board->IsGameOver()) {
		m_brick->Move(0, 1);
		watingTime = 0; // watingTime -= nextFrameTime.
		inputState = VK_DOWN;
		Coliision();
	}
}

void Tetris::Draw(HWND hWnd, HDC hdc)
{
	HDC MemDC;
	HBITMAP MyBit, OldBit;
	RECT rect;
	GetClientRect(hWnd, &rect);

	MemDC = CreateCompatibleDC(hdc);
	MyBit = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	OldBit = (HBITMAP)SelectObject(MemDC, MyBit);
	FillRect(MemDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	//백버퍼에 그림을 그리기 위해 백버퍼를 넘겨준다.
	m_board->Draw(MemDC, startPos, Margin::x, Margin::y);
	m_brick->Draw(MemDC, startPos, Margin::x, Margin::y);

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBit);
	DeleteObject(MyBit);
	DeleteDC(MemDC);
}

void Tetris::Shutdown()
{
	if (m_board)
		delete m_board;
	if (m_brick)
		delete m_brick;
}

void Tetris::KeyEvent(WPARAM wParam)
{
	if (m_board->IsGameOver())
		return;
	inputState = wParam;
	switch (inputState) {
	case VK_UP:
		m_brick->Rotate(true);
		break;
	case VK_DOWN:
		m_brick->Move(0, 1);
		watingTime = 0;
		break;
	case VK_RIGHT:
		m_brick->Move(1, 0);
		break;
	case VK_LEFT:
		m_brick->Move(-1, 0);
		break;
	case VK_SPACE:
		while (!m_board->IsCollision(m_brick->GetShapeArray(), m_brick->GetPosition()))
			m_brick->Move(0, 1);
		watingTime = 0;
		break;
	}
	Coliision();
}

void Tetris::Coliision()
{
	while (m_board->IsCollision(m_brick->GetShapeArray(), m_brick->GetPosition()) && !m_board->IsGameOver())
	{
		CollisionSolve(inputState);
	}
}

void Tetris::CollisionSolve(WPARAM wParam)
{
	Point pos(m_board->GetCollisionPos());
	switch (inputState)
	{
	case VK_UP:
		m_brick->Move(2 - pos.xpos, 0);
		if (m_board->IsCollision(m_brick->GetShapeArray(), m_brick->GetPosition()))
		{
			m_brick->Rotate(false);
			m_brick->Move(pos.xpos - 2, 0);
		}
		break;
	case VK_RIGHT:
		m_brick->Move(-1, 0);
		break;
	case VK_LEFT:
		m_brick->Move(1, 0);
		break;
	case VK_DOWN: case VK_SPACE: // 위로 한칸 올린 후, 스텍을 쌓고 라인을 체크한다.
		m_brick->Move(0, -1);
		m_board->StackBrick(m_brick->GetShapeArray(), m_brick->GetPosition());
		m_brick->Reset(beforeBrick, Point(15 / 2 - 3, -1), 0);
		beforeBrick = rand() % 7;
		m_board->IsLineFull();
		break;
	}
}
