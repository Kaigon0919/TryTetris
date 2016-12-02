
#include"System.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	bool result;
	SystemClass system;

	result = system.Initialize();

	if (result)
		system.Run();

	system.Shutdown();
	return 0;
}