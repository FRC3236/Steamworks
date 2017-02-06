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
}

// Called repeatedly when this Command is scheduled to run
// This command presumes that the gear/ball toggle panel is
// extended and ready to block a gear from falling into the
// hopper. It also presumes that the gear fetching panel is
// extended and has a gear placed in it.
void DropGear::Execute() {
	double Time = AutoTimer->Get();
	if (Time < 0.35) {
		gearsystem->SolenoidI->Set(DoubleSolenoid::Value::kReverse);
	} else if (Time > 0.35 && Time < 1) {
		gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
	} else {
		gearsystem->StopAll();
	}
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

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DropGear::Interrupted() {

}
