#ifndef AutoDriveAtPeg_H
#define AutoDriveAtPeg_H

#include "../CommandBase.h"

class AutoDriveAtPeg : public CommandBase {
private:
	std::shared_ptr<NetworkTable> table;
	std::vector<double> area, centerY, centerX, height, width, solidity;
public:
	bool finished;
	AutoDriveAtPeg();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDriveAtPeg_H
