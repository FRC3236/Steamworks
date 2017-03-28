/**
	FRC2017
	RopeClimber.cpp
	Purpose: Class for the RopeClimber object

	@author Eric Bernard
	@version 1.0 3/27/2016
*/

#include "RopeClimber.h"
#include "../RobotMap.h"
#include "WPILib.h"

RopeClimber::RopeClimber() : frc::Subsystem("RopeClimber") {
	ClimbLeftTalon = new Talon(ClimberLeftPWMPort);
	ClimbRightTalon = new Talon(ClimberRightPWMPort);
}

/**
	Sets both Talons to 0 to ensure a known
	configuration
*/
void RopeClimber::Initialize() {
	this->Stop();
	return;
}

/**
	Pulls the robot up or down the rope

	@param Multiplier - speed at which to climb
*/
void RopeClimber::Climb(double Multiplier) {
	ClimbLeftTalon->Set(-1*Multiplier);
	ClimbRightTalon->Set(-1*Multiplier);
	return;
}

/**
	Stops all motion on the climber.
*/
void RopeClimber::Stop() {
	ClimbLeftTalon->Set(0);
	ClimbRightTalon->Set(0);
	return;
}
