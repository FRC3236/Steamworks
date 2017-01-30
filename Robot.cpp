/*
*
*  $$$$$$$$\        $$\ $$$$$$$$\                                             $$$$$$\   $$$$$$\   $$$$$$\   $$$$$$\
*  \__$$  __|       \__|$$  _____|                                           $$ ___$$\ $$  __$$\ $$ ___$$\ $$  __$$\
*     $$ | $$$$$$\  $$\ $$ |    $$$$$$\   $$$$$$\   $$$$$$$\  $$$$$$\        \_/   $$ |\__/  $$ |\_/   $$ |$$ /  \__|
*     $$ |$$  __$$\ $$ |$$$$$\ $$  __$$\ $$  __$$\ $$  _____|$$  __$$\         $$$$$ /  $$$$$$  |  $$$$$ / $$$$$$$\
*     $$ |$$ |  \__|$$ |$$  __|$$ /  $$ |$$ |  \__|$$ /      $$$$$$$$ |        \___$$\ $$  ____/   \___$$\ $$  __$$\
*     $$ |$$ |      $$ |$$ |   $$ |  $$ |$$ |      $$ |      $$   ____|      $$\   $$ |$$ |      $$\   $$ |$$ /  $$ |
*     $$ |$$ |      $$ |$$ |   \$$$$$$  |$$ |      \$$$$$$$\ \$$$$$$$\       \$$$$$$  |$$$$$$$$\ \$$$$$$  | $$$$$$  |
*     \__|\__|      \__|\__|    \______/ \__|       \_______| \_______|       \______/ \________| \______/  \______/
*
*  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*
*  Lead Programmer: Eric Bernard
*  Programmer's Assistants:
*  	+ John Winship
*  	+ Antonio Figueiredo
*
*  	Thanks to all the teams who helped us
*  	out via email and through ChiefDelphi!
*
*/


#include <memory>

#include <Commands/Command.h>
#include <Commands/Scheduler.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

#include "Commands/AutoDefault.h"
#include "Commands/TeleopDefault.h"
#include "CommandBase.h"

class Robot: public frc::IterativeRobot {
private:
	frc::SendableChooser<frc::Command*> autonomousChooser;
	frc::SendableChooser<frc::Command*> teleopChooser;
	std::unique_ptr<frc::Command> autonomousMode;
	std::unique_ptr<frc::Command> teleopMode;

public:
	void RobotInit() override {
		std::cout << "[robot] Robot initalizing..." << std::endl;

		CommandBase::init();
		teleopChooser.AddDefault("Default", new TeleopDefault());
		autonomousChooser.AddDefault("Default", new AutoDefault());

		frc::SmartDashboard::PutData("Auto Modes", &autonomousChooser);
		frc::SmartDashboard::PutData("Teleop Modes", &teleopChooser);

		std::cout << "[robot] Robot initialized." << std::endl;
	}

	void AutonomousInit() override {
		autonomousMode.reset(autonomousChooser.GetSelected());
		if (autonomousMode != nullptr) {
			autonomousMode->Start();
			std::cout << "[autonomous] Autonomous program has started." << std::endl;
		} else {
			std::cout << "[autonomous] There was a problem starting the autonomous mode." << std::endl;
		}
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		teleopMode.reset(teleopChooser.GetSelected());
		if (teleopMode != nullptr) {
			std::cout << "[teleop] Teleop mode is starting." << std::endl;
			teleopMode->Start();
		} else {
			std::cout << "[teleop] Teleop mode could not start." << std::endl;
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}
};

START_ROBOT_CLASS(Robot);
