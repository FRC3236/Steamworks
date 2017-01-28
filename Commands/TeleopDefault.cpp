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
	//Requires(drivetrain);
	drivetrain = new DriveTrain();
	TeleopTimer = new Timer();
}

void TeleopDefault::Initialize() {
	drivetrain->ResetAlignment();
	TeleopTimer->Reset();
	TeleopTimer->Start();
}

void TeleopDefault::Execute() {
	double DeadzoneX = controls->RightStick->GetX();
	double DeadzoneY = controls->RightStick->GetY();

	//Turning Code//
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
	drivetrain->KillDrive();
}

void TeleopDefault::Interrupted() {
	drivetrain->KillDrive();
}


