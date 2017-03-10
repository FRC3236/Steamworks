#include "AutoDriveFromLeftNV.h"
#include "TurnAbout.h"
#include "DoNothing.h"
#include "ZeroWheels.h"

AutoDriveFromLeftNV::AutoDriveFromLeftNV() {
	AddSequential(new TurnAbout(77, 0.5), 5);
	AddSequential(new DoNothing(), 2);
	AddSequential(new ZeroWheels(), 2);
	AddSequential(new DoNothing(), 1);
}
