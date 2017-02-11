/*
 * TeleopDefault.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */

#include "TeleopDefault.h"
#include "../CommandBase.h"
#include "../RobotMap.h"
#include "WPILib.h"
#include "DropGear.h"
#include "DropFuel.h"
#include "PushGear.h"
#include "DisableCompressor.h"
#include "EnableCompressor.h"
#include <cmath>

TeleopDefault::TeleopDefault() {
	std::cout << "Making a new teleop!" << std::endl;
	Requires(drivetrain);
	Requires(ropeclimber);
	TeleopTimer = new Timer();
	dropgear = new DropGear();
	pushgear = new PushGear();
	//this->SetInterruptible(false);
}

void TeleopDefault::Initialize() {
	std::cout << "[teleop] Teleop initalizing..." << std::endl;
	drivetrain->ResetAlignment();
	TeleopTimer->Reset();
	TeleopTimer->Start();

	controls->DropGearButton->WhenPressed(new DropGear());
	//controls->DropGearButton->WhenReleased(this);
	//controls->DropFuelButton->ToggleWhenPressed();
	//controls->DropFuelButton->WhenReleased(this);
	controls->PushGearButton->WhenPressed(new PushGear());
	//controls->PushGearButton->WhenReleased(this);

	//Print Solenoid information to smart dashboard for debugging.
	frc::SmartDashboard::PutNumber("Solenoid I (gear door)", gearsystem->SolenoidI->Get());
	frc::SmartDashboard::PutNumber("Solenoid II (gear pusher)", gearsystem->SolenoidII->Get());
	frc::SmartDashboard::PutNumber("Solenoid III (doesn't do anything)", 0);
	frc::SmartDashboard::PutNumber("Solenoid IV (gear/ball toggle)", gearsystem->SolenoidIV->Get());

	std::cout << "[teleop] Teleop initialized." << std::endl;
}

void TeleopDefault::Execute() {

	//std::cout << "TeleopDefault Execute!" << std::endl;

	frc::SmartDashboard::PutNumber("Solenoid I (gear door)", gearsystem->SolenoidI->Get());
	frc::SmartDashboard::PutNumber("Solenoid II (gear pusher)", gearsystem->SolenoidII->Get());
	frc::SmartDashboard::PutNumber("Solenoid III (doesn't do anything)", 0);
	frc::SmartDashboard::PutNumber("Solenoid IV (gear/ball toggle)", gearsystem->SolenoidIV->Get());

	if (controls->TraverseButton->Get()) {
		drivetrain->Traverse(controls->RightStick->GetX(), controls->RightStick->GetY());
	} else if (controls->SpinButton->Get()) {
		drivetrain->DoAutoAlign(0.125, -0.125, 0.125, -0.125);
		double DeadzoneX = controls->RightStick->GetX();
		if (fabs(DeadzoneX) > JOYSTICKDEADZONE) {
			double Speed = -(controls->RightStick->GetX()/2);
			drivetrain->DriveSpecial(Speed, Speed, Speed, Speed);
		} else {
			drivetrain->Drive(0);
		}
	} else {
		drivetrain->TurnAbout(15/(controls->RightStick->GetX()),controls->RightStick->GetY());
	}

	//Operator stuff is handed by OI.cpp and the buttons' "WhenPressed()" method.
	if (controls->ClimberButton->Get()) {
		double Amount = controls->LeftStick->GetRawAxis(3);
		ropeclimber->Climb(Amount);
	} else {
		ropeclimber->Climb(0);
	}
}

bool TeleopDefault::IsFinished() {
	return false;
}

void TeleopDefault::End() {
	std::cout << "[teleop] Teleop->End() has been called. Ending Teleop..." << std::endl;
	//CommandBase::Reset(); //Reset all the subsystems to be new again!
}

void TeleopDefault::Interrupted() {
	std::cout << "[teleop] Teleop was interrtuped. Aborting..." << std::endl;

}


