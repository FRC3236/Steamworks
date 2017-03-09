#ifndef AutoDriveAtPegFromRight_H
#define AutoDriveAtPegFromRight_H

#include "../CommandBase.h"

class AutoDriveAtPegFromRight : public CommandBase {
public:
	bool Complete;
	bool FoundPeg;
	double DriveStraightReference;
	AutoDriveAtPegFromRight();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDriveAtPegFromLeft_H
