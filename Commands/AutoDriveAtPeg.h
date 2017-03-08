#ifndef AutoDriveAtPeg_H
#define AutoDriveAtPeg_H

#include "../CommandBase.h"

class AutoDriveAtPeg : public CommandBase {
private:
public:
	AutoDriveAtPeg();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDriveAtPeg_H
