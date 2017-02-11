/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */
#include "DriveTrain.h"
#include "WPILib.h"
#include "../RobotMap.h"

DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	frc::Subsystem("DriveTrain");
	std::cout << "[drivetrain] DriveTrain initializing..." << std::endl;

	Gyro = new AnalogGyro(0);
	Accelerometer = new AnalogAccelerometer(1);

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

	std::cout << "[drivetrain] DriveTrain initialized." << std::endl;
}

void DriveTrain::Initialize() {
	Gyro->Reset();
	Accelerometer->SetSensitivity(0.018);
	Accelerometer->SetZero(0);
	this->ResetAlignment();
	this->Drive(0);
	return;
}

void DriveTrain::Drive(double speed) {

	DriveBackLeft->Set(-speed);
	DriveBackRight->Set(speed);
	DriveFrontLeft->Set(-speed);
	DriveFrontRight->Set(speed);
	return;

}

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

	std::cout << "SWERVEANGLE: " << TurnAngle << std::endl;
	if (fabs(Speed) > JOYSTICKDEADZONE) {
		this->DoAutoAlign(TurnAngle, TurnAngle, TurnAngle, TurnAngle);
		this->Drive(Speed);
	} else {
		this->Drive(0);
		this->ResetAlignment();
	}
}

void DriveTrain::TurnAbout(double Distance, double Speed) {
	double LeftDegree = -0.5*M_1_PI*atanf(7.5/(Distance-7.5));
	double RightDegree = -0.5*M_1_PI*atanf(7.5/(Distance+7.5));
	double Swing = hypotf(7.5, Distance + 7.5)/hypotf(7.5, Distance - 7.5) || 1;
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

	std::cout << "SPEEDS: " << Swing << " " << LeftSpeed << "  " << RightSpeed << std::endl;

	//std::cout << "[drivetrain] Right degree:" << RightDegree << std::endl << "Left Degree: " << LeftDegree << std::endl;
	this->DoAutoAlign(LeftDegree, -LeftDegree, -RightDegree, RightDegree);
	DriveBackLeft->Set(-LeftSpeed);
	DriveBackRight->Set(RightSpeed);
	DriveFrontLeft->Set(-LeftSpeed);
	DriveFrontRight->Set(RightSpeed);
}

double DriveTrain::DegreeToRadian(double Degree) {
	return 360/Degree;
	//return M_PI*Degree/180;
}

void DriveTrain::DoAutoAlign(double DFLA, double DBLA, double DBRA, double DFRA) {

	double CorrectionMultiplier = 9; //frc::SmartDashboard::GetNumber("Wheel Alignment Correction", CorrectionMultiplier);
	double CorrectionAdditive = 0; //frc::SmartDashboard::GetNumber("Wheel Alignment Additive", CorrectionAdditive);

	//std::cout << "CORRECTION NUMBERS:: " << CorrectionMultiplier << " " << CorrectionAdditive << std::endl;

	double TURNMODIFIERCORRECTION = fabs(((DriveBackLeftCAN->GetPosition()-DBLA))*CorrectionMultiplier) + CorrectionAdditive;
	if (DBLA + TURNMARGINOFERROR <= DriveBackLeftCAN->GetPosition() )
	{
		DriveBackLeftCAN->Set(TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else if (DBLA - TURNMARGINOFERROR >= DriveBackLeftCAN->GetPosition() )
	{
		DriveBackLeftCAN->Set(-TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else {
		DriveBackLeftCAN->Set(0.0);
	}
	TURNMODIFIERCORRECTION = fabs(((DriveBackRightCAN->GetPosition()-DBRA))*CorrectionMultiplier)+ CorrectionAdditive;
	if (DBRA + TURNMARGINOFERROR <= DriveBackRightCAN->GetPosition() )
	{
		DriveBackRightCAN->Set(TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else if (DBRA - TURNMARGINOFERROR >= DriveBackRightCAN->GetPosition() )
	{
		DriveBackRightCAN->Set(-TURNVELOCITY * TURNMODIFIERCORRECTION);
	}
	TURNMODIFIERCORRECTION = fabs(((DriveFrontRightCAN->GetPosition()-DFRA))*CorrectionMultiplier)+ CorrectionAdditive;
	if (DFRA + TURNMARGINOFERROR <= DriveFrontRightCAN->GetPosition() )
	{
		DriveFrontRightCAN->Set(TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else if (DFRA - TURNMARGINOFERROR >= DriveFrontRightCAN->GetPosition() )
	{
		DriveFrontRightCAN->Set(-TURNVELOCITY * TURNMODIFIERCORRECTION);
	}
	TURNMODIFIERCORRECTION = fabs(((DriveFrontLeftCAN->GetPosition()-DFLA))*CorrectionMultiplier)+CorrectionAdditive;
	if (DFLA + TURNMARGINOFERROR <= DriveFrontLeftCAN->GetPosition() )
	{
		DriveFrontLeftCAN->Set(TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else if (DFLA - TURNMARGINOFERROR >= DriveFrontLeftCAN->GetPosition() )
	{
		DriveFrontLeftCAN->Set(-TURNVELOCITY * TURNMODIFIERCORRECTION);
	}

	frc::SmartDashboard::PutNumber("Front Left Wheel Angle", DriveFrontLeftCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Front Right Wheel Angle", DriveFrontRightCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Back Left Wheel Angle", DriveBackLeftCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Back Right Wheel Angle", DriveBackRightCAN->GetPosition());
	frc::SmartDashboard::PutNumber("Gyro Angle", Gyro->GetAngle());
	frc::SmartDashboard::PutNumber("Accelerometer Angle", Accelerometer->GetAcceleration());

	return;
}

void DriveTrain::DriveSpecial(double DFLS, double DBLS, double DBRS, double DFRS) {
	DriveFrontLeft->Set(DFLS);
	DriveFrontRight->Set(DFRS);
	DriveBackLeft->Set(DBLS);
	DriveBackRight->Set(DBRS);
	return;
}

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

void DriveTrain::ResetAlignment() {
	this->DoAutoAlign(0,0,0,0);
	return;
}

void DriveTrain::SetZeros() {
	DriveFrontLeftCAN->SetPosition(0);
	DriveFrontRightCAN->SetPosition(0);
	DriveBackLeftCAN->SetPosition(0);
	DriveBackRightCAN->SetPosition(0);
	return;
}

void DriveTrain::KillSpin() {
	DriveFrontLeftCAN->Set(0.0);
	DriveFrontRightCAN->Set(0.0);
	DriveBackLeftCAN->Set(0.0);
	DriveBackRightCAN->Set(0.0);
	return;
}
