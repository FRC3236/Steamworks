/*
 * TeleopDefault.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */

#include "TeleopDefault.h"
#include "../CommandBase.h"
#include "../RobotMap.h"

TeleopDefault::TeleopDefault() {
	Requires(drivetrain);
	TeleopTimer = new Timer();
}

void TeleopDefault::Initialize() {
	std::cout << "[teleop] Teleop initalizing..." << std::endl;
	drivetrain->ResetAlignment();
	TeleopTimer->Reset();
	TeleopTimer->Start();
	std::cout << "[teleop] Teleop initialized." << std::endl;
}

void TeleopDefault::Execute() {
	double DeadzoneX = controls->RightStick->GetX();
	double DeadzoneY = controls->RightStick->GetY();

	if (controls->TraverseButton->Get()) {
		if (DeadzoneX > JOYSTICKDEADZONE || DeadzoneX < -JOYSTICKDEADZONE) {
			double TurnAngle = controls->RightStick->GetX()/4;
			drivetrain->DoAutoAlign(TurnAngle,TurnAngle,TurnAngle,TurnAngle);
		}
		if (DeadzoneY > JOYSTICKDEADZONE || DeadzoneY < -JOYSTICKDEADZONE) {
			double Speed = controls->RightStick->GetY()/2;
			drivetrain->Drive(Speed);
		}
	} else if (controls->SpinButton->Get()) {
		if (DeadzoneX > JOYSTICKDEADZONE || DeadzoneX < -JOYSTICKDEADZONE) {
			double Speed = controls->RightStick->GetY()/4;
			drivetrain->Drive(Speed);
		}
	} else {
		if (DeadzoneX > JOYSTICKDEADZONE || DeadzoneX < -JOYSTICKDEADZONE) {
			double TurnAngle = controls->RightStick->GetX()/4;
			drivetrain->DoAutoAlign(TurnAngle, -TurnAngle, -TurnAngle, TurnAngle);
		}
		if (DeadzoneY > JOYSTICKDEADZONE || DeadzoneY < -JOYSTICKDEADZONE) {
			double Speed = controls->RightStick->GetY()/2;
			drivetrain->Drive(Speed);
		}
	}
}

bool TeleopDefault::IsFinished() {
	return false;
}

void TeleopDefault::End() {
	std::cout << "[teleop] Teleop->End() has been called. Ending Teleop..." << std::endl;
	drivetrain->KillDrive();
}

void TeleopDefault::Interrupted() {
	std::cout << "[teleop] Teleop was interrtuped. Aborting..." << std::endl;
	drivetrain->KillDrive();
}


