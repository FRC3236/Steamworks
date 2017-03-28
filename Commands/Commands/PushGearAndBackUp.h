#ifndef PushGearAndBackUp_H
#define PushGearAndBackUp_H

#include "../../CommandBase.h"

class PushGearAndBackUp : public CommandBase {
private:
public:

	Timer *AutoTimer;
	bool canExecute;
	PushGearAndBackUp();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // AutoDrive_H
