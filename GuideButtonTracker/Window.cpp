#include "Window.h"

Window *Window::instance;

Window::Window(std::wstring appName)
:appName(appName), quit(false)
{
	WNDCLASSEX wc;

	hInstance = GetModuleHandle(NULL);

	auto name = appName.c_str();

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = name;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	windowHandle = CreateWindowEx(WS_EX_APPWINDOW, name, name,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		0, 0, 0, 0, NULL, NULL, hInstance, NULL);

	instance = this;
}

Window::~Window()
{
	DestroyWindow(windowHandle);
	windowHandle = NULL;
	UnregisterClass(appName.c_str(), hInstance);
	hInstance = NULL;
}

LRESULT Window::WndProc(HWND whandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	return instance->OnMessage(whandle, message, wParam, lParam);
}

LRESULT Window::OnMessage(HWND whandle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		quit = true;
		break;
	case WM_QUIT:
		quit = true;
		break;
	default:
		return DefWindowProc(whandle, message, wParam, lParam);
	}
	return 0;
}
