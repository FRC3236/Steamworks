#ifndef DropFuel_H
#define DropFuel_H

#include "../CommandBase.h"

class DropFuel : public CommandBase {
public:
	Timer *AutoTimer;
	DropFuel();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // DropFuel_H
