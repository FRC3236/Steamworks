#include "AutoDriveAtPeg.h"
#include "PushGearAndBackUp.h"
#include <cmath>

using namespace std;

bool completed = false;
bool foundPeg = false;

AutoDriveAtPeg::AutoDriveAtPeg() {
	cout << "AutoDriveAtPeg" << endl;
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(vt);
	AutoTimer = new Timer();
	pushGearAndBackUp = new PushGearAndBackUp();
	cout << "AutoDriveAtPeg2" << endl;
}

// Called just before this Command runs the first time
void AutoDriveAtPeg::Initialize() {
	cout << "Auto init" << endl;
	drivetrain->ResetAlignment();
	AutoTimer->Stop();
	AutoTimer->Reset();
	AutoTimer->Start();
	cout << "Auto init2" << endl;
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
			int Margin = 3;
			if (TargetAngle != 0x00) {
				if (ceil(TargetAngle - CurrentAngle) < Margin) {
					cout << "--------FMOD ANGLE " << fmod(TargetAngle, 360) << endl;
					//drivetrain->Crawl(round(fmod(TargetAngle,360)), 0.5);
				} else {
					if (!foundPeg) {
						driveStraightReference = drivetrain->Gyro->GetAngle();
						foundPeg = true;
					}
					cout << "--------DRIVESTRAIGHTREFERENCE: " << driveStraightReference << endl;
					drivetrain->DriveStraight(0.3, driveStraightReference);
				}
			} else {
				cout << "Can't find the thing!" << endl;
			}

			//drivetrain->Drive(0.3);

			if (gearsystem->LimitSwitch->Get()) {
				completed = true;
			}
		} else if (Time > 10 && Time < 11) {
			drivetrain->Drive(-0.5);
		} else if (Time == 11) {
			TargetAngle = drivetrain->Gyro->GetAngle();
		} else if (Time > 11 && Time < 12) {
			drivetrain->SpinTo(TargetAngle-60, 0.5);
		} else if (Time > 12) {
			drivetrain->TurnAbout(75, 0.5);
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
