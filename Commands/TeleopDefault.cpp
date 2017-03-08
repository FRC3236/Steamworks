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
#include "ZeroWheels.h"
#include "DisableCompressor.h"
#include "EnableCompressor.h"
#include <cmath>

TeleopDefault::TeleopDefault() {
	Requires(drivetrain);
	Requires(ropeclimber);
	TeleopTimer = new Timer();
	dropgear = new DropGear();
	pushgear = new PushGear(true);
	pushgearoverride = new PushGear(false);
	LockAngle = 0;
}

void TeleopDefault::Initialize() {
	std::cout << "[teleop] Teleop initalizing..." << std::endl;
	drivetrain->ResetAlignment();
	TeleopTimer->Reset();
	TeleopTimer->Start();

	controls->DropGearButton->WhenPressed(new DropGear());

	controls->PushGearButton->WhenPressed(this->pushgear);
	controls->GearSafetyButton->WhenPressed(this->pushgearoverride);

	controls->ClimberButton->WhenPressed(new DisableCompressor()); //disable the compressor during climb.
	controls->ClimberButton->WhenReleased(new EnableCompressor()); //reenable the compressor after the climb.

	std::cout << "[teleop] Teleop initialized." << std::endl;
	LockAngle = 0;
}

void TeleopDefault::Execute() {

	if (controls->TraverseButton->Get()) {
		drivetrain->TraverseSimple(controls->RightStick->GetX());
	} else if (controls->RightStick->GetPOV() >= 0) {
		drivetrain->Crawl((double) controls->RightStick->GetPOV()/360);
	} else if (controls->SpinButton->Get()) {
		drivetrain->DoAutoAlign(0.125, -0.125, 0.125, -0.125);
		double DeadzoneX = controls->RightStick->GetX();
		if (fabs(DeadzoneX) > JOYSTICKDEADZONE) {
			double Speed = -(controls->RightStick->GetX()/2);
			drivetrain->DriveSpecial(Speed, Speed, Speed, Speed);
		} else {
			drivetrain->Drive(0);
		}

	} else if (controls->LeftStick->GetRawButton(11)) {
		drivetrain->SpinTo(90, 0.5);
	} else if (controls->ResetButton->Get()) {
		drivetrain->DoAutoAlign(0,0,0,0);
	} else {
		drivetrain->TurnAbout(15*fabs(controls->RightStick->GetX())/(powf(controls->RightStick->GetX(),3)),-(controls->RightStick->GetY()));
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
	drivetrain->Drive(0);
	drivetrain->KillSpin();
	drivetrain->ResetAlignment();
}

void TeleopDefault::Interrupted() {
	std::cout << "[teleop] Teleop was interrtuped. Aborting..." << std::endl;

}


