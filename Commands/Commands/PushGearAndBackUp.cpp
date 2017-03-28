#include "PushGearAndBackUp.h"

PushGearAndBackUp::PushGearAndBackUp() {
    Requires(drivetrain);
    Requires(gearsystem);
    AutoTimer = new Timer();
    canExecute = false;
}

void PushGearAndBackUp::Initialize() {
    drivetrain->ResetAlignment();
    drivetrain->Drive(0);
    AutoTimer->Stop();
    AutoTimer->Reset();
    AutoTimer->Start();
    drivetrain->Gyro->Reset();
    canExecute = gearsystem->LimitSwitch->Get();
}

void PushGearAndBackUp::Execute() {
	CommandBase::debug->LogWithTime("PushGearAndBackUp", "Push Gear status: " + to_string(canExecute));
	if (canExecute) {
		double Time = AutoTimer->Get();
		double CurrentAngle = 0;
		if (Time < 0.3) {
			gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kForward);
		} else if (Time > 0.3 && Time < 0.6) {
			gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kReverse);
		} else if (Time > 0.6 && Time < 1.3) {
			gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward);
			gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
		} else if (Time > 1.3 && Time < 2) {
			gearsystem->StopAll();
			drivetrain->Drive(-0.5);
		} else if (Time > 2 && Time < 2.5) {
			drivetrain->ResetAlignment();
			drivetrain->KillDrive();
		}
	}
}

bool PushGearAndBackUp::IsFinished() {
	return (!canExecute && AutoTimer->Get() > 2.4);
}

void PushGearAndBackUp::End() {
	drivetrain->KillDrive();
}

void PushGearAndBackUp::Interrupted() {
	this->End();
}
