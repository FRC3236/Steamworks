#include "AutoDriveAtPegFromLeft.h"
#include "PushGearAndBackUp.h"
#include <cmath>

using namespace std;
using namespace frc;

AutoDriveAtPegFromLeft::AutoDriveAtPegFromLeft() {
	Requires(drivetrain);
	Requires(gearsystem);
	Requires(vt);
	Completed = false;
	FoundPeg = false;
	DriveRef = 0;
	AutoTimer = new Timer();
	pushGearAndBackUp = new PushGearAndBackUp();
}

void AutoDriveAtPegFromLeft::Initialize() {
	drivetrain->ResetAlignment();
	AutoTimer->Stop();
	AutoTimer->Reset();
	AutoTimer->Start();
	drivetrain->SetStraightReference();
	return;
}

void AutoDriveAtPegFromLeft::Execute() {
	double Time = AutoTimer->Get();
	if (Time < 10 && !Completed) {
		pair<double, double> VTInfo = vt->FindPeg();
		double PegLoc = VTInfo.first;
		double SpeedScale = VTInfo.second;
		if (PegLoc != 0x00 && SpeedScale != 0x00) {
			if (!FoundPeg) {
				FoundPeg = true;
				drivetrain->SetStraightReference();
			}
			//We see the peg and know how fast to drive.
			SpeedScale = fmax(0.15, SpeedScale);
			drivetrain->TurnAbout(-45 + fmod(PegLoc, 360), SpeedScale);
		} else {
			if (!FoundPeg) {
				drivetrain->TurnAbout(77, 0.5);
				if (Time > 5 && !FoundPeg) {
					Completed = true;
					this->End();
				}
			} else {
				drivetrain->DriveStraight(0.25);
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

bool AutoDriveAtPegFromLeft::IsFinished() {
	return Completed;
}

void AutoDriveAtPegFromLeft::End() {
	drivetrain->KillDrive();
	drivetrain->ResetAlignment();
	return;
}

void AutoDriveAtPegFromLeft::Interrupted() {
	this->End();
	return;
}