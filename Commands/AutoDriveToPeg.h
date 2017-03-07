#ifndef AutoDriveToPeg_H
#define AutoDriveToPeg_H

#include "../CommandBase.h"

class AutoDriveToPeg : public CommandBase {
private:
	double speed;
	double startangle;
	std::shared_ptr<NetworkTable> table;
public:
	AutoDriveToPeg(double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDriveToPeg_H
