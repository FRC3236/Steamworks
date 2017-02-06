#include "CommandBase.h"

#include <Commands/Scheduler.h>

#include "Subsystems/DriveTrain.h"
#include "Subsystems/RopeClimber.h"
#include "Subsystems/GearSystem.h"



OI* CommandBase::controls = NULL;
DriveTrain* CommandBase::drivetrain = NULL;
RopeClimber* CommandBase::ropeclimber = NULL;
GearSystem* CommandBase::gearsystem = NULL;

CommandBase::CommandBase(char const *name): frc::Command(name) {}

CommandBase::CommandBase(): frc::Command() {}

void CommandBase::init() {

	std::cout << "[commandbase] CommandBase initalizing..." << std::endl;

	drivetrain = new DriveTrain();
	controls = new OI();
	ropeclimber = new RopeClimber();
	gearsystem = new GearSystem();

	std::cout << "[commandbase] CommandBase initialized." << std::endl;
}
