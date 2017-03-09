#ifndef TELEOPDEFAULT_H
#define TELEOPDEFAULT_H

#include "PushGear.h"
#include "PushGearNoSafety.h"
#include "DropGear.h"
#include "../CommandBase.h"

class TeleopDefault: public CommandBase {
private:
	DropGear *dropgear;
	PushGear *pushgear;
	PushGearNoSafety *pushgearoverride;
	Timer *TeleopTimer;
	double LockAngle;
public:
	TeleopDefault();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};




#endif /* SRC_COMMANDS_TELEOPDEFAULT_H_ */
