/*
* GuideButtonPoller.cpp
*
*  Created on: Nov 12, 2012
*      Author: James
*/
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>

#include "xinput.h"

int main()
{
	XInput xinput(0);
	XInput::ControllerStruct buttons;
	HWND lHwnd = FindWindow(L"Shell_TrayWnd", nullptr);
	while (1) //Infinite polling loop
	{

		xinput.getControllerState(buttons);  //call the function with the controller number(zero based) and
		if (buttons.guideButton)
		{
			SendMessage(lHwnd, WM_COMMAND, 419, 0);
		}
	}

	return 0;
}