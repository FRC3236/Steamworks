#include "DropGear.h"
#include "WPILib.h"

DropGear::DropGear() {
	AutoTimer = new Timer();
	Requires(gearsystem);
}

// Called just before this Command runs the first time
void DropGear::Initialize() {
	AutoTimer->Reset();
	AutoTimer->Start();
	return;
}

// Called repeatedly when this Command is scheduled to run

void DropGear::Execute() {
	double Time = AutoTimer->Get();
	std::cout << gearsystem->LimitSwitch->Get() << " :: LIMIT SWITCH" << std::endl;
	if (gearsystem->TopToggle) {
		//Set up the gear door to be ready to accept a gear.
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward); //Close the gear pusher
		gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kForward);
		gearsystem->SolenoidI->Set(DoubleSolenoid::Value::kForward);
	} else {
		//Time the gear system to drop a gear.
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward); //Close the gear pusher
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
bool DropGear::IsFinished() {
	if (AutoTimer->Get() < 1) {
		return false;
	} else {
		return true;
	}
}

// Called once after isFinished returns true
void DropGear::End() {
	gearsystem->Toggle();
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropGear::Interrupted() {
	gearsystem->Toggle();
	return;
}
