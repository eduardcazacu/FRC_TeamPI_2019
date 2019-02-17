/*

created by Eduard Cazacu on 08 February 2019
Team pi 6968
*/

#pragma once


#include "PI_TargetNames.h"
#include <frc/XboxController.h>
#include <frc/buttons/Button.h>
#include "frc/buttons/POVButton.h"



class PI_Navigator
{   
    public:
        PI_Navigator(int controllerID);
        frc::XboxController *ManualController;
        frc::POVButton *gamePadPOV0;
        frc::POVButton *gamePadPOV1;
        frc::POVButton *gamePadPOV2;
        
        // manual gripper
        double manualGrip();
        bool extendGrabber();
        bool retractGrabber();
        bool grip();
        bool release();
        //lift 
        double  ManualLift();
        bool lvl0Btn();
        bool lvl1Btn();
        bool lvl2Btn();

        AutoTarget target;

    private:
};