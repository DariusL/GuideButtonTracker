#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#include "xinput.h"
#include "Window.h"

void processMessage()
{
	MSG msg = {};
	GetMessage(&msg, NULL, 0, 0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Window window(L"GuideButtonTracker");
	XInput xinput(0);
	XInput::ControllerStruct buttons;
	HWND lHwnd = FindWindow(L"Shell_TrayWnd", nullptr);
	while (!window.IsQuit())
	{
		xinput.getControllerState(buttons);  //call the function with the controller number(zero based) and
		if (buttons.guideButton)
		{
			SendMessage(lHwnd, WM_COMMAND, 419, 0);
		}

		processMessage();
		Sleep(30);
	}

	return 0;
}
