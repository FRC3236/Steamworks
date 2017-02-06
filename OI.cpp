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

	ExtendGearPusher = new JoystickButton(LeftStick, 5);
	RetractGearPusher = new JoystickButton(LeftStick, 3);
	ExtendGearDoor = new JoystickButton(LeftStick, 6);
	RetractGearDoor = new JoystickButton(LeftStick, 4);
	RopeClimbButton = new JoystickButton(LeftStick, 1);
	ToggleGearBall = new JoystickButton(LeftStick, 2);

	std::cout << "[oi] OperatorInterface initialized." << std::endl;
}
