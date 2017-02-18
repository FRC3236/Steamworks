/*#include "BetterCameraServer.h"
#include "../RobotMap.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


BetterCameraServer::BetterCameraServer() : Subsystem("BetterCameraServer") {
	started = false;
	currentcamid = 0;

}

void BetterCameraServer::Initialize() {

	this->cam0 = new cs::UsbCamera(0);
	this->cam1 = new cs::UsbCamera(1);
	this->started = false;
	this->currentCamera = this->cam0;
}

void BetterCameraServer::Start() {
	if (this->started) {
		return;
	}
	this->started = true;
}

void BetterCameraServer::SetCamera(double CamID) {
	if (CamID == 0) {
		this->currentCamera = this->cam0;
		this->currentcamid = 0;
	} else if (CamID == 1) {
		this->currentCamera = this->cam1;
		this->currentcamid = 1;
	} else {
		this->currentCamera = this->cam0; //default to 0;
		this->currentcamid = 0;
	}
}

void BetterCameraServer::SwitchCamera() {
	if (this->currentcamid == 0) {
		this->currentCamera = this->cam1;
		this->currentcamid = 1;
	} else {
		this->currentCamera = this->cam0;
		this->currentcamid = 0;
	}
}

void BetterCameraServer::Thread() {
	if (this->currentCamera.IsConnected()) {
		while (true) {
			frc::CameraServer::GetInstance()->StartAutomaticCapture(this->currentCamera);
			this->currentCamera.SetResolution(640,480);
			this->currentCamera.SetFPS(30);
			cs::CvSink cvSink = frc::CameraServer::GetInstance()->GetVideo();
			cs::CvSource outputStream = frc::CameraServer::GetInstance()->PutVideo("Color", 640, 480);
			cv::Mat source;
			cv::Mat output;
			cvSink.GrabFrame(source);
			cvtColor(source, output, cv::COLOR_BGR2RGB);
			outputStream.PutFrame(output);
		}
	}
}*/
