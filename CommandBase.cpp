#include "CommandBase.h"

#include <Commands/Scheduler.h>

#include "Subsystems/VisionTracking.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/RopeClimber.h"
#include "Subsystems/GearSystem.h"
#include "Subsystems/Debug.h"

VisionTracking* CommandBase::vt = NULL;
OI* CommandBase::controls = NULL;
DriveTrain* CommandBase::drivetrain = NULL;
RopeClimber* CommandBase::ropeclimber = NULL;
GearSystem* CommandBase::gearsystem = NULL;
Debug* CommandBase::debug = NULL;


CommandBase::CommandBase(char const *name): frc::Command(name) {}

CommandBase::CommandBase(): frc::Command() {}

void CommandBase::init() {

	std::cout << "[commandbase] CommandBase initalizing..." << std::endl;

	drivetrain = NULL;
	controls = NULL;
	ropeclimber = NULL;
	gearsystem = NULL;
	vt = NULL;
	debug = NULL;

	drivetrain = new DriveTrain();
	controls = new OI();
	ropeclimber = new RopeClimber();
	gearsystem = new GearSystem();
	vt = new VisionTracking();
	debug = new Debug();

	std::cout << "[commandbase] CommandBase initialized." << std::endl;
}
