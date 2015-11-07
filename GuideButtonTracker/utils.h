#pragma once
#include <string>

#define Assert(x) \
	if (!x) \
	{ \
		MessageBox(NULL, (L"Error: " + std::to_wstring(GetLastError())).c_str(), L"Explosions!", MB_OK);\
		DebugBreak(); \
	}
