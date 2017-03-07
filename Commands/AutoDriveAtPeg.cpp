#include "AutoDriveAtPeg.h"

using namespace std;

AutoDriveAtPeg::AutoDriveAtPeg() {
	finished = false;
	Requires(drivetrain);
	Requires(gearsystem);
}

// Called just before this Command runs the first time
void AutoDriveAtPeg::Initialize() {
	table = NetworkTable::GetTable("GRIP/myContoursReport");
}

// Called repeatedly when this Command is scheduled to run
void AutoDriveAtPeg::Execute() {
	if (gearsystem->LimitSwitch->Get() == 1) {
		finished = true;
	} else {
		// Get data from network table
		area = table->GetNumberArray("area", llvm::ArrayRef<double>());
		centerY = table->GetNumberArray("centerY", llvm::ArrayRef<double>());
		centerX = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
		height = table->GetNumberArray("height", llvm::ArrayRef<double>());
		width = table->GetNumberArray("width", llvm::ArrayRef<double>());
		solidity = table->GetNumberArray("solidity", llvm::ArrayRef<double>());

		// If two or more contours are found,
		if (centerX.size()>=2) {
			// Declare variables for the x position of the left and right pieces of tape and the peg, and declare a variable for the width deviation.
			double leftX = 0, rightX = 0, width_deviation = 10000, pegX = 0;

			// For every contour,
			for (unsigned int i = 0; i < centerX.size(); i++) {
				// For every contour,
				for (unsigned int j = 0; j < centerX.size(); j++) {
					// If the contours are unique and have similare dimensions and have less width deviation than the current record,
					if (i!=j && fabs(width[i]-width[j]) < 10 && fabs(height[i]-height[j]) < 10 && fabs(width[i] - width[j])<width_deviation) {
						// Store the new width deviation
						width_deviation = fabs(width[i] - width[j]);
						// Determine which contour is on the left and which is on the right, and store the x positions respectively.
						if (centerX[i]<centerX[j]) {
							leftX = centerX[i];
							rightX = centerX[j];
						} else {
							leftX = centerX[j];
							rightX = centerX[i];
						}
					}
				}
			}

			// If no contour pairs are found, drive forward slowely.
			if (width_deviation == 10000) {
				std::cout<<"AHHHH! No peg found"<<std::endl;
				drivetrain->Drive(0.25);
			}
			// If a contour pair is found,
			else {
				// Calculate the x position of the peg (0 is the center of the image)
				pegX = (leftX + rightX)/2 - 320;
				std::cout<<pegX<<std::endl;
				// Swirve toward the peg
//				drivetrain->TurnAbout(768000*pegX/powf((pegX),3),0.25);
				// Crawl toward the peg
				double angle = 0.1*atan((pegX)/320);
				drivetrain->DoAutoAlign(angle, angle, angle, angle);
				drivetrain->Drive(0.2);
			}
		}
		// If less than two contours are found,
		else {
			std::cout<<"AHHHH! Not enough tape"<<centerX[0]-320<<std::endl;
			// If one contour is found,
			if (centerX.size()==1) {
				// If the width of the contour is large, drive forward slowely.
				if (width[0]>100) {
					drivetrain->Drive(0.1);
				}
				// If the width of the contour is small, turn toward the contour.
				else {
					drivetrain->DoAutoAlign(0.125, -0.125, 0.125, -0.125);
					double speed = (centerX[0]-320)/1280;
					drivetrain->DriveSpecial(speed, speed, speed, speed);
				}
			}
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoDriveAtPeg::IsFinished() {
	return finished;
}

// Called once after isFinished returns true
void AutoDriveAtPeg::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoDriveAtPeg::Interrupted() {

}
