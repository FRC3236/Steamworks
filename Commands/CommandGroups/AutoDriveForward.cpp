#include "AutoDriveForward.h"
#include "../Commands/DriveForward.h"

AutoDriveForward::AutoDriveForward() {
	AddSequential(new DriveForward(), 3);
}
