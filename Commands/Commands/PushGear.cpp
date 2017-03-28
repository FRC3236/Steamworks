#include <Commands/Command.h>
#include <Commands/Scheduler.h>

#include "PushGear.h"
#include "../../CommandBase.h"
#include "../../RobotMap.h"
#include "WPILib.h"
#include "DropGear.h"

#include "PushGear.h"
#include "DisableCompressor.h"
#include "EnableCompressor.h"
#include <cmath>

PushGear::PushGear() {
	AutoTimer = new Timer();
	Requires(gearsystem);
	startedtimer = false;
	finished = false;
	enabled = true;

}

// Called just before this Command runs the first time
void PushGear::Initialize() {

	//Determine if the command can run
	enabled = gearsystem->LimitSwitch->Get();

	this->AutoTimer->Start();
	this->finished = false;
	return;
}

// Called repeatedly when this Command is scheduled to run
void PushGear::Execute() {

	double Time = this->AutoTimer->Get();
	if (enabled) {

		if (Time < 0.3) {
			gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kForward);
		} else if (Time > 0.3 && Time < 0.6) {
			gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kReverse);
		} else if (Time > 0.6 && Time < 1.3) {
			gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward);
			gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
		} else if (Time > 1.3) {
			gearsystem->StopAll();
			this->finished = true;
			this->AutoTimer->Reset();
			this->AutoTimer->Stop();
			this->startedtimer = false;
			this->End();
		}
	} else {
		if (Time < 0.2) {
			gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward);
			gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
		} else {
			gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kOff);
			gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kOff);
			this->finished = true;
			this->AutoTimer->Reset();
			this->AutoTimer->Stop();
			this->startedtimer = false;
		}
	}
	return;
}

// Make this return true when this Command no longer needs to run execute()
bool PushGear::IsFinished() {
	return this->finished;
}

// Called once after isFinished returns true
void PushGear::End() {
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PushGear::Interrupted() {
	this->End();
	return;
}
