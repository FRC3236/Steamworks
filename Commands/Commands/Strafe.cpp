#include "Strafe.h"

Strafe::Strafe(double Angle=0.5) {
	Requires(drivetrain);
	angle = Angle;
}

// Called just before this Command runs the first time
void Strafe::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Strafe::Execute() {
	drivetrain->Crawl(this->angle);
}

// Make this return true when this Command no longer needs to run execute()
bool Strafe::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Strafe::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Strafe::Interrupted() {

}
