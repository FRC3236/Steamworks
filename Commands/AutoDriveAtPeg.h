#ifndef AutoDriveAtPeg_H
#define AutoDriveAtPeg_H

#include "../CommandBase.h"
#include "Timer.h"
#include "PushGearAndBackUp.h"

class AutoDriveAtPeg : public CommandBase {
private:
public:
	Timer *AutoTimer;
	PushGearAndBackUp *pushGearAndBackUp;
	AutoDriveAtPeg();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDriveAtPeg_H
