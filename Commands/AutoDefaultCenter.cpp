#include "AutoDefaultCenter.h"
#include "AutoDrive.h"
#include "SpinToFromHere.h"
#include "Strafe.h"
AutoDefaultCenter::AutoDefaultCenter() {
	//Just cross the baseline.
	AddSequential(new Strafe(5));
}
