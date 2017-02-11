#include "PushGear.h"

PushGear::PushGear() {
	AutoTimer = new Timer();
	Requires(gearsystem);
}

// Called just before this Command runs the first time
void PushGear::Initialize() {
	AutoTimer->Reset();
	AutoTimer->Start();
	return;
}

// Called repeatedly when this Command is scheduled to run
void PushGear::Execute() {
	double Time = AutoTimer->Get();
	if (Time < 0.3) {
		gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kForward);
	} else if (Time > 0.3 && Time < 0.6) {
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kReverse);
	} else if (Time > 0.6 && Time < 1.3) {
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward);
		gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
	} else {
		gearsystem->StopAll();
	}
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool PushGear::IsFinished() {
	if (AutoTimer->Get() < 1.3) {
		return false;
	} else {
		return true;
	}
}

// Called once after isFinished returns true
void PushGear::End() {
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PushGear::Interrupted() {
	return;
}
