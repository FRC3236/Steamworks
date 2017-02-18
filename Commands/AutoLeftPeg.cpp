#include "AutoLeftPeg.h"
#include "AutoDrive.h"
#include "PushGear.h"
#include "DoNothing.h"
#include "SpinToFromHere.h"
#include "ZeroWheels.h"
AutoLeftPeg::AutoLeftPeg() {

	AddSequential(new AutoDrive(0.35), 1.75);
	AddSequential(new AutoDrive(0.15), 1.2); //coast to peg location
	AddSequential(new SpinToFromHere(45, 0.5), 1);
	AddSequential(new AutoDrive(0.1), .5); //coast into peg.
	AddSequential(new DoNothing(), 0.5);
	AddSequential(new PushGear(true), 1);
	AddSequential(new AutoDrive(0.2), 0.4); //back away from peg
	AddSequential(new SpinToFromHere(-45, 0.5), 1);
	AddSequential(new AutoDrive(0.3), 1.5); //cross the baseline
	AddSequential(new DoNothing(), 1);

}
