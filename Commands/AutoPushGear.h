#ifndef AutoPushGear_H
#define AutoPushGear_H

#include "../CommandBase.h"

class AutoPushGear : public CommandBase {
public:
	AutoPushGear();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoPushGear_H
