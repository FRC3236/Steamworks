/*
 * TeleopDefault.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */

#include "TeleopDefault.h"
#include "../CommandBase.h"

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
	double TurnAngle = controls->RightStick->GetX();
	double Speed = controls->LeftStick->GetY()/4;
	if (controls->TraverseButton->Get()) {
		TurnAngle = TurnAngle/4;
		drivetrain->DoAutoAlign(TurnAngle, TurnAngle, TurnAngle, TurnAngle);
	} else if (controls->SpinButton->Get()) {
		TurnAngle = TurnAngle/4;
		drivetrain->DoAutoAlign(0.125, -0.125, 0.125, -0.125);
		drivetrain->Drive(Speed);
	} else {
		TurnAngle = TurnAngle/6;
		drivetrain->DoAutoAlign(TurnAngle, -TurnAngle, -TurnAngle, TurnAngle);
		drivetrain->Drive(Speed);
	}
	return;
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


