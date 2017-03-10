#include "AutoDriveAtPeg.h"
#include "PushGearAndBackUp.h"
#include <cmath>

using namespace std;

bool completed = false;
bool foundPeg = false;
double _driveref = 0;

AutoDriveAtPeg::AutoDriveAtPeg() {
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(vt);
	AutoTimer = new Timer();
	pushGearAndBackUp = new PushGearAndBackUp();
}

// Called just before this Command runs the first time
void AutoDriveAtPeg::Initialize() {
	drivetrain->ResetAlignment();
	AutoTimer->Stop();
	AutoTimer->Reset();
	AutoTimer->Start();
	_driveref = drivetrain->Gyro->GetAngle();
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveAtPeg::Execute() {
	double TargetAngle = 0;
	double Time = AutoTimer->Get();
	if (!completed) {
		if (Time < 10) {
			double TargetAngle = vt->FindPeg();
			double CurrentAngle = drivetrain->Gyro->GetAngle();
			double driveStraightReference = drivetrain->Gyro->GetAngle();
			int Margin = 2;
			if (TargetAngle != 0x00) {
				if (fabs(ceil(TargetAngle - CurrentAngle)) > Margin) {
					CommandBase::debug->LogWithTime("AutoDriveAtPeg", "FMOD info: " + to_string(fmod(TargetAngle, 360)));
					CommandBase::debug->LogWithTime("AutoDriveAtPeg", to_string(TargetAngle) + " " + to_string(CurrentAngle));
					drivetrain->Crawl(fmod(TargetAngle,360), 0.5);
				} else {
					if (!foundPeg) {
						driveStraightReference = drivetrain->Gyro->GetAngle();
						foundPeg = true;
					}

					CommandBase::debug->LogWithTime("AutoDriveAtPeg", "I am in range!" + to_string(driveStraightReference));
					drivetrain->Drive(0.3);
				}
			} else {
				foundPeg = false;
				driveStraightReference = 0;
				CommandBase::debug->LogWithTime("VisionTracking", "Cannot find peg: Drive straight");
				drivetrain->DriveStraight(0.3, _driveref);
			}

			//drivetrain->Drive(0.3);

			if (gearsystem->LimitSwitch->Get()) {
				completed = true;
			}
		}
	} else {
		//The code now needs to push the gear.
		pushGearAndBackUp->Start();
	}
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveAtPeg::IsFinished() {
	return completed;
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
