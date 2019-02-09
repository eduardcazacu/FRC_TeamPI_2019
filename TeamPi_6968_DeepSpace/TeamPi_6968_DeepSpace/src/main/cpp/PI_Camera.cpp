
#include "PI_Camera.h"

PI_Camera::PI_Camera(){
    frc::CameraServer::GetInstance()->StartAutomaticCapture();
}

