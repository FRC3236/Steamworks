#include "AutoPushGear.h"

AutoPushGear::AutoPushGear() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(gearsystem);
}

// Called just before this Command runs the first time
void AutoPushGear::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AutoPushGear::Execute() {
	if (gearsystem->LimitSwitch->Get()) {

	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoPushGear::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutoPushGear::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoPushGear::Interrupted() {

}
