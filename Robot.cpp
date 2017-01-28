#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Commands/ExampleCommand.h"
#include "Commands/AutoDefault.h"
#include "Commands/TeleopDefault.h"
#include "Commands/TestCommand.h"
#include "CommandBase.h"

class Robot: public frc::IterativeRobot {
private:
	frc::SendableChooser<frc::Command*> autonomousChooser;
	frc::SendableChooser<frc::Command*> teleopChooser;
	std::unique_ptr<frc::Command> autonomousMode;
	std::unique_ptr<frc::Command> teleopMode;

public:
	void RobotInit() override {
		std::cout << "ROBOT INIT!" << std::endl;

		CommandBase::init();
		teleopChooser.AddDefault("Default", new TeleopDefault());

		autonomousChooser.AddDefault("Default", new AutoDefault());
		autonomousChooser.AddObject("Example", new ExampleCommand());
		autonomousChooser.AddObject("Test", new TestCommand());
		frc::SmartDashboard::PutData("Auto Modes", &autonomousChooser);
	}

	void AutonomousInit() override {
		autonomousMode.reset(autonomousChooser.GetSelected());
		std::cout << "Autonomous mode: " << autonomousChooser.GetSelected() << std::endl;
		if (autonomousMode != nullptr) {
			autonomousMode->Start();
			std::cout << "HOUSTON, WE HAVE LIFTOFF" << std::endl << "/" << std::endl;
		} else {
			std::cout << "HOUSTON, WE HAVE A PROBLEM!" << std::endl << "/" << std::endl;
		}
	}

	void AutonomousPeriodic() override {
		std::cout << "AutonomousPeriodic " << frc::Scheduler::GetInstance() << std::endl;
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to
		// continue until interrupted by another command, remove
		// this line or comment it out.

		teleopMode.reset(teleopChooser.GetSelected());
		if (teleopMode != nullptr) {
			teleopMode->Start();
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot);
