/*
 * TeleopDefault.h
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */

#ifndef TELEOPDEFAULT_H
#define TELEOPDEFAULT_H
#include "PushGear.h"
#include "DropGear.h"
#include "../CommandBase.h"

class TeleopDefault: public CommandBase {
public:
	Timer *TeleopTimer;
	TeleopDefault();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};




#endif /* SRC_COMMANDS_TELEOPDEFAULT_H_ */
