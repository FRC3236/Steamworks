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
*	+ Kevin Kohls
*
*  	Thanks to all the teams who helped us
*  	out via email and through ChiefDelphi!
*
*/

//I just wanna see shweg. -Kevin, 2k17.

#include <Commands/AutoDriveAtPegFromLeft.h>
#include <Commands/AutoDriveAtPegFromRight.h>
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
#include "Subsystems/Debug.h"
#include "Commands/TeleopDefault.h"
#include "Commands/DropGear.h"
#include "Commands/PushGear.h"
#include "Commands/DoNothing.h"
#include "Commands/AutoDrive.h"
#include "Commands/AutoDriveAtPeg.h"
#include "Commands/AutoDriveAtPegFromLeft.h"
#include "Commands/AutoDriveAtPegFromRight.h"
#include "Commands/AutoDriveFromLeftNV.h"
#include "Commands/AutoDriveFromRightNV.h"
#include "CommandBase.h"

using namespace frc;
using namespace std;

double Debug = false;


class Robot: public IterativeRobot {
private:
	SendableChooser<Command*> autonomousChooser;
	SendableChooser<Command*> teleopChooser;
	unique_ptr<Command> autonomousMode;
	unique_ptr<Command> teleopMode;
	Command* teleopDefault;
	Command* autoDefault;

	static void VisionThread() {
		cs::UsbCamera camera = CameraServer::GetInstance()->StartAutomaticCapture();
		camera.SetBrightness(20);
		if (camera.IsConnected()) {
			camera.SetResolution(640,480);
			camera.SetFPS(60);
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

		CommandBase::init(); //Initializes all commands and subsystems

		//Moved to down here because sometimes the SmartDashboard forgets to add them.
		std::thread visionThread(VisionThread);
		visionThread.detach();
	}

	void DisabledInit() override {
		CommandBase::debug->ResetTracking();
		frc::Scheduler::GetInstance()->ResetAll();
		frc::Scheduler::GetInstance()->RemoveAll();


		teleopChooser.AddDefault("Default Driver", new TeleopDefault());

		autonomousChooser.AddDefault("Drive at Peg (center) [NV]", new AutoDrive());
		autonomousChooser.AddObject("Drive at Peg (left) [NV]", new AutoDriveFromLeftNV());
		autonomousChooser.AddObject("Drive at Peg (right) [NV]", new AutoDriveFromRightNV());
		autonomousChooser.AddObject("Drive at Peg (center) [VT]", new AutoDriveAtPeg());

		SmartDashboard::PutData("Autonomous Modes", &autonomousChooser);
		SmartDashboard::PutData("Teleoperated Modes", &teleopChooser);

	}

	void AutonomousInit() override {
		CommandBase::debug->StartTracking();
		CommandBase::debug->Enable();
		autonomousMode.release(); //RELINQUISH THE AUTONOMOUS!
		autonomousMode.reset(autonomousChooser.GetSelected());
		if (autonomousMode != nullptr) {

			autonomousMode->Start();
			CommandBase::debug->LogWithTime("AutoInit", "Starting autonomous program...");
		} else {
			CommandBase::debug->LogWithTime("AutoInit", "Autonomous program could not start.");
		}
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		CommandBase::debug->StartTracking();
		CommandBase::debug->Enable();
		teleopMode.release(); //RELINQUISH THE TELEOP!
		teleopMode.reset(teleopChooser.GetSelected());
		if (teleopMode != nullptr) {
			CommandBase::debug->LogWithTime("TeleopInit", "Starting teleop program...");
			teleopMode->Start();
		} else {
			CommandBase::debug->LogWithTime("TeleopInit", "Teleop program could not start.");
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

};
START_ROBOT_CLASS(Robot);
