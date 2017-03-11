#include "AutoDrive.h"
#include "DriveForward.h"
#include "DoNothing.h"
#include "ZeroWheels.h"
#include "TurnAbout.h"
#include "PushGearAndBackUp.h"
AutoDrive::AutoDrive() {
	AddSequential(new DriveForward(), 4);
	AddSequential(new DoNothing(), 1);
	AddSequential(new ZeroWheels(), 0.5);
	AddSequential(new PushGearAndBackUp());
}
