/*
 * DriveTrain.h
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "WPILib.h"
#include <Commands/Subsystem.h>
#include "CANTalon.h"

class DriveTrain: public frc::Subsystem {
public:
	CANTalon *DriveFrontLeftCAN;
	CANTalon *DriveFrontRightCAN;
	CANTalon *DriveBackLeftCAN;
	CANTalon *DriveBackRightCAN;

	Talon *DriveFrontLeft;
	Talon *DriveBackLeft;
	Talon *DriveBackRight;
	Talon *DriveFrontRight;

	DriveTrain();
	void Initialize();
	void Execute();
	void DoAutoAlign(double, double, double, double);
	void ResetAlignment();
	void Drive(double);
	void KillDrive();
	void DriveSpecial(double, double, double, double);
};





#endif /* SRC_SUBSYSTEMS_DRIVETRAIN_H_ */
