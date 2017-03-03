#include "AutoCenterPeg.h"
#include "AutoDrive.h"
#include "PushGear.h"
#include "DoNothing.h"
#include "SpinToFromHere.h"
#include "ZeroWheels.h"
#include "TurnAbout.h"
#include "WPILib.h"
AutoDefault::AutoDefault() {
	//Current Time: 14.25
	double pause = 0;
	frc::SmartDashboard::GetNumber("Autonomous Pause", pause);
	if (pause > 0.75) {
		pause = 0.75;
	}
	AddSequential(new DoNothing(), pause);
	AddSequential(new ZeroWheels(), 0.30);
	AddSequential(new AutoDrive(0.41), 2.55);
	AddSequential(new AutoDrive(0.1), 1.60); //coast into peg
	AddSequential(new PushGear(true), 1.00);
	AddSequential(new DoNothing(), 0.2);
	AddSequential(new ZeroWheels(), 0.50);
	AddSequential(new DoNothing(), 0.10);
	AddSequential(new AutoDrive(-0.5), .9);
	AddSequential(new ZeroWheels(), 0.20);
	AddSequential(new SpinToFromHere(60, 0.5), 2.2);
	AddSequential(new TurnAbout(50, 0.6), 2.10);
	AddSequential(new AutoDrive(0.4), 1.50);
	AddSequential(new DoNothing(), 0.50);
	AddSequential(new ZeroWheels(), 0.60);

}
