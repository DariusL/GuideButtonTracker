#pragma once

//target Win7
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0601

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <Strsafe.h>
#include <Commctrl.h>
#include <Shellapi.h>

#include "utils.h"

using namespace std;
class Window
{
	static const UINT MESSAGE;
	static Window *instance;
	HWND windowHandle;
	std::wstring appName;
	HINSTANCE hInstance;
	bool quit;
	NOTIFYICONDATA nid;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	Window(wstring appName);
	~Window();

	HWND GetWindowHandle(){ return windowHandle; }

	bool IsQuit() { return quit; }
};

