#pragma once
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
using namespace std;
class Window
{
	static Window *instance;
	HWND windowHandle;
	std::wstring appName;
	HINSTANCE hInstance;
	bool quit;

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK OnMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	Window(wstring appName);
	~Window();

	HWND GetWindowHandle(){ return windowHandle; }

	bool IsQuit() { return quit; }
};

