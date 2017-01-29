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
	std::cout << "[drivetrain] DriveTrain initialized." << std::endl;
}

void DriveTrain::Initialize() {
	this->DoAutoAlign(0,0,0,0);
	this->Drive(0);
}

void DriveTrain::Drive(double speed) {

	DriveBackLeft->Set(speed);
	DriveBackRight->Set(-speed);
	DriveFrontLeft->Set(speed);
	DriveFrontRight->Set(-speed);
	std::cout << "Drive! " << speed << std::endl;
	return;

}

void DriveTrain::DoAutoAlign(double DFLA, double DBLA, double DBRA, double DFRA) {
	double TURNMODIFIERCORRECTION = fabs(((DriveBackLeftCAN->GetPosition()-DBLA))*6) + 0.1;
	if (DBLA + TURNMARGINOFERROR <= DriveBackLeftCAN->GetPosition() )
	{
		DriveBackLeftCAN->Set(TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else if (DBLA - TURNMARGINOFERROR >= DriveBackLeftCAN->GetPosition() )
	{
		DriveBackLeftCAN->Set(-TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else {
		DriveBackLeftCAN->Set(0.0);
	}
	TURNMODIFIERCORRECTION = fabs(((DriveBackRightCAN->GetPosition()-DBRA))*6) + 0.1;
	if (DBRA + TURNMARGINOFERROR <= DriveBackRightCAN->GetPosition() )
	{
		DriveBackRightCAN->Set(TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else if (DBRA - TURNMARGINOFERROR >= DriveBackRightCAN->GetPosition() )
	{
		DriveBackRightCAN->Set(-TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else {
		DriveBackRightCAN->Set(0.0);
	}
	TURNMODIFIERCORRECTION = fabs(((DriveFrontRightCAN->GetPosition()-DFRA))*6) + 0.1;
	if (DFRA + TURNMARGINOFERROR <= DriveFrontRightCAN->GetPosition() )
	{
		DriveFrontRightCAN->Set(TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else if (DFRA - TURNMARGINOFERROR >= DriveFrontRightCAN->GetPosition() )
	{
		DriveFrontRightCAN->Set(-TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else {
		DriveFrontRightCAN->Set(0.0);
	}
	TURNMODIFIERCORRECTION = fabs(((DriveFrontLeftCAN->GetPosition()-DFLA))*6) + 0.1;
	if (DFLA + TURNMARGINOFERROR <= DriveFrontLeftCAN->GetPosition() )
	{
		DriveFrontLeftCAN->Set(TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else if (DFLA - TURNMARGINOFERROR >= DriveFrontLeftCAN->GetPosition() )
	{
		DriveFrontLeftCAN->Set(-TURNVELOCITY * TURNMODIFIERCORRECTION);
	} else {
		DriveFrontLeftCAN->Set(0.0);
	}
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
	this->DoAutoAlign(0,0,0,0);
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



