/*
 * AutoDefault.h
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */

#ifndef AUTODEFAULT_H
#define AUTODEFAULT_H

#include "../CommandBase.h"

class AutoDefault: public CommandBase {
public:

	Timer *AutoTimer;
	AutoDefault();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif /* SRC_COMMANDS_AUTODEFAULT_H_ */
