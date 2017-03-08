#include "SpinToFromHere.h"

SpinToFromHere::SpinToFromHere(double Target, double Speed) {
	Requires(drivetrain);
	startangle = drivetrain->Gyro->GetAngle();
	target = Target + startangle;
	speed = Speed;

}

// Called just before this Command runs the first time
void SpinToFromHere::Initialize() {
	//gey
}

// Called repeatedly when this Command is scheduled to run
void SpinToFromHere::Execute() {
	drivetrain->SpinTo(this->target, this->speed);
}

// Make this return true when this Command no longer needs to run execute()
bool SpinToFromHere::IsFinished() {
	if (fabs(drivetrain->Gyro->GetAngle()) > fabs(this->target + 2)) { //2 degrees of error
		drivetrain->ResetAlignment();
		drivetrain->Drive(0);
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void SpinToFromHere::End() {
	drivetrain->Drive(0);
	drivetrain->KillSpin();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinToFromHere::Interrupted() {
	this->End();
}
