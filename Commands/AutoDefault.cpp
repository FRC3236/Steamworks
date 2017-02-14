#include "AutoDefault.h"
#include "AutoDrive.h"
#include "PushGear.h"
#include "DoNothing.h"
#include "ZeroWheels.h"
AutoDefault::AutoDefault() {
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
	AddSequential(new AutoDrive(0.3), 2.5);
	AddSequential(new DoNothing(), 0.75);
	AddSequential(new PushGear());
	AddSequential(new DoNothing(), 0.75);
	AddSequential(new ZeroWheels(), 1);
	AddSequential(new AutoDrive(-0.3), 1);
	AddSequential(new ZeroWheels(), 0.5);
}
