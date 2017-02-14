#include "GearSystem.h"
#include "../RobotMap.h"
#include "WPILib.h"

GearSystem::GearSystem() : Subsystem("GearSystem") {
	frc::Subsystem("GearSystem");

	std::cout << "[gearsystem] GearSystem initializing..." << std::endl;

	//Solenoid1 is Extending Gear Slot - forward extends it out, reverse pulls it in
	//Solenoid2 extends gear pusher - reverse extends it, forward retracts it
	//Solenoid3 does nothing
	//Solenoid4 is the gear/ball toggle - forward is up, reverse is down.

	TopToggle = false;

	CompressorPort = new Compressor(0);
	SolenoidI = new DoubleSolenoid(SolenoidIPort, SolenoidIPort+1);
	SolenoidII = new DoubleSolenoid(SolenoidIIPort, SolenoidIIPort+1);
	SolenoidIII = new DoubleSolenoid(SolenoidIIIPort, SolenoidIIIPort+1);
	SolenoidIV = new DoubleSolenoid(SolenoidIVPort, SolenoidIVPort+1);

	LimitSwitch = new DigitalInput(0);

	std::cout << "[gearsystem] GearSystem initialized." << std::endl;

}

void GearSystem::Initalize() {
	SolenoidI->Set(DoubleSolenoid::Value::kOff);
	SolenoidII->Set(DoubleSolenoid::Value::kOff);
	SolenoidIII->Set(DoubleSolenoid::Value::kOff);
	SolenoidIV->Set(DoubleSolenoid::Value::kOff);
	return;
}

void GearSystem::Execute() {
	return;
}

void GearSystem::StopAll() {
	SolenoidI->Set(DoubleSolenoid::Value::kOff);
	SolenoidII->Set(DoubleSolenoid::Value::kOff);
	SolenoidIII->Set(DoubleSolenoid::Value::kOff);
	SolenoidIV->Set(DoubleSolenoid::Value::kOff);
}

void GearSystem::StartCompressor() {
	CompressorPort->SetClosedLoopControl(true);
}

void GearSystem::StopCompressor() {
	CompressorPort->SetClosedLoopControl(false);
}

void GearSystem::ToggleCompressor() {
	CompressorPort->SetClosedLoopControl(!CompressorPort->GetClosedLoopControl());
}

void GearSystem::Toggle() {
	TopToggle = !TopToggle;
}
