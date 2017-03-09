#include "AutoDriveForward.h"
#include "DriveForward.h"

AutoDriveForward::AutoDriveForward() {
	AddSequential(new DriveForward(), 3);
}
