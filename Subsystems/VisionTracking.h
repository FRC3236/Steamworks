#ifndef VisionTracking_H
#define VisionTracking_H

#include <Commands/Subsystem.h>
#include "WPILib.h"

using namespace std;

class VisionTracking : public Subsystem {
private:
	shared_ptr<NetworkTable> table;
	vector<double> area, centerX, centerY, width, height, solidity;

public:
	VisionTracking();
	void Update();
	pair<double, double> FindPeg();
	vector< vector<double> > GetContours();
	vector< vector<double> > GetSpecificContours(double, double, double, double);
	vector<double> GetLargestContour();
	vector<double> GetSmallestContour();
};

#endif  // VisionTracking_H
