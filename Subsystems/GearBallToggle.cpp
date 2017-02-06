#include "GearBallToggle.h"
#include "../RobotMap.h"

GearBallToggle::GearBallToggle() : Subsystem("ExampleSubsystem") {
	ToggleSolenoid = new DoubleSolenoid(9,10);
	bool IsExtended = false;
}

void GearBallToggle::Initialize(){

	ToggleSolenoid->Set(DoubleSolenoid::Value::kOff);

}

void GearBallToggle::Execute() {
	//Doesn't do anything for now
}

void GearBallToggle::Toggle() {
	std::cout << ToggleSolenoid->Get() << std::endl;
	if (IsExtended) {
		//Retract the solenoid
		ToggleSolenoid->Set(DoubleSolenoid::Value::kReverse);
	} else {
		//Extend the solenoid
		ToggleSolenoid->Set(DoubleSolenoid::Value::kForward);
	}
}
