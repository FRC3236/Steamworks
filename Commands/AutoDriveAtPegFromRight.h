#ifndef AutoDriveAtPegFromLeft_H
#define AutoDriveAtPegFromLeft_H

#include "../CommandBase.h"

class AutoDriveAtPegFromRight : public CommandBase {
public:
	AutoDriveAtPegFromRight();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDriveAtPegFromLeft_H
