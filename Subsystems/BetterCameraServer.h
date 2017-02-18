#ifndef CameraServer_H
#define CameraServer_H

#include <Commands/Subsystem.h>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class BetterCameraServer : public Subsystem {
private:

	//cs::UsbCamera cam0, cam1, currentCamera;
	bool started;
	double currentcamid;
	//void camerathread;
	//AtomicImager selected;

public:
	BetterCameraServer();
	void Initialize();
	void Start();
	void SetCamera(double);
	void SwitchCamera();
	void Thread();
};

#endif  // CameraServer_H
