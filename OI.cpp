#include "Commands/DropGear.h"
#include "Commands/PushGear.h"

#include "OI.h"
#include "RobotMap.h"
#include "WPILib.h"

OI::OI() {

	std::cout << "[oi] OperatorInterface initializing..." << std::endl;

	// Process operator interface input here.
	RightStick = new Joystick(RIGHTSTICKPORT); //Driver stick
	LeftStick = new Joystick(LEFTSTICKPORT); //Operator Stick

	//Driver Stick
	SpinButton = new JoystickButton(RightStick, SPINBUTTON);
	ResetButton = new JoystickButton(RightStick, RESETBUTTON);
	TraverseButton = new JoystickButton(RightStick, TRAVERSEBUTTON);

	//Operator Stick
	DropGearButton = new JoystickButton(LeftStick, 3);
	DropGearButton->WhenPressed(new DropGear());

	PushGearButton = new JoystickButton(LeftStick, 5);
	PushGearButton->WhenPressed(new PushGear());

	DropFuelButton = new JoystickButton(LeftStick, 4); //Used for adding fuel to the hopper
	//DropBallButton->WhenPressed(new DropFuel());

	std::cout << "[oi] OperatorInterface initialized." << std::endl;
}
