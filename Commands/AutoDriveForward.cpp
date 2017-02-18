#include "AutoDriveForward.h"
#include "AutoDrive.h"
#include "DoNothing.h"

AutoDriveForward::AutoDriveForward() {

	//Time: 5 seconds

	AddSequential(new AutoDrive(0.5), 3);
	AddSequential(new DoNothing(), 2);
}
