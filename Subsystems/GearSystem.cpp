#include "GearSystem.h"
#include "../RobotMap.h"
#include "WPILib.h"

GearSystem::GearSystem() : Subsystem("GearSystem") {
	frc::Subsystem("GearSystem");

	std::cout << "[gearsystem] GearSystem initializing..." << std::endl;

	//Solenoid1 is Extending Gear Slot - forward
	//Solenoid2 extends gear pusher - reverse
	//Solenoid3 does nothing
	//Solenoid4 is the gear/ball toggle

	//PCMCAN = new CANTalon(PCMCANPort);
	CompressorPort = new Compressor(0);
	std::cout << "[gearsystem] Compressor test: " << CompressorPort->Enabled() << " " << CompressorPort->GetCompressorCurrent() << std::endl;
	SolenoidI = new DoubleSolenoid(SolenoidIPort, SolenoidIPort+1);
	SolenoidII = new DoubleSolenoid(SolenoidIIPort, SolenoidIIPort+1);
	SolenoidIII = new DoubleSolenoid(SolenoidIIIPort, SolenoidIIIPort+1);
	SolenoidIV = new DoubleSolenoid(SolenoidIVPort, SolenoidIVPort+1);

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

void GearSystem::ExtendGearInput() {
	SolenoidI->Set(DoubleSolenoid::Value::kForward);
}

void GearSystem::RetractGearInput() {
	SolenoidI->Set(DoubleSolenoid::Value::kReverse);
}

void GearSystem::PushGearOutput() {
	SolenoidII->Set(DoubleSolenoid::Value::kReverse);
}

void GearSystem::PullGearOutput() {
	SolenoidII->Set(DoubleSolenoid::Value::kForward);
}

void GearSystem::StopAll() {
	SolenoidI->Set(DoubleSolenoid::Value::kOff);
	SolenoidII->Set(DoubleSolenoid::Value::kOff);
	SolenoidIII->Set(DoubleSolenoid::Value::kOff);
	SolenoidIV->Set(DoubleSolenoid::Value::kOff);
}
