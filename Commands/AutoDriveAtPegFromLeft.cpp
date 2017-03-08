#include "AutoDriveAtPegFromLeft.h"

bool completed = false;
bool foundPeg = false;
double driveStraightReference = 0;

AutoDriveAtPegFromLeft::AutoDriveAtPegFromLeft() {
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(vt);
}

void AutoDriveAtPegFromLeft::Initialize() {
	drivetrain->ResetAlignment();
	vt->Update();
}

void AutoDriveAtPegFromLeft::Execute() {
	double TargetAngle = vt->FindPeg(), CurrentAngle = drivetrain->Gyro->GetAngle();
	if (TargetAngle) {
		//Peg has been found and we have a valid value.
		int Margin = 5;
		if (ceil(TargetAngle - CurrentAngle) < Margin) {
			foundPeg = false;
			drivetrain->SpinTo(round(fmod(TargetAngle,360)), 0.5);
		} else {
			if (!foundPeg) {
				foundPeg = true;
				driveStraightReference = drivetrain->Gyro->GetAngle();
			}
			drivetrain->DriveStraight(0.3, driveStraightReference);
		}
	} else {
		//Peg couldn't be found. Look for it!
		//The peg should be just to the left,
		//so we'll just drive in that general
		//direction.
		foundPeg = false;
		drivetrain->TurnAbout(-60, 0.3);
	}

	drivetrain->Drive(0.3);

	if (gearsystem->LimitSwitch->Get()) {
		completed = true;
	}
}

bool AutoDriveAtPegFromLeft::IsFinished() {
	return completed;
}

void AutoDriveAtPegFromLeft::End() {
	drivetrain->KillDrive();
	drivetrain->ResetAlignment();
}

void AutoDriveAtPegFromLeft::Interrupted() {
	this->End();
}
