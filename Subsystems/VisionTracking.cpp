#include "VisionTracking.h"
#include "../RobotMap.h"
#include "../CommandBase.h"

using namespace std;
using namespace frc;

VisionTracking::VisionTracking() : Subsystem("VisionTracking") {

	table = NetworkTable::GetTable("GRIP/myContoursReport");

}

/*
 * 	Update()
 * 	Updates all the vectors based on the info in the NetworkTable.
 * 	This function is called internally by every function that
 * 	processes contours, so unless something is terribly wrong,
 * 	this function shouldn't have to be called externally.
 */
void VisionTracking::Update() {
	area = table->GetNumberArray("area", llvm::ArrayRef<double>());
	width = table->GetNumberArray("width", llvm::ArrayRef<double>());
	height = table->GetNumberArray("height", llvm::ArrayRef<double>());
	centerX = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	centerY = table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	solidity = table->GetNumberArray("solidity", llvm::ArrayRef<double>());
}


/*
 * 	FindPeg()
 * 	This function returns the angle at which the peg is at compared to the current
 * 	rotation of the robot. The robot can use its gyro to move in accordance to the
 * 	value returned from here.
 *
 */
double VisionTracking::FindPeg() {

	double angle = 0;
	this->Update();

	vector< vector<double> > contours = this->GetContours(); //Get list of all contours found.
	if (contours.size() >= 2) {

		double	left = 0,
				right = 0,
				peg = 0,
				diff = 10000;


		for (vector<int>::size_type i = 0; i != contours.size(); i++) {

			vector<double> contourA = contours[i]; // Select the main comparison contour vector
			for (vector<int>::size_type j = i+1; j != contours.size(); j++) {

				vector<double> contourB = contours[j]; // Select the secondary comparison contour vector
				if (contourB != contourA) { //Make sure we're not comparing a contour with itself (even though it shouldn't happen				//First, compare widths. Then, compare heights//
					double widthDiff = fabs(contourB[4] - contourA[4]);
					double heightDiff = fabs(contourB[5] - contourA[5]);
					if (widthDiff < 10 && widthDiff < diff && heightDiff < 10) {
						//We have found a candidate for our peg!
						diff = widthDiff;
						if (contourA[1] > contourB[1]) {
							CommandBase::debug->LogWithTime("VisionTracking", "ContourA is on the left");
							left = contourA[1];
							right = contourB[1];
						} else {
							CommandBase::debug->LogWithTime("VisionTracking", "ContourA is on the right.");
							left = contourB[1];
							right = contourA[1];
						}
					}
				}
			}
		}

		//Check if the difference between the contours is too far
		if (diff > 1000) {

			//The contours are too far apart to be the ones we're looking for
			CommandBase::debug->LogWithTime("VisionTracking", "Contours are too far apart for use!");
			return 0x00;

		} else {

			peg = (left + right)/4 + 320;
			angle = 0.1 * atan( (peg)/320 );

		}

	} else {
		CommandBase::debug->LogWithTime("VisionTracking", "Cannot find enough contours!");
		angle = 0x00;
	}
	CommandBase::debug->LogWithTime("VisionTracking", to_string(angle));
	//CommandBase::debug->LogWithTime("VisionTracking", "Angle: " + to_string(angle));
	return angle;

}


/*
 *	GetContours()
 *	Used for getting all contours published by GRIP/myContoursReport
 *	If you're looking to get contours with specific properties, see
 *	GetSpecificContours().
 *
 *	This function returns a 2D vector, meaning there are vectors within the main vector.
 *	Here's the basic structure (in pseudocode):
 *	contours = {
 *		[0] = { //Contour 0
 *			10,		//AREA [0]
 *			100,	//CENTERX [1]
 *			100,	//CENTERY [2]
 *			1,		//SOLIDITY [3]
 *			5,		//WIDTH [4]
 *			2,		//HEIGHT [5]
 *		}
 *	}
 */
vector< vector<double> > VisionTracking::GetContours() {
	vector< vector<double> > returnVec; //Woo, 2d vectors!

	this->Update(); //Update all the tables before checking all of them.

	for (vector<int>::size_type i = 0; i != centerX.size(); i++) {
		vector<double> contour;
		contour.push_back(area[i]);
		contour.push_back(centerX[i]);
		contour.push_back(centerY[i]);
		contour.push_back(solidity[i]);
		contour.push_back(width[i]);
		contour.push_back(height[i]);

		returnVec.push_back(contour);
	}

	return returnVec;
}

/*
 * 	GetSpecificContours(double, double, double, double)
 * 	Used for filtering out undesired contours publised in GRIP/myContoursReport
 *
 * 	This function returns a 2D vector, meaning there are vectors within the main vector.
 *	Here's the basic structure (in pseudocode):
 *	contours = {
 *		[0] = { //Contour 0
 *			10,		//AREA
 *			100,	//CENTERX
 *			100,	//CENTERY
 *			1,		//SOLIDITY
 *			5,		//WIDTH
 *			2,		//HEIGHT
 *		}
 *	}
 */
vector< vector<double> > VisionTracking::GetSpecificContours(double MinW, double MinH, double MaxW, double MaxH) {
	vector< vector<double> > returnVec;

	this->Update(); //Update all the tables before checking all of them.

	for (vector<int>::size_type i = 0; i != centerX.size(); i++) {
		double w = width[i];
		double h = height[i];
		if (w >= MinW && w <= MaxW && h >= MinH && h <= MaxH) {
			vector<double> contour;
			contour.push_back(area[i]);
			contour.push_back(centerX[i]);
			contour.push_back(centerY[i]);
			contour.push_back(solidity[i]);
			contour.push_back(width[i]);
			contour.push_back(height[i]);

			returnVec.push_back(contour);
		}
	}

	return returnVec;
}


vector<double> VisionTracking::GetLargestContour() {

	double largest = 0;
	double largestI = 0;
	vector< vector<double> > contours = this->GetContours();

	for (vector<int>::size_type i = 0; i != contours.size(); i++) {
		vector<double> contour = contours[i];
		if (contour[0] > largest) {
			largest = contour[0];
			largestI = i;
		}
	}

	return contours[largestI];

}

vector<double> VisionTracking::GetSmallestContour() {

	double smallest = 100000;
	double smallestI = 0;
	vector< vector<double> > contours = this->GetContours();

	for (vector<int>::size_type i = 0; i != contours.size(); i++) {
		vector<double> contour = contours[i];
		if (contour[0] < smallest) {
			smallest = contour[0];
			smallestI = i;
		}
	}

	return contours[smallestI];

}
