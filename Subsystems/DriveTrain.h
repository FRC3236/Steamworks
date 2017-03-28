#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "WPILib.h"
#include <Commands/Subsystem.h>
#include "CANTalon.h"

class DriveTrain: public frc::Subsystem {
private:
	CANTalon *DriveFrontLeftCAN, *DriveFrontRightCAN, *DriveBackLeftCAN, *DriveBackRightCAN;
	Talon *DriveFrontLeft, *DriveBackLeft, *DriveBackRight, *DriveFrontRight;

public:

	ADXRS450_Gyro *Gyro;
	AnalogAccelerometer *Accelerometer;
	DriveTrain();
	void Initialize();
	double GetDeltaAngle(double, double);
	void Execute();
	void DoAutoAlign(double, double, double, double);
	void ResetAlignment();
	void Drive(double);
	void Crawl(double);
	void Crawl(double, double);
	void Traverse(double, double);
	void TurnAbout(double, double);
	void KillDrive();
	void SpinTo(double, double);
	void DriveAlignedTo(double, double);
	void DriveStraight(double, double);
	void SetZeros();
	bool WheelsAreAligned();
	void DriveSpecial(double, double, double, double);
	void KillSpin();
};





#endif /* SRC_SUBSYSTEMS_DRIVETRAIN_H_ */
