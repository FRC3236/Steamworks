#ifndef AutoDriveAtPegFromLeft_H
#define AutoDriveAtPegFromLeft_H

#include "../CommandBase.h"

class AutoDriveAtPegFromLeft : public CommandBase {
public:
	AutoDriveAtPegFromLeft();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDriveAtPegFromLeft_H
