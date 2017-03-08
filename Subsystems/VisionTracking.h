#ifndef VisionTracking_H
#define VisionTracking_H

#include <Commands/Subsystem.h>

using namespace std;

class VisionTracking : public Subsystem {
private:
	shared_ptr<NetworkTable> table;
	vector<double> area, centerX, centerY, width, height, solidity;

public:
	VisionTracking();
	void Update();
	double FindPeg();
	vector< vector<string,double> > GetContours();
	vector< vector<string,double> > GetSpecificContours(double, double, double, double);
	vector<string,double> GetLargestContour();
	vector<string,double> GetSmallestContour();
};

#endif  // VisionTracking_H
