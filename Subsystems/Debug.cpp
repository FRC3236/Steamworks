#include "Debug.h"
#include <cmath>
#include "../RobotMap.h"
#include "WPILib.h"

using namespace std;

Debug::Debug() : Subsystem("Debug") {
	TrackingTimer = new Timer();
	Tracking = false;
	Frequency = 0;
	Enabled = true;
}

void Debug::SetFrequency(double NewFreq) {
	Frequency = NewFreq;
}

void Debug::Enable() {
	Enabled = true;
}

void Debug::Disable() {
	Enabled = false;
}

void Debug::Toggle() {
	Enabled = !Enabled;
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

void Debug::StopTracking() {
	Tracking = false;
	TrackingTimer->Stop();
}

void Debug::Log(string Information) {

	//if (fmod(TrackingTimer->Get(), Frequency) == 0 && Enabled) {
		cout << "[Debug] " << Information << endl;
	//}

}

void Debug::Log(string Location, string Information) {

	//if (fmod(TrackingTimer->Get(), Frequency) == 0 && Enabled) {
		cout << "[" << Location << "] " << Information << endl;
	//}

}

void Debug::LogWithTime(string Information) {

	//if (fmod(TrackingTimer->Get(), Frequency) == 0 && Enabled) {
		cout << "[Debug : " << TrackingTimer->Get() << "] " << Information << endl;
	//}

}

void Debug::LogWithTime(string Location, string Information) {

	//if (fmod(TrackingTimer->Get(), Frequency) == 0 && Enabled) {
		cout << "[" << Location << " : " << TrackingTimer->Get() << "] " << Information << endl;
	//}

}
