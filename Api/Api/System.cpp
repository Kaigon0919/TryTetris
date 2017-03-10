#include "System.h"
SystemClass::SystemClass()
{
	m_board = new Board(20, 15);
	m_brick = new Brick();
	m_draw = new Draw(Point(10,10),20, 20);
	srand((unsigned)time(NULL));
	isPause = false;
}

SystemClass::SystemClass(const SystemClass & ref)
{
}

SystemClass::~SystemClass()
{

}

bool SystemClass::Initialize()
{
	if (!InitializeWindows())
		return false;
	// First Brick Set.
	m_brick->Reset(rand() % 7, Point(15 / 2 - 2, -2), 0);
	curTime = oldTime = (float)timeGetTime() * 0.001;
	waitingTime = 1.5f;
	return true;
}

void SystemClass::Run()
{
	MSG Message;
	bool done = false;
	ZeroMemory(&Message, sizeof(Message));


	while (!done)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			//�޼����� ���� �Ͻ� �ݺ����� Ż��. �ش� ó���� ������ WndProc���� â�� ���ֵ� ���α׷��� �����ְ� �ȴ�.
			if (Message.message == WM_QUIT)
				done = true;
			else { // �ƴҽ� �޼��� ó��.
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
		else
			Frame();// �޼����� ��� ��� ó���ؾ��� �Լ�.

	}
}

void SystemClass::Shutdown()
{
	if (m_board)
		delete m_board;
	if (m_brick)
		delete m_brick;
	if (m_draw)
		delete m_draw;
}

bool SystemClass::InitializeWindows()
{
	// WndProc���� �ش� ��ü�� ���� �����ϰ� static �����Ϳ� �ش� ��ü�� �ѱ�.
	ApplicationHandle = this;

	WNDCLASS WndClass;

	// ���α׷� �̸� ����.
	m_applicationName = TEXT("MyApi");

	// ���� ���α׷��� �ν��Ͻ� ���� �����ɴϴ�.
	m_hInstance = GetModuleHandle(NULL);

	// ������ ����.
	WndClass.cbClsExtra = 0;					//���࿵��1, Ư���� ��� ���Ǹ� �׿ܴ� 0����
	WndClass.cbWndExtra = 0;					//���࿵��2, ���� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW + 1);   //�������� ��� ������ ����.
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);			//���콺 Ŀ�� ����.
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);		//������ ����.
	WndClass.hInstance = m_hInstance;					//������ Ŭ������ ����ϴ� ���α׷��� ��ȣ�� WinMain�� hInstance�� �ָ� �ȴ�.
	WndClass.lpfnWndProc = WndProc;					//�޼����� ó���� �Լ�.(�߿�!)
	WndClass.lpszClassName = m_applicationName;				//���α׷� Ŭ������ �̸� ���.
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);					//���α׷��� ����� �޴��� �����Ѵ�.
	WndClass.style = CS_HREDRAW | CS_VREDRAW;			//������ ��Ÿ��(�����찡 � ���¸� ���� ���� ����)
	RegisterClass(&WndClass);					//WndClass Ư���� ����.

	// ������ ����.
	m_hwnd = CreateWindow(m_applicationName, m_applicationName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 333, 480, NULL, NULL, m_hInstance, NULL);

	// ������ ǥ��.
	ShowWindow(m_hwnd, SW_SHOW);

	return true;
}

bool SystemClass::Frame()
{
	curTime = (float)timeGetTime() * 0.001;
	if (isPause)
	{
		oldTime = curTime;
		return 0;
	}
	if (curTime - oldTime >= waitingTime && !m_board->IsGameOver())
	{
		m_brick->Move(0, 1);
		oldTime = curTime ;
		inputState = VK_DOWN;
		Coliision();
		InvalidateRect(m_hwnd, NULL, false);
	}
	return false;
}

void SystemClass::MessageProc(WPARAM wParam)
{
	if (isPause)
	{
		oldTime = curTime;
		return;
	}
	inputState = wParam;
	switch (inputState) {
	case VK_UP:
		m_brick->Rotate(true);
		break;
	case VK_DOWN:
		m_brick->Move(0, 1);
		oldTime = (float)timeGetTime() * 0.001;
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
		oldTime = (float)timeGetTime() * 0.001;
		break;
	}
}

void SystemClass::Coliision()
{
	while (m_board->IsCollision(m_brick->GetShapeArray(), m_brick->GetPosition()) && !m_board->IsGameOver())
	{
		CollisionSolve(inputState);
	}
}

void SystemClass::CollisionSolve(WPARAM inputState)
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
		m_brick->Reset(rand() % 7, Point(15 / 2 - 3, -2), 0);
		m_board->IsLineFull();
		break;
	}
}

void SystemClass::TetrisDraw(HDC hdc)
{
	HDC MemDC;
	HBITMAP MyBit,OldBit;
	RECT rect;
	GetClientRect(m_hwnd, &rect);

	MemDC = CreateCompatibleDC(hdc);
	//MyBit = CreateBitmap(rect.right - rect.left, rect.bottom - rect.top, 1, 32, NULL);
	MyBit = CreateCompatibleBitmap(hdc, rect.right - rect.left, rect.bottom - rect.top);
	OldBit = (HBITMAP)SelectObject(MemDC, MyBit);
	FillRect(MemDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));	

	m_draw->PaintBackGround(m_board->GetColRow(), MemDC);
	m_draw->Paint(m_board->GetBoardArray(), Point(0, 0), MemDC);
	m_draw->Paint(m_brick->GetShapeArray(), m_brick->GetPosition(), MemDC);

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBit);
	DeleteObject(MyBit);
	DeleteDC(MemDC);
}

LRESULT SystemClass::MessageHandler(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[128] = TEXT("ABC");
	wstring temp;
	switch (iMessage) {
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd,&ps);
		TetrisDraw(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_CHAR:
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			return 0;
		}
		return 0;
	case WM_KEYDOWN:
		if (wParam == 'S')
			isPause = isPause ? false : true;
		if (m_board->IsGameOver())
			return 0;
		MessageProc(wParam);
		Coliision();
		InvalidateRect(m_hwnd, NULL, false);
		return 0;
	case WM_LBUTTONDOWN:
		return 0;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

LRESULT CALLBACK SystemClass::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return ApplicationHandle->MessageHandler(hWnd, iMessage, wParam, lParam);
	}
}