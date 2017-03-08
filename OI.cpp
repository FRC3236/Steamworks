#include "Commands/DropGear.h"
#include "Commands/PushGear.h"

#include "OI.h"
#include "RobotMap.h"
#include "WPILib.h"

OI::OI() {

	std::cout << "[oi] OperatorInterface initializing..." << std::endl;

	RightStick = new Joystick(RIGHTSTICKPORT); //Driver stick
	LeftStick = new Joystick(LEFTSTICKPORT); //Operator Stick

	//Driver Stick
	SpinButton = new JoystickButton(RightStick, SPINBUTTON);
	ResetButton = new JoystickButton(RightStick, RESETBUTTON);
	TraverseButton = new JoystickButton(RightStick, TRAVERSEBUTTON);
	CameraSwitchButton = new JoystickButton(RightStick, CAMERASWITCHBUTTON);
	LockAngleButton = new JoystickButton(RightStick, LOCKANGLEBUTTON);

	//Operator Stick
	DropGearButton = new JoystickButton(LeftStick, 5);
	PushGearButton = new JoystickButton(LeftStick, 3);
	PushGearOverrideButton = new JoystickButton(LeftStick, 4);
	DropFuelButton = new JoystickButton(LeftStick, 6);
	ClimberButton = new JoystickButton(LeftStick, 1);
	RopeClimbButton = new JoystickButton(LeftStick,4);
	GearSafetyButton = new JoystickButton(LeftStick, GEAROVERRIDEBUTTON);

	std::cout << "[oi] OperatorInterface initialized." << std::endl;
}
