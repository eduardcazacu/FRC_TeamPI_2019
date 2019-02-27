#include "PI_Navigator.h"

PI_Navigator::PI_Navigator(int ManualControllerID)
{
    this->ManualController = new frc::XboxController(ManualControllerID);
    this->gamePadPOVLeft = new frc::POVButton(*ManualController, 270);
    this->gamePadPOVDown = new frc::POVButton(*ManualController, 180);
    this->gamePadPOVRight = new frc::POVButton(*ManualController, 90);
    this->gamePadPOVUp = new frc::POVButton(*ManualController, 0);
}

double PI_Navigator::manualGrip()
{
    return ManualController->GetTriggerAxis(frc::GenericHID::kRightHand);
}

bool PI_Navigator::extendGrabber()
{
    return this->ManualController->GetYButtonPressed();
}

bool PI_Navigator::retractGrabber()
{
    return this->ManualController->GetAButtonPressed();
}

bool PI_Navigator::grip()
{
    return this->ManualController->GetBButtonPressed();
}
bool PI_Navigator::release()
{
    return this->ManualController->GetXButtonPressed();
}
double PI_Navigator::ManualLift()
{
    return -this->ManualController->GetY(frc::GenericHID::kRightHand);
}
bool PI_Navigator::liftOff()
{
    return this->gamePadPOVLeft->Get();
}
bool PI_Navigator::lvl0Btn()
{
    return this->gamePadPOVDown->Get();
}

bool PI_Navigator::lvl1Btn()
{
    return this->gamePadPOVRight->Get();
}
bool PI_Navigator::lvl2Btn()
{
    return this->gamePadPOVUp->Get();
}