#include "CommandBase.h"

#include <Commands/Scheduler.h>

#include "Subsystems/ExampleSubsystem.h"
#include "Subsystems/DriveTrain.h"

OI* CommandBase::controls = NULL;
DriveTrain* CommandBase::drivetrain = NULL;

CommandBase::CommandBase(char const *name): frc::Command(name) {}

CommandBase::CommandBase(): frc::Command() {}

void CommandBase::init() {
	drivetrain = new DriveTrain();
	controls = new OI();
}
