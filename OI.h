#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
public:

	Joystick *RightStick;
	Joystick *LeftStick;

	//Driver stick stuff
	JoystickButton	*ResetButton,
					*SpinButton,
					*TraverseButton;

	JoystickButton	*DropGearButton,
					*PushGearButton,
					*DropFuelButton;


	//Operator stick stuff

	OI();
};

#endif  // OI_H
