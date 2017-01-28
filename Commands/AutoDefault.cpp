/*
 * AutoDefault.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */
#include "AutoDefault.h"
#include "../CommandBase.h"

AutoDefault::AutoDefault() : CommandBase("AutoDefault") {
	Requires(drivetrain);
	//drivetrain = new DriveTrain();
	AutoTimer = new Timer();
}

void AutoDefault::Initialize() {
	//drivetrain->ResetAlignment();
	AutoTimer->Reset();
	AutoTimer->Start();
}

void AutoDefault::Execute() {
	std::cout << "AUTODEFAULT GO!" << std::endl;
	if (AutoTimer->Get() > 1) {
		drivetrain->Drive(0.5);
	} else {
		this->End();
	}
}

bool AutoDefault::IsFinished() {
	std::cout << "AUTODEFAULT::ISFINISHED() " << AutoTimer->Get() << std::endl;
	if (AutoTimer->Get() > 1) {
		return true;
	}
	return false;
}

void AutoDefault::Interrupted() {
	return;
}

void AutoDefault::End() {
	drivetrain->KillDrive();
	AutoTimer->Stop();
	return;
}

