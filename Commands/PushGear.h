#ifndef PushGear_H
#define PushGear_H

#include "../CommandBase.h"

class PushGear : public CommandBase {

public:
	bool safety;
	Timer *AutoTimer;
	bool finished;
	bool startedtimer;
	PushGear(bool);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // PushGear_H
