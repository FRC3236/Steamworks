#ifndef AutoDriveAtPegFromLeft_H
#define AutoDriveAtPegFromLeft_H

#include "../CommandBase.h"

class AutoDriveAtPegFromLeft : public CommandBase {
public:
	bool Complete;
	bool FoundPeg;
	double DriveStraightReference;
	AutoDriveAtPegFromLeft();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDriveAtPegFromLeft_H
