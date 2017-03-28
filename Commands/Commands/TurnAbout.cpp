#include "TurnAbout.h"

TurnAbout::TurnAbout(double Distance, double Speed) {
	Requires(drivetrain);
	distance = Distance;
	speed = Speed;
}

// Called just before this Command runs the first time
void TurnAbout::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TurnAbout::Execute() {
	drivetrain->TurnAbout(this->distance, this->speed);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnAbout::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TurnAbout::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnAbout::Interrupted() {

}
