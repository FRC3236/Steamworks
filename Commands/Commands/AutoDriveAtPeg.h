#ifndef AutoDriveAtPeg_H
#define AutoDriveAtPeg_H

#include "../../CommandBase.h"
#include "PushGearAndBackUp.h"
class AutoDriveAtPeg : public CommandBase {
public:
	Timer *AutoTimer;
	PushGearAndBackUp *pushGearAndBackUp;
	bool Completed;
	bool FoundPeg;
	double *DriveRef;
	AutoDriveAtPeg();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDriveAtPeg_H
