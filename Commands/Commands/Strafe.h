#ifndef Strafe_H
#define Strafe_H

#include "../../CommandBase.h"

class Strafe : public CommandBase {
public:
	double angle;
	Strafe(double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // Strafe_H
