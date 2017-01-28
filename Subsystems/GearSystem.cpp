#include "GearSystem.h"
#include "../RobotMap.h"

GearSystem::GearSystem() : Subsystem("GearSystem") {
	frc::Subsystem("GearSystem");

	SolenoidICAN = new CANTalon(SolenoidICANPort);
	SolenoidIICAN = new CANTalon(SolenoidIICANPort);
	SolenoidIIICAN = new CANTalon(SolenoidIIICANPort);
	SolenoidIVCAN = new CANTalon(SolenoidIVCANPort);

}

void GearSystem::Initalize() {
	return;
}

void GearSystem::Execute() {
	return;
}
