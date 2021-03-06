#ifndef DriveForward_H
#define DriveForward_H

#include "../CommandBase.h"

class DriveForward : public CommandBase {
public:
	double driveStraightReference;
	DriveForward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DriveForward_H
