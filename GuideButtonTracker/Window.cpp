#include "Window.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Rpcrt4.lib")

Window *Window::instance;
const UINT Window::MESSAGE_NOTIF = WM_USER + 1;
const UINT Window::MESSAGE_QUIT = WM_USER + 2;

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

	GUID guid;
	Assert(UuidFromString((RPC_WSTR)L"A15F7BA5-BCC3-4140-9B2A-AAE31BD53A4A", &guid) == RPC_S_OK);

	nid = {};
	nid.uVersion = NOTIFYICON_VERSION_4;
	nid.cbSize = sizeof(nid);
	nid.hWnd = windowHandle;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_SHOWTIP | NIF_GUID | NIF_MESSAGE;
	nid.uCallbackMessage = MESSAGE_NOTIF;

	nid.guidItem = guid;

	StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"GuideButtonTracker");

	Assert(LoadIconMetric(nullptr, IDI_APPLICATION, LIM_SMALL, &(nid.hIcon)) == S_OK);

	Shell_NotifyIcon(NIM_ADD, &nid);
	Shell_NotifyIcon(NIM_SETVERSION, &nid);

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
	case MESSAGE_NOTIF:
		if (LOWORD(lParam) == WM_CONTEXTMENU)
		{
			POINT pt = {};
			if (GetCursorPos(&pt))
			{
				HMENU hPopupMenu = CreatePopupMenu();
				AppendMenu(hPopupMenu, MF_STRING, MESSAGE_QUIT, L"Quit");
				TrackPopupMenu(hPopupMenu, TPM_BOTTOMALIGN | TPM_RIGHTALIGN, pt.x, pt.y, 0, windowHandle, NULL);
			}
		}
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == MESSAGE_QUIT)
		{
			quit = true;
		}
		break;
	default:
		return DefWindowProc(whandle, message, wParam, lParam);
	}
	return 0;
}
