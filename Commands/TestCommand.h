/*
 * TestCommand.h
 *
 *  Created on: Jan 28, 2017
 *      Author: ROBOTICS-Net
 */

#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "../CommandBase.h"

class TestCommand: public CommandBase {
public:
	TestCommand();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};




#endif /* SRC_COMMANDS_TESTCOMMAND_H_ */
