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
	CANTalon *DriveFrontLeftCAN, *DriveFrontRightCAN, *DriveBackLeftCAN, *DriveBackRightCAN;
	Talon *DriveFrontLeft, *DriveBackLeft, *DriveBackRight, *DriveFrontRight;

	AnalogGyro *Gyro;
	AnalogAccelerometer *Accelerometer;

	DriveTrain();
	void Initialize();
	void Execute();
	void DoAutoAlign(double, double, double, double);
	void ResetAlignment();
	void Drive(double);
	void Traverse(double, double);
	void TurnAbout(double, double);
	void KillDrive();
	void SetZeros();
	void DriveSpecial(double, double, double, double);
	void KillSpin();
	double DegreeToRadian(double);
};





#endif /* SRC_SUBSYSTEMS_DRIVETRAIN_H_ */
