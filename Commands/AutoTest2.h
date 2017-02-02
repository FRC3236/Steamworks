#ifndef AutoTest2_H
#define AutoTest2_H

#include "../CommandBase.h"

class AutoTest2 : public CommandBase {
public:
	Timer *AutoTimer;
	AutoTest2();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // AutoTest2_H
