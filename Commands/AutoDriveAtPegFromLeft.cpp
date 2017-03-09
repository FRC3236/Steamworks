#include "AutoDriveAtPegFromRight.h"

bool Rcompleted = false;
bool RfoundPeg = false;
double RdriveStraightReference = 0;

AutoDriveAtPegFromRight::AutoDriveAtPegFromRight() {
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(vt);
}

void AutoDriveAtPegFromRight::Initialize() {
	drivetrain->ResetAlignment();
	vt->Update();
}

void AutoDriveAtPegFromRight::Execute() {
	double TargetAngle = vt->FindPeg(), CurrentAngle = drivetrain->Gyro->GetAngle();
	if (TargetAngle) {
		//Peg has been found and we have a valid value.
		int Margin = 5;
		if (ceil(TargetAngle - CurrentAngle) < Margin) {
			RfoundPeg = false;
			drivetrain->SpinTo(round(fmod(TargetAngle,360)), 0.5);
		} else {
			if (!RfoundPeg) {
				RfoundPeg = true;
				RdriveStraightReference = drivetrain->Gyro->GetAngle();
			}
			drivetrain->DriveStraight(0.3, RdriveStraightReference);
		}
	} else {
		//Peg couldn't be found. Look for it!
		//The peg should be just to the left,
		//so we'll just drive in that general
		//direction.
		RfoundPeg = false;
		drivetrain->TurnAbout(60, 0.3);
	}

	drivetrain->Drive(0.3);

	if (gearsystem->LimitSwitch->Get()) {
		Rcompleted = true;
	}
}

bool AutoDriveAtPegFromRight::IsFinished() {
	return Rcompleted;
}

void AutoDriveAtPegFromRight::End() {
	drivetrain->KillDrive();
	drivetrain->ResetAlignment();
}

void AutoDriveAtPegFromRight::Interrupted() {
	this->End();
}
