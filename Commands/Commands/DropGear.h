#ifndef DropGear_H
#define DropGear_H

#include "WPILib.h"
#include "../../CommandBase.h"

class DropGear : public CommandBase {
public:
	Timer *AutoTimer;
	DropGear();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DropGear_H
