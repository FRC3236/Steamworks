#include "VisionTracking.h"
#include "../RobotMap.h"

using namespace std;

VisionTracking::VisionTracking() : Subsystem("VisionTracking") {

	table = NetworkTable::GetTable("GRIP/myContourReports");

}

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

	if (centerX.size() >= 2) {

		double	left = 0,
				right = 0,
				peg = 0,
				diff = 10000;

		vector< vector<string,double> > contours = this->GetContours(); //Get list of all contours found.
		for (vector<int>::size_type i = 0; i != contours.size(); i++) {

			vector<string,double> contourA = contours[i]; // Select the main comparison contour vector
			for (vector<int>::size_type j = i+1; j != contours.size(); i++) {

				vector<string,double> contourB = contours[j]; // Select the secondary comparison contour vector

				//First, compare widths//
				double widthDiff = fabs(contourB["width"] - contourA["width"]);
				double heightDiff = fabs(contourB["height"] - contourA["height"]);
				if (widthDiff < 10 && widthDiff < diff && heightDiff < 10) {
					//We have found a candidate for our peg!
					diff = widthDiff;
					if (contourA["centerX"] > contourB["centerX"]) {
						left = contourA["centerX"];
						right = contourB["centerX"];
					} else {
						left = contourB["centerX"];
						right = contourA["centerX"];
					}
				}
			}
		}

		//Check if the difference between the contours is too far
		if (diff > 1000) {

			//The contours are too far apart to be the ones we're looking for
			return nullptr;

		} else {

			peg = (left + right)/4 + 320;
			angle = 0.1 * atan( (peg)/320 );

		}

	}
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
 *			10,	//AREA
 *			5,	//WIDTH
 *			2,	//HEIGHT
 *			0.5,//SOLIDITY
 *			1,	//CENTERX
 *			1,	//CENTERY
 *		},
 *	}
 */
vector< vector<string,double> > VisionTracking::GetContours() {
	vector< vector<string,double> > returnVec; //Woo, 2d vectors!

	this->Update(); //Update all the tables before checking all of them.

	for (vector<int>::size_type i = 0; i != centerX.size(); i++) {
		vector<string,double> contour;
		contour["area"] = area[i];
		contour["centerX"] = centerX[i];
		contour["centerY"] = centerY[i];
		contour["solidity"] = solidity[i];
		contour["width"] = width[i];
		contour["height"] = height[i];

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
 *		[0] = {
 *			10, //AREA
 *			5, //WIDTH
 *			2, //HEIGHT
 *			0.5, //SOLIDITY
 *			1, //CENTERX
 *			1, //CENTERY
 *		},
 *	}
 */
vector< vector<string,double> > VisionTracking::GetSpecificContours(double MinW, double MinH, double MaxW, double MaxH) {
	vector< vector<string,double> > returnVec;

	this->Update(); //Update all the tables before checking all of them.

	for (vector<int>::size_type i = 0; i != centerX.size(); i++) {
		double w = width[i];
		double h = height[i];
		if (w >= MinW && w <= MaxW && h >= MinH && h <= MaxH) {
			vector<string,double> contour;
			contour["area"] = area[i];
			contour["centerX"] = centerX[i];
			contour["centerY"] = centerY[i];
			contour["solidity"] = solidity[i];
			contour["width"] = width[i];
			contour["height"] = height[i];

			returnVec.push_back(contour);
		}
	}

	return returnVec;
}


vector<string,double> VisionTracking::GetLargestContour() {

	double largest = 0;
	double largestI = 0;
	this->Update();
	vector< vector<string,double> > contours = this->GetContours();

	for (vector<int>::size_type i = 0; i != contours.size(); i++) {
		vector<string,double> contour = contours[i];
		if (contour["area"] > largest) {
			largest = contour[0];
			largestI = i;
		}
	}

	return contours[largestI];

}

vector<string,double> VisionTracking::GetSmallestContour() {

	double smallest = 100000;
	double smallestI = 0;
	this->Update();
	vector< vector<string,double> > contours = this->GetContours();

	for (vector<int>::size_type i = 0; i != contours.size(); i++) {
		vector<string,double> contour = contours[i];
		if (contour["area"] < smallest) {
			smallest = contour[0];
			smallestI = i;
		}
	}

	return contours[smallestI];

}
