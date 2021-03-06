#include "System.h"
SystemClass::SystemClass()
{
	stateNum = 0;
	srand((unsigned)time(NULL));
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

	// 시간 초기화.
	curTime = oldTime = (float)timeGetTime() * 0.001;
	
	// 게임모드를 객체화 후 vector에 넣습니다.
	m_Mode.push_back(new Title(m_hInstance,m_hwnd));
	m_Mode.push_back(new Tetris(m_hInstance, m_hwnd));
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
			//메세지가 종료 일시 반복문을 탈출. 해당 처리가 없으면 WndProc에서 창을 없애도 프로그램은 남아있게 된다.
			if (Message.message == WM_QUIT)
				done = true;
			else { // 아닐시 메세지 처리.
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
		else
			Frame();// 메세지가 없어도 계속 처리해야할 함수.

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
	// WndProc에서 해당 객체로 접근 가능하게 static 포인터에 해당 객체를 넘김.
	ApplicationHandle = this;

	WNDCLASS WndClass;

	// 프로그램 이름 설정.
	m_applicationName = TEXT("MyApi");

	// 현재 프로그램의 인스턴스 값을 가져옵니다.
	m_hInstance = GetModuleHandle(NULL);

	// 윈도우 설정.
	WndClass.cbClsExtra = 0;					//예약영역1, 특수한 경우 사용되며 그외는 0으로
	WndClass.cbWndExtra = 0;					//예약영역2, 이하 동일
	WndClass.hbrBackground = (HBRUSH)GetStockObject(COLOR_WINDOW + 1);   //윈도우의 배경 색상을 지정.
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);			//마우스 커서 지정.
	WndClass.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_ICON1));		//아이콘 지정.
	WndClass.hInstance = m_hInstance;					//윈도우 클래스를 등록하는 프로그램의 번호로 WinMain의 hInstance를 주면 된다.
	WndClass.lpfnWndProc = WndProc;					//메세지를 처리할 함수.(중요!)
	WndClass.lpszClassName = m_applicationName;				//프로그램 클래스의 이름 등록.
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);					//프로그램이 사용할 메뉴를 지정한다.
	WndClass.style = CS_HREDRAW | CS_VREDRAW;			//윈도우 스타일(윈도우가 어떤 형태를 갖을 지의 값들)
	RegisterClass(&WndClass);					//WndClass 특성을 저장.

	// 윈도우 생성.
	m_hwnd = CreateWindow(m_applicationName, m_applicationName, WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, 480, 480, NULL, NULL, m_hInstance, NULL);

	// 윈도우 표시.
	ShowWindow(m_hwnd, SW_SHOW);
	
	return true;
}

bool SystemClass::Frame()
{
	// 상태변환 확인
	int newState = m_Mode[stateNum]->GetNewState();
	if (newState != -1)
	{
		ChangeState(newState);

		return true;
	}

	// 플레이.
	curTime = (float)timeGetTime() * 0.001;
	m_Mode[stateNum]->Update(curTime - oldTime);
	oldTime = curTime;
	InvalidateRect(m_hwnd, NULL, false);

	return true;
}
void SystemClass::ChangeState(int idx)
{
	m_Mode[stateNum]->SetNewState(false);
	m_Mode[stateNum]->Shutdown();
	stateNum = idx;
	m_Mode[idx]->Initialization();
}
LRESULT SystemClass::MessageHandler(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage) {
	case WM_CREATE:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd,&ps);
		m_Mode[stateNum]->Draw(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_COMMAND:
		m_Mode[stateNum]->CommandEvent(wParam);
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
		m_Mode[stateNum]->KeyEvent(wParam);
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