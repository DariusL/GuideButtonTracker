#include "xinput.h"

XInput::XInput(int controller)
	:controller(controller)
{
	dll = LoadLibrary(L"C:/Windows/System32/xinput1_3.dll");
	FARPROC lpfnGetProcessID = GetProcAddress((HMODULE)dll, (LPCSTR)100); 
	
	getControllerData = (pICFUNC)lpfnGetProcessID;
}

XInput::~XInput()
{
	FreeLibrary(dll);
}

void XInput::getControllerState(ControllerStruct & state)
{
	getControllerData(controller, state);
}
