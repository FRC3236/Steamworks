#ifndef GearBallToggle_H
#define GearBallToggle_H

#include <Commands/Subsystem.h>

class GearBallToggle : public Subsystem {
private:
	DoubleSolenoid *ToggleSolenoid;
	bool *IsExtended();
public:
	GearBallToggle();
	void Initialize();
	void Execute();
	void Toggle();
};

#endif  // GearBallToggle_H
