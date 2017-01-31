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
	drivetrain->ResetAlignment();
	AutoTimer = new Timer();
}

void AutoDefault::Initialize() {
	std::cout << "[autonomous] Program 'AutoDefault' is initializing." << std::endl;
	drivetrain->ResetAlignment();
	AutoTimer->Reset();
	AutoTimer->Start();
}

void AutoDefault::Execute() {
	std::cout << "[autonomous] Program 'AutoDefault' is executing." << std::endl;
	if (AutoTimer->Get() < 1) {
		drivetrain->Drive(0.2);
	} else if (AutoTimer->Get() > 1 && AutoTimer->Get() < 2) {
		std::cout << "BEGINNING ALIGNMENT" << std::endl;
		drivetrain->DoAutoAlign(0.125, 0.125, 0.125, 0.125);
		drivetrain->Drive(-0.2);
	} else {
		this->End();
	}
}

bool AutoDefault::IsFinished() {
	if (AutoTimer->Get() < 2) {
		return false;
	} else {
		return true;
	}
}

void AutoDefault::Interrupted() {
	std::cout << "[autonomous] Program 'AutoDefault' has been interrupted. Aborting..." << std::endl;
	this->End();
	return;
}

void AutoDefault::End() {
	std::cout << "[autonomous] Program 'AutoDefault' has reached the end of its sequence." << std::endl;
	drivetrain->ResetAlignment();
	drivetrain->KillDrive();
	AutoTimer->Stop();
	return;
}

