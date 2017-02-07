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
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

//Include all the commands//
#include "Commands/AutoDefault.h"
#include "Commands/TeleopDefault.h"
#include "Commands/DropGear.h"
#include "Commands/PushGear.h"

#include "CommandBase.h"

class Robot: public frc::IterativeRobot {
private:
	frc::SendableChooser<frc::Command*> autonomousChooser;
	frc::SendableChooser<frc::Command*> teleopChooser;
	std::unique_ptr<frc::Command> autonomousMode;
	std::unique_ptr<frc::Command> teleopMode;


	static void VisionThread() {
		cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
		if (camera.IsConnected()) {
			camera.SetResolution(640,480);
			camera.SetFPS(30);
			cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
			cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("Color", 640, 480);
			cv::Mat source;
			cv::Mat output;
			while (true) {
				cvSink.GrabFrame(source);
				cvtColor(source, output, cv::COLOR_BGR2RGB);
				outputStreamStd.PutFrame(output);
			}
		}
	}


public:
	void RobotInit() override {
		std::cout << "[robot] Robot initalizing..." << std::endl;

		std::thread visionThread(VisionThread);
		visionThread.detach();

		CommandBase::init();

		teleopChooser.AddDefault("Default Driver", new TeleopDefault());
		autonomousChooser.AddDefault("AutoDefault", new AutoDefault());
		autonomousChooser.AddObject("DropGear", new DropGear());
		autonomousChooser.AddObject("PushGear", new PushGear());
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
		//std::cout << "AutoPeriodic Before" << std::endl;
		frc::Scheduler::GetInstance()->Run();
		//std::cout << "AutoPeriodic After" << std::endl;
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
		//std::cout << "TeleopPeriodic before" << std::endl;
		frc::Scheduler::GetInstance()->Run();
		//std::cout << "TeleopPeriodic after" << std::endl;
	}

	void DisabledInit() override {
		std::cout << "[robot] Reseting all frc scheduler instances..." << std::endl;
		frc::Scheduler::GetInstance()->ResetAll();
		frc::Scheduler::GetInstance()->RemoveAll(); //Trying this out. Maybe this will work, maybe not. :P
	}

};
START_ROBOT_CLASS(Robot);
