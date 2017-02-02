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
	DoubleSolenoid *SolenoidI;
	DoubleSolenoid *SolenoidII;
	DoubleSolenoid *SolenoidIII;
	DoubleSolenoid *SolenoidIV;

	Compressor *CompressorPort;
	//CANTalon *PCMCAN;

	GearSystem();
	void Initalize();
	void Execute();
	void ExtendGearInput();
	void RetractGearInput();
	void PushGearOutput();
	void PullGearOutput();
	void RunTest();
	void StopAll();
};



#endif /* SRC_SUBSYSTEMS_GEARSYSTEM_H_ */
