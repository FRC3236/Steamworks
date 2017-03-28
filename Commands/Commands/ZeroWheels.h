#ifndef ZeroWheels_H
#define ZeroWheels_H

#include "../../CommandBase.h"

class ZeroWheels : public CommandBase {
public:
	ZeroWheels();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // ZeroWheels_H
