/*
 * RopeClimber.h
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */

#ifndef ROPECLIMBER_H
#define ROPECLIMBER_H

#include "WPILib.h"
#include <Commands/Subsystem.h>

class RopeClimber: public frc::Subsystem {
public:
	Talon *ClimbTalon;

	RopeClimber();
	void Initialize();
	void Execute();
	void ClimbUp();
	void ClimbDown();
	void Stop();
};



#endif /* SRC_SUBSYSTEMS_ROPECLIMBER_H_ */
