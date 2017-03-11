#ifndef PushGearAndBackUpNoSafety_H
#define PushGearAndBackUpNoSafety_H

#include "../CommandBase.h"

class PushGearAndBackUpNoSafety : public CommandBase {
private:
public:

	Timer *AutoTimer;
	PushGearAndBackUpNoSafety();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // AutoDrive_H
