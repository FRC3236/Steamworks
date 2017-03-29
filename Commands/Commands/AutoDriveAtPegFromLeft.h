#ifndef AutoDriveAtPegFromLeft_H
#define AutoDriveAtPegFromLeft_H

#include "../../CommandBase.h"
#include "PushGearAndBackUp.h"
class AutoDriveAtPegFromLeft : public CommandBase {
public:
	Timer *AutoTimer;
	PushGearAndBackUp *pushGearAndBackUp;
	bool Completed;
	bool FoundPeg;
	double *DriveRef;
	AutoDriveAtPegFromLeft();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDriveAtPeg_H
