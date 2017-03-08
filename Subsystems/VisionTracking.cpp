#include "VisionTracking.h"
#include "../RobotMap.h"

using namespace std;

VisionTracking::VisionTracking() : Subsystem("VisionTracking") {

	table = NetworkTable::GetTable("GRIP/myContourReports");

}

vector<double> VisionTracking::FindPeg() {

	area = table->GetNumberArray("area", llvm::ArrayRef<double>());
	width = table->GetNumberArray("width", llvm::ArrayRef<double>());
	height = table->GetNumberArray("height", llvm::ArrayRef<double>());
	centerX = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
	centerY = table->GetNumberArray("centerY", llvm::ArrayRef<double>());
	solidity = table->GetNumberArray("solidity", llvm::ArrayRef<double>());

	vector<double> returnVector;

	if (centerX.size() >= 2) {

		double	left = 0,
				right = 0,
				peg = 0,
				diff = 10000;

		for (int i = 0; i < centerX.size(); i++) {
			for (int j = 0; j < centerX.size(); j++) {

				if (i!=j && fabs(width[i]-width[j]) < 10 && fabs(height[i]-height[j]) < 10 && fabs(width[i] - width[j])<diff) {

					diff = fabs(width[i]-width[j]);

					if (centerX[i]<centerX[j]) {
						left = centerX[i];
						right = centerX[j];
					} else {
						left = centerX[j];
						right = centerX[i];
					}

				}

			}
		}

		//Check if the difference between the pegs is too far
		if (diff > 1000) {

			//No peg has been found.
			return returnVector;

		} else {

			peg = (left + right)/4 + 320;
			double angle = 0.1*atan((peg)/320);
			returnVector.push_back(peg);
			returnVector.push_back(angle);

		}

	}
	//If centerX.size() < 2 then returnVector.size() will be 0.
	//Use that for checking the amt. of contours.
	return returnVector;

}
