#ifndef AutoMoveForward_H
#define AutoMoveForward_H

#include "../CommandBase.h"

class AutoMoveForward : public CommandBase {
public:

	Timer *AutoTimer;
	AutoMoveForward();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoMoveForward_H
