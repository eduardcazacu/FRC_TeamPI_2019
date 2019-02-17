#include "PI_Navigator.h"

PI_Navigator::PI_Navigator(int ManualControllerID)
{
    this->*ManualController = new frc::Controller(ManualControllerID);
    this->*gamePadPOV0 = new frc::POVButton(frc::GenericHID::kHIDGamepad, 270, 0);
    this->*gamePadPOV1 = new frc::POVButton(frc::GenericHID::kHIDGamepad, 0, 0);
    this->*gamePadPOV2 = new frc::POVButton(frc::GenericHID::kHIDGamepad, 360, 0);
}
bool PI_Navigator::climbUpBtn()
{
    this->*ManualController->
}

bool PI_Navigator::climbFrontDownBtn()
{
    return this->ManualController->GetXButtonPressed();
}

bool PI_Navigator::lastGripperExtendBtn()
{
    return this->ManualController->GetYButtonPressed();
}

bool PI_Navigator::gripperRetractBtn()
{
    return this->ManualController->GetAButtonPressed();
}

bool PI_Navigator::gripBtn()
{
    return this->ManualController->GetTriggerAxis(joystickHand::kRightHand);
}
double PI_Navigator::ManualLift()
{
    return this->ManualController->GetY(JoystickHand::kRightHand);
}
bool PI_Navigator::lvl0Btn()
{
    return this->ManualController->get
}

bool PI_Navigator::lvl0Btn90(){
    return this->gamePadPOV0->Get();

}