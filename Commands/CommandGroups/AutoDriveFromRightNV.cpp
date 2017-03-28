#include "AutoDriveFromRightNV.h"
#include "../Commands/TurnAbout.h"
#include "../Commands/DoNothing.h"
#include "../Commands/ZeroWheels.h"
#include "../Commands/PushGearAndBackUp.h"

AutoDriveFromRightNV::AutoDriveFromRightNV() {
	AddSequential(new TurnAbout(-77, 0.5), 5);
	AddSequential(new DoNothing(), 1);
	AddSequential(new ZeroWheels(), 1);
	//AddSequential(new PushGearAndBackUp());
}
