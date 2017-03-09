#include "Debug.h"
#include <cmath>
#include "../RobotMap.h"
#include "WPILib.h"

using namespace std;

Debug::Debug() : Subsystem("Debug") {
	TrackingTimer = new Timer();
	Tracking = false;
	Frequency = 0;
}

void Debug::StartTracking() {
	TrackingTimer->Start();
	Tracking = true;
}

void Debug::ToggleTracking() {
	Tracking = !Tracking;
	if (Tracking) {
		TrackingTimer->Stop();
	} else {
		TrackingTimer->Start();
	}
}

void Debug::ResetTracking() {
	Tracking = false;
	TrackingTimer->Reset();
}

void Debug::Log(string Information) {

	cout << "[Debug] " << Information << endl;

}

void Debug::Log(string Location, string Information) {
	cout << "[" << Location << "] " << Information << endl;
}

void Debug::LogWithTime(string Information) {
	cout << "[Debug : " << TrackingTimer->Get() << "] " << Information << endl;
}

void Debug::LogWithTime(string Location, string Information) {
	cout << "[" << Location << " : " << TrackingTimer->Get() << "] " << Information << endl;
}
