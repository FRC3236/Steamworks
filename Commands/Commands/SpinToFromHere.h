#ifndef SpinToFromHere_H
#define SpinToFromHere_H

#include "../../CommandBase.h"

class SpinToFromHere : public CommandBase {
public:
	double target;
	double startangle;
	double speed;
	SpinToFromHere(double, double);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // SpinToFromHere_H
