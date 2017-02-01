#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
public:
	OI();
	Joystick *RightStick;
	Joystick *LeftStick;

	//Driver stick stuff
	JoystickButton *ResetButton;
	JoystickButton *SpinButton;
	JoystickButton *TraverseButton;

	//Operator stick stuff
	JoystickButton *RopeClimbButton;
	JoystickButton *ExtendGearDoor;
	JoystickButton *RetractGearDoor;
	JoystickButton *ExtendGearPusher;
	JoystickButton *RetractGearPusher;
};

#endif  // OI_H
