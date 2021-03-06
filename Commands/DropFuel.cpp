#include "DropFuel.h"
#include "WPILib.h"

DropFuel::DropFuel() {
	AutoTimer = new Timer();
	Requires(gearsystem);
}

// Called just before this Command runs the first time
void DropFuel::Initialize() {
	AutoTimer->Reset();
	AutoTimer->Start();
	return;
}

// Called repeatedly when this Command is scheduled to run

void DropFuel::Execute() {
	double Time = AutoTimer->Get();
	if (gearsystem->TopToggle) {
		//Set up the gear door to be ready to accept a gear.
		gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
		gearsystem->SolenoidI->Set(DoubleSolenoid::Value::kForward);
	} else {
		//Time the gear system to drop a gear.
		if (Time < 0.35) {
			gearsystem->SolenoidI->Set(DoubleSolenoid::Value::kReverse);
		} else if (Time > 0.39 && Time < 1) {
			gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
		} else {
			gearsystem->StopAll();
		}
	}
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool DropFuel::IsFinished() {
	if (AutoTimer->Get() < 1) {
		return false;
	} else {
		return true;
	}
}

// Called once after isFinished returns true
void DropFuel::End() {
	gearsystem->Toggle();
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropFuel::Interrupted() {
	gearsystem->Toggle();
	return;
}
