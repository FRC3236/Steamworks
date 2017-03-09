#ifndef Debug_H
#define Debug_H

#include "WPILib.h"
#include <Commands/Subsystem.h>

using namespace std;

class Debug : public Subsystem {
private:

public:
	Timer *TrackingTimer;
	bool Tracking;
	double *Frequency;
	Debug();
	void StartTracking();
	void ToggleTracking();
	void ResetTracking();
	void Log(string Information);
	void Log(string Location, string Information);
	void LogWithTime(string Location, string Information);
	void LogWithTime(string Information);
};

#endif  // Debug_H
