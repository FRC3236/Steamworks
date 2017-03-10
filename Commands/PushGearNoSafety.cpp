#include "PushGearNoSafety.h"


PushGearNoSafety::PushGearNoSafety() {
	Requires(gearsystem);
	AutoTimer = new Timer();
	finished = false;
}

// Called just before this Command runs the first time
void PushGearNoSafety::Initialize() {

	AutoTimer->Reset();
	AutoTimer->Start();

}

// Called repeatedly when this Command is scheduled to run
void PushGearNoSafety::Execute() {
	double Time = this->AutoTimer->Get();
	if (Time < 0.3) {
		gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kForward);
	} else if (Time > 0.3 && Time < 0.6) {
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kReverse);
	} else if (Time > 0.6 && Time < 1.3) {
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward);
		gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
	} else if (Time > 1.3) {
		gearsystem->StopAll();
		finished = true;
		this->AutoTimer->Reset();
		this->AutoTimer->Stop();
		this->End();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool PushGearNoSafety::IsFinished() {

	return (AutoTimer->Get() > 1.2);
}

// Called once after isFinished returns true
void PushGearNoSafety::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PushGearNoSafety::Interrupted() {

}
