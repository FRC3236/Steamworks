#include "AutoDriveFromLeftNV.h"
#include "TurnAbout.h"
#include "DoNothing.h"
#include "ZeroWheels.h"
#include "PushGearAndBackUp.h"

AutoDriveFromLeftNV::AutoDriveFromLeftNV() {
	AddSequential(new TurnAbout(77, 0.5), 5);
	AddSequential(new DoNothing(), 1);
	AddSequential(new ZeroWheels(), 1);
	//AddSequential(new PushGearAndBackUp());
}
