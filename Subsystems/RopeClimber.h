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
private:
	Talon *ClimbLeftTalon;
	Talon *ClimbRightTalon;

public:
	RopeClimber();
	void Initialize();
	void Execute();
	void ClimbUp(double);
	void ClimbDown(double);
	void Stop();
	void Climb(double);
};



#endif /* SRC_SUBSYSTEMS_ROPECLIMBER_H_ */
