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
	vector<double> FindPeg();
};

#endif  // VisionTracking_H
