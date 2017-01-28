#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
public:
	OI();
	Joystick *RightStick;
	Joystick *LeftStick;

	JoystickButton *ResetButton;
	JoystickButton *SpinButton;
	JoystickButton *TraverseButton;
};

#endif  // OI_H
