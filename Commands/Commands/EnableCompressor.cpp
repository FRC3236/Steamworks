#include "EnableCompressor.h"

EnableCompressor::EnableCompressor() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(gearsystem);
}

// Called just before this Command runs the first time
void EnableCompressor::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void EnableCompressor::Execute() {
	gearsystem->StartCompressor();
}

// Make this return true when this Command no longer needs to run execute()
bool EnableCompressor::IsFinished() {
	return gearsystem->CompressorPort->Enabled();
}

// Called once after isFinished returns true
void EnableCompressor::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void EnableCompressor::Interrupted() {

}
