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

class GearSystem: public frc::Subsystem {
private:

public:


	DoubleSolenoid *SolenoidI;
	DoubleSolenoid *SolenoidII;
	DoubleSolenoid *SolenoidIII;
	DoubleSolenoid *SolenoidIV;

	Compressor *CompressorPort;

	bool TopToggle;
	DigitalInput *LimitSwitch;
	GearSystem();
	void Initalize();
	void StopAll();
	void StartCompressor();
	void StopCompressor();
	void ToggleCompressor();
	void Toggle(); //For toggling the commands
};



#endif /* SRC_SUBSYSTEMS_GEARSYSTEM_H_ */
