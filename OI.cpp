#include "OI.h"
#include "RobotMap.h"
#include "WPILib.h"

OI::OI() {

	std::cout << "[oi] OperatorInterface initializing..." << std::endl;

	// Process operator interface input here.
	RightStick = new Joystick(RIGHTSTICKPORT); //Driver stick
	LeftStick = new Joystick(LEFTSTICKPORT); //Operator Stick

	SpinButton = new JoystickButton(RightStick, SPINBUTTON);
	ResetButton = new JoystickButton(RightStick, RESETBUTTON);
	TraverseButton = new JoystickButton(RightStick, TRAVERSEBUTTON);

	RopeClimbButton = new JoystickButton(LeftStick, 1);

	std::cout << "[oi] OperatorInterface initialized." << std::endl;
}
