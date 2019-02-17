#include "PI_Navigator.h"

PI_Navigator::PI_Navigator(int ManualControllerID)
{
    this->ManualController = new frc::XboxController(ManualControllerID);
    this->gamePadPOV0 = new frc::POVButton(*ManualController, 180);
    this->gamePadPOV1 = new frc::POVButton(*ManualController, 90);
    this->gamePadPOV2 = new frc::POVButton(*ManualController, 0);
}

double PI_Navigator::manualGrip(){
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
bool PI_Navigator::lvl0Btn()
{
    return this->gamePadPOV0->Get();
}

bool PI_Navigator::lvl1Btn(){
    return this->gamePadPOV1->Get();

}
bool PI_Navigator::lvl2Btn(){
    return this->gamePadPOV2->Get();

}