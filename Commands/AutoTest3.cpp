#include "AutoTest3.h"

AutoTest3::AutoTest3() {
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(ropeclimber);
	AutoTimer = new Timer();
}

// Called just before this Command runs the first time
void AutoTest3::Initialize() {
	drivetrain->ResetAlignment();
	AutoTimer->Reset();
	AutoTimer->Start();
	gearsystem->StopAll();
}

// Called repeatedly when this Command is scheduled to run
void AutoTest3::Execute() {
	double Time = AutoTimer->Get();
	if (Time < 1) {
		drivetrain->Drive(0.5);
	} else if (Time >= 1 && Time < 2) {
		drivetrain->DoAutoAlign(0.125,-0.125,0.125,-0.125);
		drivetrain->DriveSpecial(0.5,0.5,0.5,0.5);
	} else if (Time >= 2 && Time < 2.3) {
		drivetrain->Drive(0);
		gearsystem->PushGearOutput();
	} else if (Time >= 2.3 && Time < 2.6) {
		gearsystem->PullGearOutput();
	} else if (Time >= 2.6 && Time < 3) {
		gearsystem->StopAll();
		drivetrain->ResetAlignment();
	} else {
		drivetrain->KillDrive();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoTest3::IsFinished() {
	if (AutoTimer->Get() < 3) {
		return false;
	} else {
		return true;
	}
}

// Called once after isFinished returns true
void AutoTest3::End() {
	drivetrain->KillDrive();
	gearsystem->StopAll();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoTest3::Interrupted() {
	drivetrain->KillDrive();
	gearsystem->StopAll();
}
