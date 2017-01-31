#include "GearSystem.h"
#include "../RobotMap.h"

GearSystem::GearSystem() : Subsystem("GearSystem") {
	frc::Subsystem("GearSystem");

	std::cout << "[gearsystem] GearSystem initializing..." << std::endl;

	PCMCAN = new CANTalon(PCMCANPort);

	SolenoidICAN = new CANTalon(SolenoidICANPort);
	SolenoidIICAN = new CANTalon(SolenoidIICANPort);
	SolenoidIIICAN = new CANTalon(SolenoidIIICANPort);
	SolenoidIVCAN = new CANTalon(SolenoidIVCANPort);

	std::cout << "[gearsystem] GearSystem initialized." << std::endl;

}

void GearSystem::Initalize() {
	return;
}

void GearSystem::Execute() {
	return;
}
