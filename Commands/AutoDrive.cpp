#include "AutoDrive.h"
#include "DriveForward.h"
#include "DoNothing.h"
#include "ZeroWheels.h"
#include "TurnAbout.h"
AutoDrive::AutoDrive() {
	AddSequential(new DriveForward(), 5);
	AddSequential(new DoNothing(), 2);
	AddSequential(new ZeroWheels(), 2);
	AddSequential(new DoNothing(), 1);
}
