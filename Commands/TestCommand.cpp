/*
 * TestCommand.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */

#include "TestCommand.h"
#include "../CommandBase.h"
#include "../RobotMap.h"

TestCommand::TestCommand() {
	Requires(drivetrain);
}

void TestCommand::Initialize() {
	drivetrain->ResetAlignment();
}

void TestCommand::Execute() {
	drivetrain->Drive(0.1);
}

bool TestCommand::IsFinished() {
	return false;
}

void TestCommand::Interrupted() {
	return;
}

void TestCommand::End() {
	return;
}


