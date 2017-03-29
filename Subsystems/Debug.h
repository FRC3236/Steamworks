#ifndef Debug_H
#define Debug_H

#include "WPILib.h"
#include <Commands/Subsystem.h>
#include <string>

using namespace std;

class Debug : public Subsystem {
private:

public:
	Timer *TrackingTimer;
	bool Tracking;
	bool Enabled;
	double Frequency;
	Debug();
	void SetFrequency(double);
	void Toggle();
	void Enable();
	void Disable();
	void StartTracking();
	void StopTracking();
	void ToggleTracking();
	void ResetTracking();
	void Log(string Information);
	void Log(string Location, string Information);
	void LogWithTime(string Location, string Information);
	void LogWithTime(string Information);
};

#endif  // Debug_H
