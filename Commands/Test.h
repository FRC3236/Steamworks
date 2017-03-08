#ifndef Test_H
#define Test_H

#include "Commands/TimedCommand.h"

class Test : public TimedCommand {
public:
	Test(double timeout);
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif  // Test_H
