#include "ZeroWheels.h"

ZeroWheels::ZeroWheels() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(drivetrain);
}

// Called just before this Command runs the first time
void ZeroWheels::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ZeroWheels::Execute() {
	drivetrain->ResetAlignment();
}

// Make this return true when this Command no longer needs to run execute()
bool ZeroWheels::IsFinished() {
	return drivetrain->WheelsAreAligned();
}

// Called once after isFinished returns true
void ZeroWheels::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ZeroWheels::Interrupted() {

}
