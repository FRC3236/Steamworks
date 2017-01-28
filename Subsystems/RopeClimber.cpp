/*
 * RopeClimber.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */
#include "RopeClimber.h"
#include "../RobotMap.h"
#include "WPILib.h"

RopeClimber::RopeClimber() : Subsystem("RopeClimber") {
	frc::Subsystem("RopeClimber");

	ClimbTalon = new Talon(ClimberPWMPort);
}

void RopeClimber::Initialize() {
	ClimbTalon->Set(0);
	return;
}

void RopeClimber::Execute() {
	return;
}

void RopeClimber::ClimbUp() {
	ClimbTalon->Set(1);
	return;
}

void RopeClimber::ClimbDown() {
	ClimbTalon->Set(-1);
	return;
}

void RopeClimber::Stop() {
	ClimbTalon->Set(0);
	return;
}
