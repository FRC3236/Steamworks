/*
 * GearSystem.h
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */

#ifndef GEARSYSTEM_H
#define GEARSYSTEM_H

#include "WPILib.h"
#include <Commands/Subsystem.h>
#include "CANTalon.h"
class GearSystem: public frc::Subsystem {
public:
	CANTalon *SolenoidICAN;
	CANTalon *SolenoidIICAN;
	CANTalon *SolenoidIIICAN;
	CANTalon *SolenoidIVCAN;
	CANTalon *PCMCAN;

	GearSystem();
	void Initalize();
	void Execute();
};



#endif /* SRC_SUBSYSTEMS_GEARSYSTEM_H_ */
