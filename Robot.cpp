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
#include "Commands/TeleopDefault.h"
#include "Commands/DropGear.h"
#include "Commands/PushGear.h"
#include "Commands/AutoDrive.h"
#include "Commands/DoNothing.h"
#include "Commands/AutoDriveAtPeg.h"
#include "Commands/AutoDriveAtPegFromLeft.h"
#include "Commands/AutoDriveAtPegFromRight.h"
#include "Commands/Drive.h"
#include "CommandBase.h"

using namespace frc;
using namespace std;

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

		cout << "[robot] Robot initalizing..." << endl;



		CommandBase::init(); //Initializes all commands and subsystems


		//Moved to down here because sometimes the SmartDashboard forgets to add them.
		std::thread visionThread(VisionThread);
		visionThread.detach();

		teleopChooser.AddDefault("Default Driver", new TeleopDefault());

		/*autonomousChooser.AddDefault("Center Start (appx. 14.25 seconds)", new Drive());
		autonomousChooser.AddObject("Right Start (appx ? seconds)", new DoNothing());
		autonomousChooser.AddObject("AutoDriveForward", new Drive());
		*/

		autonomousChooser.AddDefault("Drive at Peg (center)", new AutoDriveAtPeg());
		autonomousChooser.AddObject("Drive at Peg (left)", new AutoDriveAtPegFromLeft());
		autonomousChooser.AddObject("Drive at Peg (right)", new AutoDriveAtPegFromRight());

		SmartDashboard::PutData("Autonomous Modes", &autonomousChooser);
		SmartDashboard::PutData("Teleoperated Modes", &teleopChooser);

		cout << "[robot] Robot initialization complete!" << endl;
	}

	void DisabledInit() override {
		frc::Scheduler::GetInstance()->ResetAll();
		frc::Scheduler::GetInstance()->RemoveAll(); //Trying this out. Maybe this will work, maybe not. :P
	}

	void AutonomousInit() override {
		autonomousMode.release(); //RELINQUISH THE AUTONOMOUS!
		autonomousMode.reset(autonomousChooser.GetSelected());
		if (autonomousMode != nullptr) {

			autonomousMode->Start();
			cout << "[autonomous] Autonomous program has started." << endl;
		} else {
			cout << "[autonomous] There was a problem starting the autonomous mode." << endl;
		}
	}

	void AutonomousPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

	void TeleopInit() override {
		teleopMode.release(); //RELINQUISH THE TELEOP!
		teleopMode.reset(teleopChooser.GetSelected());
		if (teleopMode != nullptr) {
			cout << "[teleop] Teleop mode is starting." << endl;
			teleopMode->Start();
		} else {
			cout << "[teleop] Teleop mode could not start." << endl;
		}
	}

	void TeleopPeriodic() override {
		frc::Scheduler::GetInstance()->Run();
	}

};
START_ROBOT_CLASS(Robot);
