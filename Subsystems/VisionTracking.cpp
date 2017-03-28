/**
	FRC2017
	VisionTracking.cpp
	Purpose: Modularization of vision tracking
	tasks

	@author Eric Bernard
	@version 1.1 3/27/2016
*/

#include "VisionTracking.h"
#include "../RobotMap.h"
#include "../CommandBase.h"

using namespace std;
using namespace frc;

VisionTracking::VisionTracking() : Subsystem("VisionTracking") {
	table = NetworkTable::GetTable("GRIP/myContoursReport");
}

/**
	Updates all vectors based on the information
	in the NetworkTable "GRIP/myContoursReport"
*/
void VisionTracking::Update() {
	area = table->GetNumberArray("area", llvm::ArrayRef<double>());
	width = table->GetNumberArray("width", llvm::ArrayRef<double>());
	height = table->GetNumberArray("height", llvm::ArrayRef<double>());
	centerX = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	centerY = table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	solidity = table->GetNumberArray("solidity", llvm::ArrayRef<double>());
}


/**
	Compares all contours seen in the camera and
	assesses if the peg is in view. If not, this
	method will assess where the peg is in
	relation to the robot

	@return a pair of doubles:
		-> peg - location of the peg onscreen
		-> speed - scaled speed at which to
		drive to the peg
*/
pair<double, double> VisionTracking::FindPeg() {
	//pair<double, double> returnPair;
	double angle = 0;
	this->Update();

	vector< vector<double> > contours = this->GetContours(); //Get list of all contours found.
	if (contours.size() >= 2) {

		double	left = 0x00,
				right = 0x00,
				peg = 0,
				diff = 10000,
				speedScale = 0,
				areaS = 0; //Area for scaling.


		for (vector<int>::size_type i = 0; i != contours.size(); i++) {
			if (left != 0x00 && right != 0x00) {
				break;
			}
			vector<double> contourA = contours[i]; // Select the main comparison contour vector
			for (vector<int>::size_type j = i+1; j != contours.size(); j++) {

				vector<double> contourB = contours[j]; // Select the secondary comparison contour vector
				if (contourB != contourA) {					//Make sure we're not comparing a contour with itself (even though it shouldn't happen				//First, compare widths. Then, compare heights//
					double widthDiff = fabs(contourB[4] - contourA[4]);
					double heightDiff = fabs(contourB[5] - contourA[5]);
					if (widthDiff < 10 && widthDiff < diff && heightDiff < 10) {

						//We have found a candidate for our peg!

						diff = 10;

						if (contourA[1] > contourB[1]) {
							left = contourB[1];
							right = contourA[1];
						} else {
							left = contourA[1];
							right = contourB[1];
						}

						areaS = fmax(contourA[0], contourB[0]);
						//CommandBase::debug->LogWithTime("VisionTracking", "Speed: " + std::to_string(areaS));
						break;

					}
				}
			}
		}

		//Check if the difference between the contours is too far
		if (diff > 1000) {

			//The contours are too far apart to be the ones we're looking for
			CommandBase::debug->LogWithTime("VisionTracking", "Contours are too far apart for use!");
			return make_pair(0x00,0x00);

		} else {

			peg = (left+right)/2 - 160;
			speedScale = fabs(1-(areaS / 3000)); //3000 being the largest thing we want

			CommandBase::debug->LogWithTime("VisionTracking", "SpeedScale: " + std::to_string(speedScale));
			CommandBase::debug->LogWithTime("VisionTracking", "Area: " + std::to_string(areaS));
			//CommandBase::debug->LogWithTime("VisionTracking", "Left: " + std::to_string(left));
			//CommandBase::debug->LogWithTime("VisionTracking", "Right " + std::to_string(right));
			return make_pair(peg, speedScale);
		}
	} else if (contours.size() == 1) {
		vector<double> contour = contours[0];
		if (contour[1] > 320/2) {
			//Contour is on the right side of the screen
			return make_pair(0x00, 1);
		} else {
			return make_pair(0x00, 0);
		}
		//return make_pair(peg, 0x00);
	} else {
		CommandBase::debug->LogWithTime("VisionTracking", "Cannot find enough contours!");
		angle = 0x00;
		return make_pair(0x00,0x00);
	}
}

/**
	Grabs all contours in the contour report and
	packages them into a vector of vectors.

	@return a vector of vectors:
		vector contours:
			vector contour:
				[0] - area
				[1] - centerx
				[2] - centery
				[3] - solidity
				[4] - width
				[5] - height
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
		contour.push_back(centerX[i] - width[i]/2); //X position
		contour.push_back(centerY[i] - height[i]/2); //Y position
		contour.push_back(contour[7] + width[i]); //Far x
		contour.push_back(contour[8] + height[i]); //Far y

		returnVec.push_back(contour);
	}

	return returnVec;
}

/**
	Grabs contours in the contour report that
	meet certain criteria and packages them
	into a vector of vectors
	@param MinW - minimum width accepted
	@param MinH - minimum height accepted
	@param MaxW - maxumim width accepted
	@param MaxH - maximum height accepted
	@return a vector of vectors:
		vector contours:
			vector contour:
				[0] - area
				[1] - centerx
				[2] - centery
				[3] - solidity
				[4] - width
				[5] - height
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

/**
	Grabs the largest contour out of all contours
	that are on screen.

	@return vector contour:
		[0] - area
		[1] - centerx
		[2] - centery
		[3] - solidity
		[4] - width
		[5] - height
*/
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

/**
	Grabs the smallest contour out of all contours
	that are on screen.

	@return vector contour:
		[0] - area
		[1] - centerx
		[2] - centery
		[3] - solidity
		[4] - width
		[5] - height
*/
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
