#include "AutoTest2.h"

AutoTest2::AutoTest2() {
	AutoTimer = new Timer();
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(ropeclimber);
}

// Called just before this Command runs the first time
void AutoTest2::Initialize() {
	drivetrain->ResetAlignment();
	AutoTimer->Reset();
	AutoTimer->Start();
}

// Called repeatedly when this Command is scheduled to run
void AutoTest2::Execute() {
	double Time = AutoTimer->Get();
	if (Time < 1) {
		drivetrain->Drive(0.25);
	} else if (Time >= 1 && Time < 2) {
		drivetrain->DoAutoAlign(0.125, -0.125, 0.125, -0.125);
		drivetrain->DriveSpecial(0.5, 0.5, 0.5, 0.5);
	} else if (Time >= 2 && Time < 2.5) {
		drivetrain->DoAutoAlign(0,0,0,0);
	} else {
		drivetrain->KillDrive();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoTest2::IsFinished() {
	if (AutoTimer->Get() < 2.5) {
		return false;
	} else {
		return true;
	}
}

// Called once after isFinished returns true
void AutoTest2::End() {
	drivetrain->KillDrive();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoTest2::Interrupted() {
	drivetrain->KillDrive();
}
