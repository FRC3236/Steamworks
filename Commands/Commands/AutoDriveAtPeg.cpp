#include "AutoDriveAtPeg.h"
#include "PushGearAndBackUp.h"
#include <cmath>

using namespace std;
using namespace frc;

AutoDriveAtPeg::AutoDriveAtPeg() {
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(vt);
	Completed = false;
	FoundPeg = false;
	DriveRef = 0;
	AutoTimer = new Timer();
	pushGearAndBackUp = new PushGearAndBackUp();
}

// Called just before this Command runs the first time
void AutoDriveAtPeg::Initialize() {
	drivetrain->ResetAlignment();
	AutoTimer->Stop();
	AutoTimer->Reset();
	AutoTimer->Start();
	*DriveRef = drivetrain->Gyro->GetAngle();
	drivetrain->SetStraightReference();
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveAtPeg::Execute() {
	double Time = AutoTimer->Get();
	if (Time < 10 && !Completed) {
		pair<double,double> VTInfo = vt->FindPeg();
		double PegLoc = VTInfo.first;
		double SpeedScale = VTInfo.second;
		if (PegLoc != 0x00 && SpeedScale != 0x00) {
			SpeedScale = fmax(0.15, SpeedScale);
			drivetrain->TurnAbout(-45 + fmod(PegLoc, 360), SpeedScale);
		} else {
			drivetrain->DriveStraight(0.2);
			if (Time > 5) {
				Completed = true;
				this->End();
			}
		}
		if (gearsystem->LimitSwitch->Get()) {
			Completed = true;
			this->End();
			pushGearAndBackUp->Start();
		}
	}
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveAtPeg::IsFinished() {
	return Completed;
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
