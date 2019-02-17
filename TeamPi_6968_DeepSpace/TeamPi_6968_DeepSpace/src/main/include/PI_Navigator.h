/*

created by Eduard Cazacu on 08 February 2019
Team pi 6968
*/

#pragma once


#include "PI_TargetNames.h"
#include <XboxController.h>
#include <frc/buttons/Button.h>



class PI_Navigator
{   
    public:
        PI_Navigator(uint8_t controllerID);
        frc::XboxController *ManualController;
        frc::POVButton *gamePadPOV0;
        frc::POVButton *gamePadPOV1;
        frc::POVButton *gamePadPOV2;

        //manual climbing 
        bool climbUpBtn();
        bool climbFrontDownBtn();
        bool climbBackDownBtn();
        
        // manual gripper
        bool lastGripperExtendBtn();
        bool gripperRetractBtn();
        bool gripBtn();
        //lift 
        double  ManualLift();
        bool lvl0Btn();
        bool lvl1Btn();
        bool lvl2Btn();

        AutoTarget target;

    private:
};