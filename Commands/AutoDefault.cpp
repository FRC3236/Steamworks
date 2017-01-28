/*
 * AutoDefault.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */
#include "AutoDefault.h"
#include "../CommandBase.h"

AutoDefault::AutoDefault() : CommandBase("AutoDefault") {
	//Requires(drivetrain);
	drivetrain = new DriveTrain();
	AutoTimer = new Timer();
}

void AutoDefault::Initialize() {
	drivetrain->ResetAlignment();
	AutoTimer->Reset();
	AutoTimer->Start();
}

void AutoDefault::Execute() {
	if (AutoTimer->Get() > 1) {
		this->End();
	}
	return;
}

bool AutoDefault::IsFinished() {
	if (AutoTimer->Get() > 1) {
		return true;
	} else {
		return false;
	}
}

void AutoDefault::Interrupted() {
	return;
}

void AutoDefault::End() {
	drivetrain->KillDrive();
	AutoTimer->Stop();
	return;
}

