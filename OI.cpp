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

	//Operator Stick
	DropGearButton = new JoystickButton(LeftStick, 5);
	PushGearButton = new JoystickButton(LeftStick, 3);
	PushGearOverrideButton = new JoystickButton(LeftStick, 4);
	//PushGearButton->WhenPressed(new PushGear());
	DropFuelButton = new JoystickButton(LeftStick, 6);
	ClimberButton = new JoystickButton(LeftStick, 1);
	RopeClimbButton = new JoystickButton(LeftStick,4);
	GearSafetyButton = new JoystickButton(LeftStick, GEAROVERRIDEBUTTON);

	//Used for adding fuel to the hopper
	//DropFuelButton->WhenPressed(new DropFuel());

	//DropFuelButton->WhenPressed(new DropFuel());
	//ClimberButton->WhenPressed(new DisableCompressor());
	//ClimberButton->WhenReleased(new EnableCompressor());

	std::cout << "[oi] OperatorInterface initialized." << std::endl;
}
