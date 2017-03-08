#include "Test.h"

Test::Test(double timeout) : TimedCommand(timeout) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void Test::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void Test::Execute() {

}

// Called once after command times out
void Test::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Test::Interrupted() {

}
