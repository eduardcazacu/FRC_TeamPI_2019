
#include "C03_PI_Camera.h"

C03_PI_Camera::C03_PI_Camera(){
    frc::CameraServer::GetInstance()->StartAutomaticCapture("cam0");
    frc::CameraServer::GetServer()->StartAutomaticCapture("cam0");
}

