#ifndef AutoTest3_H
#define AutoTest3_H

#include "../CommandBase.h"

class AutoTest3 : public CommandBase {
public:
	Timer *AutoTimer;
	AutoTest3();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoTest3_H
