#include "AutoDriveAtPeg.h"
#include "PushGearAndBackUP.h"
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
			int Margin = 4;
			if (TargetAngle != 0x00) {
				if (fabs(ceil(TargetAngle - CurrentAngle)) > Margin) {
					CommandBase::debug->LogWithTime("AutoDriveAtPeg", "FMOD info: " + to_string(fmod(TargetAngle, 360)));
					CommandBase::debug->LogWithTime("AutoDriveAtPeg", to_string(TargetAngle) + " " + to_string(CurrentAngle));
					drivetrain->TurnAbout(-45 + fmod(TargetAngle, 360), 0.3);
				} else {
					if (!foundPeg) {
						CommandBase::debug->LogWithTime("AutoDriveAtPeg", "Setting Drive straight reference to " + to_string(drivetrain->Gyro->GetAngle()));
						driveStraightReference = drivetrain->Gyro->GetAngle();
						foundPeg = true;
					}

					CommandBase::debug->LogWithTime("AutoDriveAtPeg", "I am in range!" + to_string(driveStraightReference));
					drivetrain->DriveStraight(0.3, driveStraightReference);
				}
			} else {
				foundPeg = false;
				driveStraightReference = 0;
				CommandBase::debug->LogWithTime("AutoDriveAtPeg", "Cannot find peg: Drive straight");
				drivetrain->DriveStraight(0.3, _driveref);
			}

			//drivetrain->Drive(0.3);

			if (gearsystem->LimitSwitch->Get()) {
				completed = true;
				CommandBase::debug->LogWithTime("AutoDriveAtPeg", "Completed!");

				pushGearAndBackUp->Start();
			}

		} else if (Time > 10 && Time < 11.5) {
			drivetrain->Drive(-0.5);
		} else {
			completed = true;
		}
	} else {
		//The code now needs to push the gear.
		CommandBase::debug->Log("AutoDriveAtPeg", "Starting PushGear");
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
