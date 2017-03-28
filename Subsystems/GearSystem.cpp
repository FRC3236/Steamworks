/**
	FRC2017
	GearSystem.cpp
	Purpose: Class for the GearSystem object

	@author Eric Bernard
	@version 1.0 3/27/2016

	@note Solenoids and their functions:
		SolenoidI - Gear Door
			-> Forward extends it
			-> Reverse retracts it
		SolenoidII - Gear Pusher
			-> Forward retracts it
			-> Reverse extends it
		SolenoidIII - No function
		SolenoidIV - Gear/Ball Toggle
			-> Forward pushes upwards
			-> Retract pulls down
*/

#include "GearSystem.h"
#include "../RobotMap.h"
#include "WPILib.h"

GearSystem::GearSystem() : Subsystem("GearSystem") {
	TopToggle = false;

	CompressorPort = new Compressor(0);
	SolenoidI = new DoubleSolenoid(SolenoidIPort, SolenoidIPort+1);
	SolenoidII = new DoubleSolenoid(SolenoidIIPort, SolenoidIIPort+1);
	SolenoidIII = new DoubleSolenoid(SolenoidIIIPort, SolenoidIIIPort+1);
	SolenoidIV = new DoubleSolenoid(SolenoidIVPort, SolenoidIVPort+1);

	LimitSwitch = new DigitalInput(0);
}

/**
	Resets all solenoids to kOff to ensure a
	known configuration.
*/
void GearSystem::Initalize() {
	this->StopAll();
	return;
}

void GearSystem::StopAll() {
	SolenoidI->Set(DoubleSolenoid::Value::kOff);
	SolenoidII->Set(DoubleSolenoid::Value::kOff);
	SolenoidIII->Set(DoubleSolenoid::Value::kOff);
	SolenoidIV->Set(DoubleSolenoid::Value::kOff);
	return;
}

/**
	Enables the compressor
*/
void GearSystem::StartCompressor() {
	CompressorPort->SetClosedLoopControl(true);
	return;
}

/**
	Disables the compressor
*/
void GearSystem::StopCompressor() {
	CompressorPort->SetClosedLoopControl(false);
	return;
}

/**
	Toggles the compressor
*/
void GearSystem::ToggleCompressor() {
	CompressorPort->SetClosedLoopControl(!CompressorPort->GetClosedLoopControl());
	return;
}

/**
	Log where the Gear/Ball toggle is
*/
void GearSystem::Toggle() {
	TopToggle = !TopToggle;
	return;
}
