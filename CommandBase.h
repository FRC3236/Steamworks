#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <memory>
#include <string>

#include <Commands/Command.h>

#include "OI.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/RopeClimber.h"
#include "Subsystems/GearSystem.h"

class CommandBase: public frc::Command {
public:
	static GearSystem *gearsystem;
	static OI *controls;
	static DriveTrain *drivetrain;
	static RopeClimber *ropeclimber;
	CommandBase(char const *name);
	CommandBase();
	static void init();
};

#endif //COMMAND_BASE_H
