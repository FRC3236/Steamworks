/**
	FRC2017
	DriveTrain.cpp
	Purpose: Class for the DriveTrain object

	@author Eric Bernard
	@version 1.4 3/27/2016
*/

#include "DriveTrain.h"
#include "WPILib.h"
#include "../RobotMap.h"

double DFRA, DBLA, DBRA, DFLA = 0;
DriveTrain::DriveTrain() : Subsystem("DriveTrain") {

	Gyro = new ADXRS450_Gyro(frc::SPI::kOnboardCS0);
	Accelerometer = new AnalogAccelerometer(0);

	DriveFrontLeftCAN = new CANTalon(FrontLeftCANPort);
	DriveBackLeftCAN = new CANTalon(BackLeftCANPort);
	DriveFrontRightCAN = new CANTalon(FrontRightCANPort);
	DriveBackRightCAN = new CANTalon(BackRightCANPort);

	DriveBackRightCAN->SetFeedbackDevice(CANTalon::QuadEncoder);
	DriveBackRightCAN->ConfigEncoderCodesPerRev(412.5);
	DriveBackLeftCAN->SetFeedbackDevice(CANTalon::QuadEncoder);
	DriveBackLeftCAN->ConfigEncoderCodesPerRev(412.5);
	DriveFrontRightCAN->SetFeedbackDevice(CANTalon::QuadEncoder);
	DriveFrontRightCAN->ConfigEncoderCodesPerRev(412.5);
	DriveFrontLeftCAN->SetFeedbackDevice(CANTalon::QuadEncoder);
	DriveFrontLeftCAN->ConfigEncoderCodesPerRev(412.5);

	DriveFrontLeft = new Talon(FrontLeftPWMPort);
	DriveFrontRight = new Talon(FrontRightPWMPort);
	DriveBackLeft = new Talon(BackLeftPWMPort);
	DriveBackRight = new Talon(BackRightPWMPort);

	frc::SmartDashboard::PutNumber("Front Left Wheel Angle", DriveFrontLeftCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Front Right Wheel Angle", DriveFrontRightCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Back Left Wheel Angle", DriveBackLeftCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Back Right Wheel Angle", DriveBackRightCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Gyro Angle", Gyro->GetAngle());
	frc::SmartDashboard::PutNumber("Accelerometer Angle", Accelerometer->GetAcceleration());

	this->SetZeros();

}

/**
	Initializes the DriveTrain object. Resets all
	calibrated objects such as the Gyro, and
	stops the DriveTrain from moving.
*/
void DriveTrain::Initialize() {
	Gyro->Calibrate();
	Accelerometer->SetSensitivity(0.018);
	Accelerometer->SetZero(0);
	this->ResetAlignment();
	this->Drive(0);
	return;
}


/**
	Drives the DriveTrain.

	@param speed - speed (in range 0-1) at which
	to drive the DriveTrain 
*/
void DriveTrain::Drive(double speed) {
	this->DriveSpecial(speed,speed,-speed,-speed);

	return;
}

/**
	An alternative traversing method to fully
	controlled traversing.

	@param Angle - the angle at which to crawl
*/
void DriveTrain::Crawl(double Angle) {
	double Speed = 0.4;
	this->DoAutoAlign(Angle, Angle, Angle, Angle);
	this->Drive(Speed);
	return;
}

/**
	An alternative traversing method to fully
	controlled traversing.

	@param Angle - the angle at which to crawl
	@param Speed - the speed at which to crawl
*/
void DriveTrain::Crawl(double Angle, double Speed) {
	this->DoAutoAlign(Angle, Angle, Angle, Angle);
	this->Drive(Speed);
	return;
}

/**
	Advanced traversing for the DriveTrain.

	@param X - x value input from the joysticks
	@param Y - y value input from the joysticks
*/
void DriveTrain::Traverse(double X, double Y) {
	double TurnAngle;
	double Speed;
	if (Y >= 0) {
		TurnAngle = atan2f(-X, Y)/(2*M_PI);
		Speed = hypotf(Y, X)/3;
	} else if (Y < 0) {
		TurnAngle = (atan2f(-X, Y)/(2*M_PI))+0.5;
		Speed = -(hypotf(Y, X)/3);
	} else {
		TurnAngle = 0;
		Speed = 0;
	}
	TurnAngle = fmod(TurnAngle, 360)/360;
	this->DoAutoAlign(TurnAngle, TurnAngle, TurnAngle, TurnAngle);
	if (fabs(Speed) > JOYSTICKDEADZONE) {
		this->DriveSpecial(-Speed,Speed,-Speed,Speed);
	} else {
		this->Drive(0);
	}
	return;
}
/**
	Drives the DriveTrain around a specified turn
	radius.

	@param Radius - radius at which to turn about
	@param Speed - speed at which to drive.
*/
void DriveTrain::TurnAbout(double Radius, double Speed) {
	double LeftDegree = -0.5*M_1_PI*atanf(7.5/(Radius-7.5));
	double RightDegree = -0.5*M_1_PI*atanf(7.5/(Radius+7.5));
	double Swing = hypotf(7.5, Radius + 7.5)/hypotf(7.5, Radius - 7.5) || 1;
	double LeftSpeed;
	double RightSpeed;
	if (Swing > 1) {
		LeftSpeed = Speed;
		RightSpeed = Speed/Swing;
	} else if (Swing < 1) {
		LeftSpeed = Speed*Swing;
		RightSpeed = Speed;
	} else {
		LeftSpeed = Speed;
		RightSpeed = Speed;
	}

	this->DoAutoAlign(LeftDegree, -LeftDegree, -RightDegree, RightDegree);
	this->DriveSpecial(LeftSpeed, LeftSpeed, -RightSpeed, -RightSpeed);
	return;
}

/**
	Drives the DriveTrain straight in accordance
	to the Gyro.

	@param Speed - speed at which to drive
	@param StartAngle - the starting angle at
	which to keep accordance to
*/
void DriveTrain::DriveStraight(double Speed, double StartAngle) {
	//double MarginOfError = 1;
	double DeltaAngle = StartAngle - Gyro->GetAngle();
	std::cout << Speed << std::endl;
	if (fabs(DeltaAngle) < 0.05) {
		this->Drive(Speed);
	} else {
		this->TurnAbout(360/DeltaAngle, Speed);
	}
	return;
}

/**
	Execute the auto-alignment on all four wheels

	@param _DFLA - the desired FrontLeft angle
	@param _DBLA - the desired BackLeft angle
	@param _DBRA - the desired BackRight angle
	@param _DFRA - the desired FrontRight angle
*/
void DriveTrain::DoAutoAlign(double _DFLA, double _DBLA, double _DBRA, double _DFRA) {
	DFLA = _DFLA;
	DFRA = _DFRA;
	DBRA = _DBRA;
	DBLA = _DBLA;

	double CorrectionMultiplier = 8; //frc::SmartDashboard::GetNumber("Wheel Alignment Correction", CorrectionMultiplier);
	//double CorrectionAdditive = 0; //frc::SmartDashboard::GetNumber("Wheel Alignment Additive", CorrectionAdditive);

	//std::cout << "CORRECTION NUMBERS:: " << CorrectionMultiplier << " " << CorrectionAdditive << std::endl;

	double TURNMODIFIERCORRECTION = this->GetDeltaAngle(DriveBackLeftCAN->GetPosition(), DBLA);
	if (fabs(TURNMODIFIERCORRECTION) > TURNMARGINOFERROR) {
		DriveBackLeftCAN->Set(-TURNMODIFIERCORRECTION * CorrectionMultiplier);
	} else {
		DriveBackLeftCAN->Set(0.0);
	}

	TURNMODIFIERCORRECTION = this->GetDeltaAngle(DriveBackRightCAN->GetPosition(), DBRA);
	if (fabs(TURNMODIFIERCORRECTION) > TURNMARGINOFERROR) {
		DriveBackRightCAN->Set(-TURNMODIFIERCORRECTION * CorrectionMultiplier);
	} else {
		DriveBackRightCAN->Set(0.0);
	}

	TURNMODIFIERCORRECTION = this->GetDeltaAngle(DriveFrontRightCAN->GetPosition(), DFRA);
	if (fabs(TURNMODIFIERCORRECTION) > TURNMARGINOFERROR) {
		DriveFrontRightCAN->Set(-TURNMODIFIERCORRECTION * CorrectionMultiplier);
	} else {
		DriveFrontRightCAN->Set(0.0);
	}

	TURNMODIFIERCORRECTION = this->GetDeltaAngle(DriveFrontLeftCAN->GetPosition(), DFLA);
	if (fabs(TURNMODIFIERCORRECTION) > TURNMARGINOFERROR) {
		DriveFrontLeftCAN->Set(-TURNMODIFIERCORRECTION * CorrectionMultiplier);
	} else {
		DriveFrontLeftCAN->Set(0.0);
	}

	frc::SmartDashboard::PutNumber("Front Left Wheel Angle", DriveFrontLeftCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Front Right Wheel Angle", DriveFrontRightCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Back Left Wheel Angle", DriveBackLeftCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Back Right Wheel Angle", DriveBackRightCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Gyro Angle", Gyro->GetAngle());
	frc::SmartDashboard::PutNumber("Accelerometer Angle", Accelerometer->GetAcceleration());

	return;
}

/**
	Returns if the wheels are aligned to where
	they should be

	@return wheels are aligned or not
*/
bool DriveTrain::WheelsAreAligned() {
	double FRA, FLA, BRA, BLA;
	FRA = this->DriveFrontRightCAN->GetPosition();
	FLA = this->DriveFrontLeftCAN->GetPosition();
	BLA = this->DriveBackLeftCAN->GetPosition();
	BRA = this->DriveBackRightCAN->GetPosition();
	double margin = TURNMARGINOFERROR*2;
	return (FRA < margin && FRA > margin) &&
			(FLA < margin && FLA > margin) &&
			(BRA < margin && BRA > margin) &&
			(BLA < margin && BLA > margin);
}


/**
	A more low-level driving function that drives
	each wheel independently of the others.

	@param DFLS - the desired FrontLeft speed
	@param DBLS - the desired BackLeft speed
	@param DBRS - the desired BackRight speed
	@param DFRS - the desired FrontRight speed
*/
void DriveTrain::DriveSpecial(double DFLS, double DBLS, double DBRS, double DFRS) {
	DriveBackLeft->Set(DBLS);
	DriveBackRight->Set(DBRS);
	DriveFrontLeft->Set(DFLS);
	DriveFrontRight->Set(DFRS);

	return;
}

/*
	Spins the robot to face a specified direction
	
	@param Angle - direction the robot wants to face
	@param Speed - power going to each motor
*/
void DriveTrain::SpinTo(double Angle, double Speed) {
	double MarginOfError = 2;
	if (fabs(Angle) > fabs(Gyro->GetAngle())+MarginOfError) {
		this->DoAutoAlign(0.125, -0.125, 0.125, -0.125);
		if (Angle > Gyro->GetAngle()) {
			this->DriveSpecial(Speed,Speed,Speed,Speed);
		} else {
			this->DriveSpecial(-Speed,-Speed,-Speed,-Speed);
		}
	} else {
		this->Drive(0);
		this->ResetAlignment();
	}
	return;
}

/**
	Stops all DriveTrain motors
*/
void DriveTrain::KillDrive() {
	std::cout << "[drivetrain] DriveTrain->KillDrive() has been executed." << std::endl;
	DriveFrontLeftCAN->Set(0.0);
	DriveFrontRightCAN->Set(0.0);
	DriveBackLeftCAN->Set(0.0);
	DriveBackRightCAN->Set(0.0);
	DriveFrontLeft->Set(0);
	DriveFrontRight->Set(0);
	DriveBackLeft->Set(0);
	DriveBackRight->Set(0);
	return;
}

/**
	Resets all wheels to their zero positions
*/
void DriveTrain::ResetAlignment() {
	this->DoAutoAlign(0,0,0,0);
	return;
}

/**
	Sets the zero position of each wheel
*/
void DriveTrain::SetZeros() {
	DriveFrontLeftCAN->SetPosition(0);
	DriveFrontRightCAN->SetPosition(0);
	DriveBackLeftCAN->SetPosition(0);
	DriveBackRightCAN->SetPosition(0);
	return;
}

/**
	Stops all swerve motors
*/
void DriveTrain::KillSpin() {
	DriveFrontLeftCAN->Set(0.0);
	DriveFrontRightCAN->Set(0.0);
	DriveBackLeftCAN->Set(0.0);
	DriveBackRightCAN->Set(0.0);
	return;
}

/**
	Gets the distance of two angles

	@param Current - the current angle
	@param Target - the target angle
	@return the distance between the two angles
*/
double DriveTrain::GetDeltaAngle(double Current, double Target) {
	Current = fmod(Current,1);
	Target = fmod(Target, 1);
	double Delta1 = Target - Current;
	double Delta2 = Delta1 + 1;
	double Delta3 = Delta1 - 1;
	return fabs(Delta1)<fmin(fabs(Delta2),fabs(Delta3))?Delta1:fabs(Delta2)<fabs(Delta3)?Delta2:Delta3;
}
