#include <Commands/Command.h>
#include <Commands/Scheduler.h>

#include "PushGear.h"

#include "../CommandBase.h"
#include "../RobotMap.h"
#include "WPILib.h"
#include "DropGear.h"
#include "DropFuel.h"
#include "PushGear.h"
#include "DisableCompressor.h"
#include "EnableCompressor.h"
#include <cmath>

PushGear::PushGear(bool Safety) {
	AutoTimer = new Timer();
	Requires(gearsystem);
	startedtimer = false;
	finished = false;
	safety = Safety;
}

// Called just before this Command runs the first time
void PushGear::Initialize() {
	this->AutoTimer->Start();
	this->finished = false;
	return;
}

// Called repeatedly when this Command is scheduled to run
void PushGear::Execute() {
	std::cout << "PUSHGEAR: " << gearsystem->LimitSwitch->Get() << std::endl << std::endl;
	if (gearsystem->LimitSwitch->Get() == 0 || !this->safety) {
		if (!this->startedtimer) {
			this->finished = false;
			this->AutoTimer->Reset();
			this->AutoTimer->Start();
			this->startedtimer = true;
		}
		double Time = this->AutoTimer->Get();

		if (Time < 0.3) {
			gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kForward);
		} else if (Time > 0.3 && Time < 0.6) {
			gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kReverse);
		} else if (Time > 0.6 && Time < 1.3) {
			gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward);
			gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
		} else if (Time > 1.3) {
			std::cout << "RESET TIMER 1" << std::endl;
			gearsystem->StopAll();
			this->finished = true;
			this->AutoTimer->Reset();
			this->AutoTimer->Stop();
			this->startedtimer = false;
			this->End();
		}
	} else {
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward);
		gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
		std::cout << "RESET TIMER 2" << std::endl;
		this->finished = true;
		this->AutoTimer->Reset();
		this->AutoTimer->Stop();
		this->startedtimer = false;
	}
	return;
	//reverting to the old command just for functionality.
	/*double Time = this->AutoTimer->Get();

	if (Time < 0.3) {
		gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kForward);
	} else if (Time > 0.3 && Time < 0.6) {
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kReverse);
	} else if (Time > 0.6 && Time < 1.3) {
		gearsystem->SolenoidII->Set(DoubleSolenoid::Value::kForward);
		gearsystem->SolenoidIV->Set(DoubleSolenoid::Value::kReverse);
	} else if (Time > 1.3) {
		std::cout << "RESET TIMER 1" << std::endl;
		gearsystem->StopAll();
		this->finished = true;
		this->End();
	}*/
}

// Make this return true when this Command no longer needs to run execute()
bool PushGear::IsFinished() {
	return this->finished;
}

// Called once after isFinished returns true
void PushGear::End() {
	std::cout << "RESET TIMER 3" << std::endl;
	//this->AutoTimer->Reset();
	//this->AutoTimer->Stop();
	//this->startedtimer = false;
	return;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PushGear::Interrupted() {
	return;
}
