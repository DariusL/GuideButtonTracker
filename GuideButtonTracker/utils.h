#pragma once
#include <string>

#ifndef _DEBUG
#define Assert(x) \
	if (!x) \
	{ \
		DebugBreak(); \
	}
#else
#define Assert(x) \
	if (!x) \
	{ \
		DebugBreak(); \
	}
#endif
