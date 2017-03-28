#include "AutoDrive.h"
#include "../Commands/DriveForward.h"
#include "../Commands/DoNothing.h"
#include "../Commands/ZeroWheels.h"
#include "../Commands/TurnAbout.h"
#include "../Commands/PushGearAndBackUp.h"
AutoDrive::AutoDrive() {
	AddSequential(new DriveForward(), 4);
	AddSequential(new DoNothing(), 1);
	AddSequential(new ZeroWheels(), 0.5);
	AddSequential(new PushGearAndBackUp());
}
