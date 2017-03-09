#include "Drive.h"

#include "AutoDriveAtPeg.h"
#include "ZeroWheels.h"
#include "PushGear.h"
#include "DoNothing.h"

Drive::Drive() {
	AddSequential(new AutoDriveAtPeg());
	AddSequential(new ZeroWheels(), 0.1);
	AddSequential(new PushGear(), 1.00);
	AddSequential(new DoNothing(), 2);
}
