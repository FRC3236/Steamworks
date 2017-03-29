#include "AutoDriveAtPeg.h"
#include "PushGearAndBackUP.h"
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
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveAtPeg::Execute() {
	double TargetAngle = 0;
	double Time = AutoTimer->Get();
	if (!Completed) {
		if (Time < 10) {
			pair<double, double> info = vt->FindPeg();
			TargetAngle = info.first;
			double SpeedScale = info.second;
			double CurrentAngle = drivetrain->Gyro->GetAngle();
			double driveStraightReference = drivetrain->Gyro->GetAngle();
			int Margin = 4;
			if (TargetAngle != 0x00 && SpeedScale != 0x00) {
				if (fabs(ceil(TargetAngle - CurrentAngle)) > Margin) {
					drivetrain->TurnAbout(-45 + fmod(TargetAngle, 360), 0.3);
				} else {
					if (!FoundPeg) {
						CommandBase::debug->LogWithTime("AutoDriveAtPeg", "Setting Drive straight reference to " + to_string(drivetrain->Gyro->GetAngle()));
						driveStraightReference = drivetrain->Gyro->GetAngle();
						FoundPeg = true;
					}

					CommandBase::debug->LogWithTime("AutoDriveAtPeg", "I am in range!" + to_string(driveStraightReference));
					drivetrain->DriveStraight(0.3, driveStraightReference);
				}
			} else {
				if (SpeedScale != 0x00) {

				} else {
					FoundPeg = false;
					driveStraightReference = 0;
					CommandBase::debug->LogWithTime("AutoDriveAtPeg", "Cannot find peg: Drive straight");
					drivetrain->DriveStraight(0.3, *DriveRef);
				}
			}

			//drivetrain->Drive(0.3);

			if (gearsystem->LimitSwitch->Get()) {
				Completed = true;
				CommandBase::debug->LogWithTime("AutoDriveAtPeg", "Completed!");

				pushGearAndBackUp->Start();
			}

		} else if (Time > 10 && Time < 11.5) {
			drivetrain->Drive(-0.5);
		} else {
			Completed = true;
		}
	} else {
		//The code now needs to push the gear.
		CommandBase::debug->Log("AutoDriveAtPeg", "Starting PushGear");
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
