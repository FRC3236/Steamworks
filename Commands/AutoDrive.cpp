#include "AutoDrive.h"

double speed;
double startangle;
AutoDrive::AutoDrive(double Speed) {
	Requires(drivetrain);
	Requires(gearsystem);
	speed = Speed;
}

// Called just before this Command runs the first time
void AutoDrive::Initialize() {
	startangle = drivetrain->Gyro->GetAngle();
}

// Called repeatedly when this Command is scheduled to run
void AutoDrive::Execute() {
	drivetrain->DriveStraight(-speed, startangle);
	if (gearsystem->LimitSwitch->Get()) {
		this->End();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDrive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutoDrive::End() {
	drivetrain->Drive(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDrive::Interrupted() {
	drivetrain->Drive(0);
}
