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

	std::cout << "[ropeclimber] RopeClimber initializing..." << std::endl;

	ClimbLeftTalon = new Talon(ClimberLeftPWMPort);
	ClimbRightTalon = new Talon(ClimberRightPWMPort);

	std::cout << "[ropeclimber] RopeClimber initialized." << std::endl;
}

void RopeClimber::Initialize() {
	ClimbLeftTalon->Set(0);
	ClimbRightTalon->Set(0);
	return;
}

void RopeClimber::Execute() {
	return;
}

void RopeClimber::Climb(double Multiplier) {
	ClimbLeftTalon->Set(-1*Multiplier);
	ClimbRightTalon->Set(-1*Multiplier);
}

void RopeClimber::ClimbUp(double Multiplier) {
	ClimbLeftTalon->Set(1*Multiplier);
	ClimbRightTalon->Set(1*Multiplier);
	return;
}

void RopeClimber::ClimbDown(double Multiplier) {
	ClimbLeftTalon->Set(-1*Multiplier);
	ClimbRightTalon->Set(-1*Multiplier);
	return;
}

void RopeClimber::Stop() {
	ClimbLeftTalon->Set(0);
	ClimbRightTalon->Set(0);
	return;
}
