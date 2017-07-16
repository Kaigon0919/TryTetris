#include "System.h"
SystemClass::SystemClass()
{
	stateNum = 1;
	srand((unsigned)time(NULL));
	isPause = false;

	m_Mode.push_back(new Title);
	m_Mode.push_back(new Tetris);
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

	curTime = oldTime = (float)timeGetTime() * 0.001;
	m_Mode[stateNum]->Initialization();
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
	for (int i = 0; i < m_Mode.size(); ++i)
	{
		if (m_Mode[i])
		{
			delete m_Mode[i];
			m_Mode[i] = nullptr;
		}
	}
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
	WndClass.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_ICON1));		//������ ����.
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
		return true;
	}
	m_Mode[stateNum]->Update(curTime - oldTime);
	oldTime = curTime;
	InvalidateRect(m_hwnd, NULL, false);

	return true;
}

void SystemClass::MessageProc(WPARAM wParam)
{
	if (isPause)
	{
		oldTime = curTime;
		return;
	}
	m_Mode[stateNum]->KeyEvent(wParam);
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
		m_Mode[stateNum]->Draw(hWnd,hdc);
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
		MessageProc(wParam);
		//InvalidateRect(m_hwnd, NULL, false);
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