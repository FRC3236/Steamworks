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

	ADXRS450_Gyro *Gyro;
	AnalogAccelerometer *Accelerometer;

	DriveTrain();
	void Initialize();
	double GetDeltaAngle(double, double);
	double GetDeltaAngle2(double, double);
	void Execute();
	void DoAutoAlign(double, double, double, double);
	void DoAutoAlign2(double, double, double, double);
	void ResetAlignment();
	void Drive(double);
	void Drive2(double);
	void Crawl(double);
	void TraverseSimple(double);
	void Traverse(double, double);
	void Traverse2(double, double);
	void TurnAbout(double, double);
	void KillDrive();
	void SpinTo(double, double);
	void DriveAlignedTo(double, double);
	void DriveStraight(double, double);
	void SetZeros();
	bool WheelsAreAligned();
	void DriveSpecial(double, double, double, double);
	void KillSpin();
	double DegreeToRadian(double);
};





#endif /* SRC_SUBSYSTEMS_DRIVETRAIN_H_ */
