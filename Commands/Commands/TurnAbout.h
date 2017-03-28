#ifndef TurnAbout_H
#define TurnAbout_H

#include "../../CommandBase.h"

class TurnAbout : public CommandBase {
public:
	double distance, speed;
	TurnAbout(double, double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // TurnAbout_H
