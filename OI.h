#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "Triggers/LimitSwitch.h"

class OI {
public:

	Joystick *RightStick;
	Joystick *LeftStick;

	//Driver stick stuff
	JoystickButton	*ResetButton,
					*SpinButton,
					*TraverseButton,
					*CameraSwitchButton;

	//Operator stick stuff
	JoystickButton	*DropGearButton,
					*PushGearButton,
					*PushGearOverrideButton,
					*ClimberButton,
					*GearSafetyButton,
					*LockAngleButton;

	LimitSwitch LimitSwitchCheck;

	OI();
};

#endif  // OI_H
