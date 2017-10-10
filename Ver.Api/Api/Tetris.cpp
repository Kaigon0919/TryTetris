#include "Tetris.h"
#include<time.h>
#include<cstring>
void Tetris::Initialization()
{
	m_board = new Board();
	m_brick = new Brick();
	m_afterBrick = new Brick();

	//����, ���, ���� ��� �ʱ�ȭ.
	m_board->Init();
	m_afterBrick->Reset(rand() % 7, Point(0, 0), 0);
	m_brick->Reset(rand() % 7, Point(15 / 2 - 2, -1), 0);
	startPos = Point(10, 10);

	//�ð� �ʱ�ȭ.
	watingTime = 0;
	playTime = 0;
	nextFrameTime = 1;
	srand((unsigned)time(NULL));
	isPause = false;

	HWND hWnd = GetHWnd();
	RECT rect;
	GetClientRect(hWnd, &rect);
	int x = 315;
	int y = 285;
	ReGameButton = CreateWindow(TEXT("button"), TEXT("ReGame"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y, 100, 50, hWnd, (HMENU)0, GetHInstance(), NULL);
	EndButton = CreateWindow(TEXT("button"), TEXT("Exit"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y + 55, 100, 50, hWnd, (HMENU)1, GetHInstance(), NULL);
	PauseButton = CreateWindow(TEXT("button"), TEXT("Pause"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y - 55, 100, 50, hWnd, (HMENU)2, GetHInstance(), NULL);
	PlayTimeStatic = CreateWindow(TEXT("static"),TEXT("0�� 0�� 0��"), WS_CHILD | WS_VISIBLE , x, 110, 100, 30, hWnd, (HMENU)-1, GetHInstance(), NULL);

	GameOverBitmap = LoadBitmap(GetHInstance(), MAKEINTRESOURCE(IDB_BITMAP2));
}

void Tetris::Update(float dt)
{
	// ���� ���� Ȥ�� ���� ���� �� Update�� ó������ �ʽ��ϴ�.
	if (isPause || m_board->IsGameOver())
		return;

	watingTime += dt;

	// ������ ����, ���׵� ���� ���� dt�� Ŀ������ �÷���Ÿ���� Ŀ���� �ʰ� ����.
	if (dt > nextFrameTime)
		playTime += nextFrameTime;
	else
		playTime += dt;

	// �÷���Ÿ���� ǥ��.
	DrawPlayTime();
	
	if (watingTime >= nextFrameTime) {
		m_brick->Move(0, 1);
		watingTime = 0; // dt�� Ŭ ��� �������� ������ �޶����� �ʰ� 0���� ����. 
		inputState = VK_DOWN;
		Coliision();
	}
}

void Tetris::Draw(HDC hdc)
{
	HDC MemDC;
	HBITMAP MyBit, OldBit;
	RECT rect;
	HWND hWnd = GetHWnd();
	GetClientRect(hWnd, &rect);

	MemDC = CreateCompatibleDC(hdc);
	MyBit = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	OldBit = (HBITMAP)SelectObject(MemDC, MyBit);
	FillRect(MemDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	//����ۿ� �׸��� �׸��� ���� ����۸� �Ѱ��ش�.
	m_board->Draw(MemDC, startPos, Margin::x, Margin::y);
	m_brick->Draw(MemDC, startPos, Margin::x, Margin::y);
	AfterBrick(MemDC, Point(startPos.xpos + Margin::x * 15 + 5, startPos.ypos - Margin::y*0.2));

	// ���� ������ ��� ���ӿ����� �׷��ݴϴ�.
	if (m_board->IsGameOver())
		DrawImage(MemDC, 0, (rect.bottom - rect.top) / 2 - 90, GameOverBitmap);

	// ����ۿ� �׸� �׸��� ȭ�鿡 ����մϴ�.
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

	DestroyWindow(ReGameButton);
	DestroyWindow(EndButton);
	DestroyWindow(PlayTimeStatic);
	DestroyWindow(PauseButton);
}

void Tetris::KeyEvent(WPARAM wParam)
{
	if (m_board->IsGameOver() || isPause)
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
	case VK_DOWN: case VK_SPACE: // ���� ��ĭ �ø� ��, ������ �װ� ������ üũ�Ѵ�.
		m_brick->Move(0, -1);
		m_board->StackBrick(m_brick->GetShapeArray(), m_brick->GetPosition());
		m_brick->Reset(m_afterBrick->GetTypeNumber(), Point(15 / 2 - 3, -1), 0);
		m_afterBrick->Reset(rand() % 7, Point(0, 0), 0);
		m_board->IsLineFull();
		break;
	}
}

void Tetris::AfterBrick(HDC hdc, const Point& position)
{
	Rectangle(hdc, position.xpos, position.ypos, position.xpos + Margin::x * 5, position.ypos + Margin::y * 5);
	Point afterPos(position.xpos, position.ypos + 14);
	m_afterBrick->Draw(hdc, afterPos, Margin::x, Margin::y);
}

void Tetris::DrawPlayTime()
{
	int h = static_cast<int>(playTime / 3600);
	int m = static_cast<int>(playTime / 60) % 60;
	int s = static_cast<int>(playTime) % 60;
	if (beforePlayTime.s != s)
	{
		wstring pt = to_wstring(h) + L"�� " + to_wstring(m) + L"�� " + to_wstring(s) + L"��";
		SetWindowText(PlayTimeStatic, pt.c_str());
		beforePlayTime = { h,m,s };
	}
}

void Tetris::CommandEvent(WPARAM wParam)
{
	switch (LOWORD(wParam))
	{

	case 0:	case ID_FILE_40001:
		ChangeState(1);
		break;
	case 1: case ID_FILE_40002:
		SendMessage(GetHWnd(), WM_DESTROY, 0, 0);
		break;
	case 2 :
		isPause = isPause ? false : true;
		if(isPause)
			SetWindowText(PauseButton, L"ReStart");
		else
			SetWindowText(PauseButton, L"Pause");
		SetFocus(GetHWnd());
		break;
	case ID_FILE_40003:
		ChangeState(0);
		break;
	}
}