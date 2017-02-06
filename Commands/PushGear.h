#ifndef PushGear_H
#define PushGear_H

#include "../CommandBase.h"

class PushGear : public CommandBase {
public:
	Timer *AutoTimer;
	PushGear();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // PushGear_H
