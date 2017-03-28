#include "PushGearAndBackUpNoSafety.h"
#include "WPILib.h"


PushGearAndBackUpNoSafety::PushGearAndBackUpNoSafety() {
    Requires(drivetrain);
    Requires(gearsystem);
    AutoTimer = new Timer();
}

void PushGearAndBackUpNoSafety::Initialize() {
    drivetrain->ResetAlignment();
    drivetrain->Drive(0);
    AutoTimer->Stop();
    AutoTimer->Reset();
    AutoTimer->Start();
}

void PushGearAndBackUpNoSafety::Execute() {
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
    	drivetrain->KillDrive();
    }
}

bool PushGearAndBackUpNoSafety::IsFinished() {
	return AutoTimer->Get() > 2.4;
}

void PushGearAndBackUpNoSafety::End() {
	drivetrain->KillDrive();
}

void PushGearAndBackUpNoSafety::Interrupted() {
	this->End();
}
