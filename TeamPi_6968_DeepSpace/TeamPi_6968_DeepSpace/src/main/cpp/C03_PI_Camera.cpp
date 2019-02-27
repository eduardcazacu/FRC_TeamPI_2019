
#include "C03_PI_Camera.h"

C03_PI_Camera::C03_PI_Camera(){
    frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
}

