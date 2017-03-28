/**
	FRC2017
	Debug.cpp
	Purpose: Custom debugging for more precise
	logging tasks

	@author Eric Bernard
	@version 1.0 3/27/2016
*/

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

/**
	Set the frequency at which to print out
	messages

	@param NewFreq - the frequency at which to
	set
*/
void Debug::SetFrequency(double NewFreq) {
	Frequency = NewFreq;
	return;
}

/**
	Enable the entire debugging system
*/
void Debug::Enable() {
	Enabled = true;
	return;
}

/**
	Disable the entire debugging system
*/
void Debug::Disable() {
	Enabled = false;
	return;
}

/**
	Toggle the entire debugging system
*/
void Debug::Toggle() {
	Enabled = !Enabled;
}

/**
	Start the tracking timer for timed outputs
*/
void Debug::StartTracking() {
	TrackingTimer->Start();
	Tracking = true;
	return;
}

/**
	Toggle whether the tracking timer is being
	updated
*/
void Debug::ToggleTracking() {
	Tracking = !Tracking;
	if (Tracking) {
		TrackingTimer->Stop();
	} else {
		TrackingTimer->Start();
	}
	return;
}

/**
	Reset tracking timer to 0 and stop the timer
*/
void Debug::ResetTracking() {
	Tracking = false;
	TrackingTimer->Reset();
	return;
}

/**
	Stop tracking for timed outputs
*/
void Debug::StopTracking() {
	Tracking = false;
	TrackingTimer->Stop();
	return;
}

/**
	Output a simple message

	@param Information - string to print
	@note In many cases, a simple std::cout would
	be easier
*/
void Debug::Log(string Information) {
	cout << "[Debug] " << Information << endl;
	return;
}

/**
	Output a simple message with a location tag

	@param Location - where the log message
	originates
	@param Information - string to print
*/
void Debug::Log(string Location, string Information) {
	cout << "[" << Location << "] " << Information << endl;
	return;
}

/**
	Output a simple message with a time tag

	@param Information - string to print
*/
void Debug::LogWithTime(string Information) {
	cout << "[Debug : " << TrackingTimer->Get() << "] " << Information << endl;
	return;
}

/**
	Output a simple message with location and
	time tag

	@param Location - where the log message
	originates
	@param Information - string to print
*/
void Debug::LogWithTime(string Location, string Information) {
	cout << "[" << Location << " : " << TrackingTimer->Get() << "] " << Information << endl;
	return;
}
