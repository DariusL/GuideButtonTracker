#pragma once
#include <windows.h>

class XInput
{
public:
	struct ControllerStruct
	{
		unsigned long eventCount; //event counter, increases with every controller event,
								  //but for some reason not by one.
		unsigned short up : 1, down : 1, left : 1, right : 1, start : 1, back : 1, l3 : 1, r3 : 1,
			lButton : 1, rButton : 1, guideButton : 1, unknown : 1, aButton : 1,
			bButton : 1, xButton : 1, yButton : 1; // button state bitfield
		unsigned char lTrigger;  //Left Trigger
		unsigned char rTrigger;  //Right Trigger
		short lJoyY;  //Left Joystick Y
		short lJoyx;  //Left Joystick X
		short rJoyY;  //Right Joystick Y 
		short rJoyX;  //Right Joystick X
	};

	typedef int(__stdcall * pICFUNC)(int, ControllerStruct &);

private:
	HINSTANCE dll;
	pICFUNC getControllerData;
	const int controller;

public:
	XInput(int controller);
	~XInput();

	void getControllerState(ControllerStruct &state);
};
