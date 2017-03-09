#include "PushGearAndBackUp.h"

PushGearAndBackUp::PushGearAndBackUp() {
    Requires(drivetrain);
    Requires(gearsystem);
    AutoTimer = new Timer();
}

void PushGearAndBackUp::Initialize() {
    drivetrain->ResetAlignment();
    drivetrain->Drive(0);
    AutoTimer->Stop();
    AutoTimer->Reset();
    AutoTimer->Start();
}

void PushGearAndBackUp::Execute() {
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
    } else if (Time == 2) {
    	CurrentAngle = drivetrain->Gyro->GetAngle();
    } else if (Time > 2 && Time < 2.5) {
        drivetrain->SpinTo(CurrentAngle-60, 0.5);
    } else if (Time > 2.5 && Time < 3.5) {
        drivetrain->TurnAbout(75, 0.5);
    }
}

bool PushGearAndBackUp::IsFinished() {
	return false;
}

void PushGearAndBackUp::End() {
	drivetrain->KillDrive();
}

void PushGearAndBackUp::Interrupted() {
	this->End();
}
