#include "AutoDriveAtPegFromLeft.h"


AutoDriveAtPegFromLeft::AutoDriveAtPegFromLeft() {
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(vt);
	Complete = false;
	FoundPeg = false;
	DriveStraightReference = 0;
}

void AutoDriveAtPegFromLeft::Initialize() {
	drivetrain->ResetAlignment();
	vt->Update();
}

void AutoDriveAtPegFromLeft::Execute() {
	double TargetAngle = vt->FindPeg(), CurrentAngle = drivetrain->Gyro->GetAngle();
	if (TargetAngle != 0x00) {
		// Peg has been found and we have a valid value.
		int Margin = 5;
		if (ceil(TargetAngle - CurrentAngle) < Margin) {
			FoundPeg = false;
			drivetrain->SpinTo(round(fmod(TargetAngle,360)), 0.5);
		} else {
			if (!FoundPeg) {
				FoundPeg = true;
				DriveStraightReference = drivetrain->Gyro->GetAngle();
			}
			drivetrain->DriveStraight(0.3, DriveStraightReference);
		}
	} else {
		//Peg couldn't be found. Look for it!
		//The peg should be just to the left,
		//so we'll just drive in that general
		//direction.
		FoundPeg = false;
		drivetrain->TurnAbout(-75, 0.35);
	}

	if (gearsystem->LimitSwitch->Get()) {
		Complete = true;
	}
}

bool AutoDriveAtPegFromLeft::IsFinished() {
	return Complete;
}

void AutoDriveAtPegFromLeft::End() {
	drivetrain->KillDrive();
	drivetrain->ResetAlignment();
}

void AutoDriveAtPegFromLeft::Interrupted() {
	this->End();
}
