#ifndef AutoDrive_H
#define AutoDrive_H

#include "../CommandBase.h"

class AutoDrive : public CommandBase {
private:
	double speed;
	double startangle;
public:
	AutoDrive(double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoDrive_H
