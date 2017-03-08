#include "AutoDriveAtPeg.h"
#include <cmath>

using namespace std;

bool completed = false;

AutoDriveAtPeg::AutoDriveAtPeg() {
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(vt);
}

// Called just before this Command runs the first time
void AutoDriveAtPeg::Initialize() {
	drivetrain->ResetAlignment();

}

// Called repeatedly when this Command is scheduled to run
void AutoDriveAtPeg::Execute() {
	double TargetAngle = vt->FindPeg();
	double CurrentAngle = drivetrain->Gyro->GetAngle();
	int Margin = 5;
	if (TargetAngle) {
		if (ceil(TargetAngle - CurrentAngle) < Margin) {
			drivetrain->SpinTo(round(fmod(TargetAngle,360)), 0.5);
		}
	}

	drivetrain->Drive(0.3);

	if (gearsystem->LimitSwitch->Get()) {
		completed = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveAtPeg::IsFinished() {
	return completed;
}

// Called once after isFinished returns true
void AutoDriveAtPeg::End() {
	drivetrain->KillDrive();
	drivetrain->ResetAlignment();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveAtPeg::Interrupted() {
	this->End();
}
