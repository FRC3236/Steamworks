#include "AutoMoveForward.h"

AutoMoveForward::AutoMoveForward() {
	AutoTimer = new Timer();
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(ropeclimber);
}

// Called just before this Command runs the first time
void AutoMoveForward::Initialize() {

	frc::SmartDashboard::PutNumber("Autonomous Time", AutoTimer->Get());
	drivetrain->ResetAlignment();
	AutoTimer->Reset();
	AutoTimer->Start();
}

// Called repeatedly when this Command is scheduled to run
void AutoMoveForward::Execute() {
	if (AutoTimer->Get() < 4.7) {
		drivetrain->Drive(0.3);
		double CorrectionAngle = drivetrain->DegreeToRadian(drivetrain->Gyro->GetAngle());
		drivetrain->DoAutoAlign(CorrectionAngle, -CorrectionAngle, -CorrectionAngle, CorrectionAngle);
	} else if (AutoTimer->Get() > 4.7 && AutoTimer->Get() < 5.5) {
		drivetrain->ResetAlignment();
	} else {
		drivetrain->KillDrive();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoMoveForward::IsFinished() {
	if (AutoTimer->Get() < 5.5) {
		return false;
	} else {
		return true;
	}
}

// Called once after isFinished returns true
void AutoMoveForward::End() {
	drivetrain->KillDrive();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoMoveForward::Interrupted() {
	drivetrain->KillDrive();
}
