/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */
#include "DriveTrain.h"
#include "WPILib.h"
#include "../RobotMap.h"

/*
 *
 */
double DFRA, DBLA, DBRA, DFLA = 0;
DriveTrain::DriveTrain() : Subsystem("DriveTrain") {
	frc::Subsystem("DriveTrain");
	std::cout << "[drivetrain] DriveTrain initializing..." << std::endl;

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

	std::cout << "[drivetrain] DriveTrain initialized." << std::endl;
}

/*
 *
 */
void DriveTrain::Initialize() {
	Gyro->Calibrate();
	Accelerometer->SetSensitivity(0.018);
	Accelerometer->SetZero(0);
	this->ResetAlignment();
	this->Drive(0);
	return;
}


/*
 *
 */
void DriveTrain::Drive(double speed) {
	this->DriveSpecial(speed,speed,-speed,-speed);

	return;
}

/*
 *
 */
void DriveTrain::Drive2(double speed) {
	if (fabs(this->GetDeltaAngle2(DriveBackLeftCAN->GetPosition(), DBLA)) < 0.25) {
		DriveBackLeft->Set(-speed);
	} else {
		DriveBackLeft->Set(speed);
	}
	if (fabs(this->GetDeltaAngle2(DriveBackRightCAN->GetPosition(), DBRA)) < 0.25) {
		DriveBackRight->Set(speed);
	} else {
		DriveBackRight->Set(-speed);
	}
	if (fabs(this->GetDeltaAngle2(DriveFrontLeftCAN->GetPosition(), DFLA)) < 0.25) {
		DriveFrontLeft->Set(-speed);
	} else {
		DriveFrontLeft->Set(speed);
	}
	if (fabs(this->GetDeltaAngle2(DriveFrontRightCAN->GetPosition(), DFRA)) < 0.25) {
		DriveFrontRight->Set(speed);
	} else {
		DriveFrontRight->Set(-speed);
	}
}

/*
 *
 */
void DriveTrain::Crawl(double Angle) {
	double Speed = 0.4;
	this->DoAutoAlign(Angle, Angle, Angle, Angle);
	this->Drive(Speed);
}

void DriveTrain::Crawl(double Angle, double Speed) {
	this->DoAutoAlign(Angle, Angle, Angle, Angle);
	this->Drive(Speed);
}

/*
 *
 */
void DriveTrain::TraverseSimple(double Speed) {
	this->DoAutoAlign(0.25, 0.25, 0.25, 0.25);
	this->Drive(Speed);
	return;
}

/*
 *
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
}

/*
 *
 */
void DriveTrain::Traverse2(double X, double Y) {
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
	this->DoAutoAlign2(TurnAngle, TurnAngle, TurnAngle, TurnAngle);
	if (fabs(Speed) > JOYSTICKDEADZONE) {
		this->Drive2(Speed);
	} else {
		this->Drive(0);
	}
}

/*
 * Drive about a circle with a specified radious
 *
 * @return void
 * @note Positive radii specify a circle to the right of the robot; negative to the left
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

	//std::cout << "[drivetrain] Right degree:" << RightDegree << std::endl << "Left Degree: " << LeftDegree << std::endl;
	this->DoAutoAlign(LeftDegree, -LeftDegree, -RightDegree, RightDegree);
	this->DriveSpecial(LeftSpeed, LeftSpeed, -RightSpeed, -RightSpeed);
	return;
}

/*
 * Converts an angle from degrees to radians
 *
 * @return calculated result
 */
double DriveTrain::DegreeToRadian(double Degree) {
	return 360/Degree;
	//return M_PI*Degree/180;
}

/*
 *
 * @return void
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

/*
 *
 *
 * @return void
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

/*
 *
 *
 * @return void
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



void DriveTrain::DoAutoAlign2(double _DFLA, double _DBLA, double _DBRA, double _DFRA) {
	DFLA = _DFLA;
	DFRA = _DFRA;
	DBRA = _DBRA;
	DBLA = _DBLA;

	double CorrectionMultiplier = 5; //frc::SmartDashboard::GetNumber("Wheel Alignment Correction", CorrectionMultiplier);
	//double CorrectionAdditive = 0; //frc::SmartDashboard::GetNumber("Wheel Alignment Additive", CorrectionAdditive);

	//std::cout << "CORRECTION NUMBERS:: " << CorrectionMultiplier << " " << CorrectionAdditive << std::endl;

	double TURNMODIFIERCORRECTION = this->GetDeltaAngle2(DriveBackLeftCAN->GetPosition(), DBLA);
	std::cout << "MODIFIER: " << TURNMODIFIERCORRECTION << std::endl;
	if (fabs(TURNMODIFIERCORRECTION) > TURNMARGINOFERROR) {
		DriveBackLeftCAN->Set(-TURNMODIFIERCORRECTION * CorrectionMultiplier);
	} else {
		DriveBackLeftCAN->Set(0.0);
	}

	TURNMODIFIERCORRECTION = this->GetDeltaAngle2(DriveBackRightCAN->GetPosition(), DBRA);
	if (fabs(TURNMODIFIERCORRECTION) > TURNMARGINOFERROR) {
		DriveBackRightCAN->Set(-TURNMODIFIERCORRECTION * CorrectionMultiplier);
	} else {
		DriveBackRightCAN->Set(0.0);
	}

	TURNMODIFIERCORRECTION = this->GetDeltaAngle2(DriveFrontRightCAN->GetPosition(), DFRA);
	if (fabs(TURNMODIFIERCORRECTION) > TURNMARGINOFERROR) {
		DriveFrontRightCAN->Set(-TURNMODIFIERCORRECTION * CorrectionMultiplier);
	} else {
		DriveFrontRightCAN->Set(0.0);
	}

	TURNMODIFIERCORRECTION = this->GetDeltaAngle2(DriveFrontLeftCAN->GetPosition(), DFLA);
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

/*
 *
 *
 * @return void
 */
void DriveTrain::DriveSpecial(double DFLS, double DBLS, double DBRS, double DFRS) {
	DriveBackLeft->Set(DBLS);
	DriveBackRight->Set(DBRS);
	DriveFrontLeft->Set(DFLS);
	DriveFrontRight->Set(DFRS);

	return;
}

/*
 * Spins the robot to face a specified direction
 *
 * @param Angle - direction the robot wants to face
 * @param Speed - power going to each motor
 * @return void
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

/*
 * Stops all drivetrain motors
 * @return void
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

/*
 * Aligns the wheels to their zero positions
 * @return void
 */
void DriveTrain::ResetAlignment() {
	this->DoAutoAlign(0,0,0,0);
	return;
}

/*
 * Sets the zero position of each wheel
 * @return void
 */
void DriveTrain::SetZeros() {
	DriveFrontLeftCAN->SetPosition(0);
	DriveFrontRightCAN->SetPosition(0);
	DriveBackLeftCAN->SetPosition(0);
	DriveBackRightCAN->SetPosition(0);
	return;
}

/*
 * Stops all swerve motors
 * @return void
 */
void DriveTrain::KillSpin() {
	DriveFrontLeftCAN->Set(0.0);
	DriveFrontRightCAN->Set(0.0);
	DriveBackLeftCAN->Set(0.0);
	DriveBackRightCAN->Set(0.0);
	return;
}

/*
 *
 */
double DriveTrain::GetDeltaAngle(double Current, double Target) {
	Current = fmod(Current,1);
	Target = fmod(Target, 1);
	double Delta1 = Target - Current;
	double Delta2 = Delta1 + 1;
	double Delta3 = Delta1 - 1;
	return fabs(Delta1)<fmin(fabs(Delta2),fabs(Delta3))?Delta1:fabs(Delta2)<fabs(Delta3)?Delta2:Delta3;
}

/*
 *
 */
double DriveTrain::GetDeltaAngle2(double Current, double Target) {
	double InverseTarget = fmod((Target+0.5),1);
	return fabs(GetDeltaAngle(Current,Target))<fabs(GetDeltaAngle(Current,InverseTarget))?GetDeltaAngle(Current,Target):GetDeltaAngle(Current,InverseTarget);
}
