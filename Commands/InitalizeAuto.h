#ifndef InitalizeAuto_H
#define InitalizeAuto_H

#include "../CommandBase.h"

class InitalizeAuto : public CommandBase {
public:
	InitalizeAuto();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // InitalizeAuto_H
