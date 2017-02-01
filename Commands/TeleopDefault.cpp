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
	Requires(gearsystem);
	Requires(ropeclimber);
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
			double TurnAngle = (controls->RightStick->GetX()/4)*-1;
			if (DeadzoneY < 0.1) {
				TurnAngle = (controls->RightStick->GetX()/4);
			}
			drivetrain->DoAutoAlign(TurnAngle,TurnAngle,TurnAngle,TurnAngle);
		} else {
			drivetrain->DoAutoAlign(0,0,0,0);
		}
		if (DeadzoneY > JOYSTICKDEADZONE || DeadzoneY < -JOYSTICKDEADZONE) {
			double Speed = controls->RightStick->GetY()/2;
			drivetrain->Drive(Speed);
		} else {
			drivetrain->Drive(0);
		}
	} else if (controls->SpinButton->Get()) {
		drivetrain->DoAutoAlign(0.125, -0.125, 0.125, -0.125);
		if (DeadzoneX > JOYSTICKDEADZONE || DeadzoneX < -JOYSTICKDEADZONE) {
			double Speed = controls->RightStick->GetX()/2;
			drivetrain->DriveSpecial(Speed, Speed, Speed, Speed);
		} else {
			drivetrain->Drive(0);
		}
	} else {
		double TurnAngle = (controls->RightStick->GetX()/10)*-1;
		if (DeadzoneX > JOYSTICKDEADZONE || DeadzoneX < -JOYSTICKDEADZONE) {
			drivetrain->DoAutoAlign(-TurnAngle, TurnAngle, TurnAngle, -TurnAngle);
		} else {
			drivetrain->DoAutoAlign(0,0,0,0);
		}
		if (DeadzoneY > JOYSTICKDEADZONE || DeadzoneY < -JOYSTICKDEADZONE) {
			double Speed = controls->RightStick->GetY()/1.2;
			if (TurnAngle > 0) {
				drivetrain->DriveSpecial(Speed/2, Speed/2, -Speed, -Speed);
			} else {
				drivetrain->DriveSpecial(Speed, Speed, -Speed/2, -Speed/2);
			}
			drivetrain->Drive(Speed);
		} else {
			drivetrain->Drive(0);
		}
	}

	//Operator stuff
	double POV = controls->RopeClimbButton->Get();
	double POVMultiplier = controls->LeftStick->GetRawAxis(3);
	if (POV) {
		ropeclimber->Climb(POVMultiplier);
		//gearsystem->SolenoidIII->Set(DoubleSolenoid::Value::kReverse);
	} else {
		//gearsystem->SolenoidIII->Set(DoubleSolenoid::Value::kOff);
		ropeclimber->Stop();
	}
	if (controls->ExtendGearDoor->Get()) {
		gearsystem->SolenoidI->Set(DoubleSolenoid::Value::kForward);
	} else if (controls->RetractGearDoor->Get()) {
		gearsystem->SolenoidI->Set(DoubleSolenoid::Value::kReverse);
	} else {
		gearsystem->SolenoidI->Set(DoubleSolenoid::Value::kOff);
	}
	if (controls->ExtendGearPusher->Get()) {
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kReverse);
	} else if (controls->RetractGearPusher->Get()) {
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward);
	} else {
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kOff);
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


