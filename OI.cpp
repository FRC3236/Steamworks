#include "OI.h"
#include "RobotMap.h"
#include "WPILib.h"

OI::OI() {
	// Process operator interface input here.
	RightStick = new Joystick(RIGHTSTICKPORT);
	LeftStick = new Joystick(LEFTSTICKPORT);

	SpinButton = new JoystickButton(RightStick, SPINBUTTON);
	ResetButton = new JoystickButton(RightStick, RESETBUTTON);
	TraverseButton = new JoystickButton(RightStick, TRAVERSEBUTTON);
}
