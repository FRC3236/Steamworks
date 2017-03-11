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
	DropGearButton = new JoystickButton(LeftStick, DROPGEARBUTTON);
	PushGearButton = new JoystickButton(LeftStick, PUSHGEARBUTTON);
	PushGearOverrideButton = new JoystickButton(LeftStick, PUSHGEAROVERRIDEBUTTON);
	ClimberButton = new JoystickButton(LeftStick, CLIMBERBUTTON);
	GearSafetyButton = new JoystickButton(LeftStick, GEAROVERRIDEBUTTON);
	//LimitSwitchCheck.WhenActive ( a new thing );

	std::cout << "[oi] OperatorInterface initialized." << std::endl;
}
