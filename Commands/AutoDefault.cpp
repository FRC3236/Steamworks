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
		drivetrain->Drive(0.5);
	} else {
		this->End();
	}
}

bool AutoDefault::IsFinished() {
	if (AutoTimer->Get() < 1) {
		return false;
	} else {
		this->End();
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
	drivetrain->KillDrive();
	AutoTimer->Stop();
	return;
}

