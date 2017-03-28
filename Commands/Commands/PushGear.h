#ifndef PushGear_H
#define PushGear_H

#include "../../CommandBase.h"

class PushGear : public CommandBase {

public:
	Timer *AutoTimer;
	bool finished;
	bool enabled;
	bool startedtimer;
	PushGear();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // PushGear_H
