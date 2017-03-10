#ifndef PushGearNoSafety_H
#define PushGearNoSafety_H

#include "../CommandBase.h"

class PushGearNoSafety : public CommandBase {
public:
	Timer *AutoTimer;
	bool finished;
	PushGearNoSafety();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // PushGearNoSafety_H
