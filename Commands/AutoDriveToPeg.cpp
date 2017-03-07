#include "AutoDriveToPeg.h"

AutoDriveToPeg::AutoDriveToPeg(double Speed) {
	Requires(drivetrain);
	Requires(gearsystem);
	speed = Speed;
	startangle = 0;
}

// Called just before this Command runs the first time
void AutoDriveToPeg::Initialize() {
	table = NetworkTable::GetTable("GRIP/myContoursReport");	// Initialize the subtable instance.
	this->startangle = drivetrain->Gyro->GetAngle();
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveToPeg::Execute() {
	// get all of the data from the network table
	std::vector<double> area = table->GetNumberArray("area", llvm::ArrayRef<double>());
	std::vector<double> centerY = table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	std::vector<double> centerX = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	std::vector<double> height = table->GetNumberArray("height", llvm::ArrayRef<double>());
	std::vector<double> width = table->GetNumberArray("width", llvm::ArrayRef<double>());
	std::vector<double> solidity = table->GetNumberArray("solidity", llvm::ArrayRef<double>());

	if (centerX.size()>=2) {
		double leftX = 0, rightX = 0, recordArea = 0;

		for (unsigned int i = 0; i < centerX.size(); i++) {
			for (unsigned int j = 0; j < centerX.size(); j++) {
				if (i!=j && fabs(width[i]-width[j]) < 5 && fabs(height[i]-height[j]) < 5 && (area[i]>recordArea || area[j]>recordArea)) {
					recordArea = fmax(area[i],area[j]);
					if (i<j) {
						leftX = centerX[i];
						rightX = centerX[j];
					} else {
						leftX = centerX[j];
						rightX = centerX[i];
					}
				}
			}
		}
		double pegX;
		if (recordArea == 0) {
			std::cout<<"Ahhhh!: Could not find peg"<<std::endl;
			drivetrain->Drive(0);
		} else {
			std::cout<<pegX<<std::endl;
			pegX = (leftX + rightX)/2;
			drivetrain->TurnAbout(640/(pegX-160),0.25);
		}
	} else {
		std::cout<<"Ahhhh!: Not enought tape"<<std::endl;
		drivetrain->Drive(0);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveToPeg::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutoDriveToPeg::End() {
	drivetrain->Drive(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveToPeg::Interrupted() {
	drivetrain->Drive(0);
}
