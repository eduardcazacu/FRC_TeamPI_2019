
#ifndef PIAIM_H_
#define PIAIM_H_

#include "PiAim.h"


PiAim::PiAim(PiMovement *driveStation, C04_PI_Pixy *pixy){
    this->driveStation = driveStation;
    this->pixy = pixy;
}
    
bool PiAim::EasyAim(){

    uint8_t *info = pixy->GetBlocks();
    return CalculateMovement(info);

}

bool PiAim::CalculateMovement(uint8_t *info){

    double stopDistance = 16;
    double fullSpeedDistance = 60;
    double speed = 0.1;
    double turnRate = 0.6;
    double angelError = info[0];
    errorSum += angelError;

    double angleI = 0.00001;

    std::cout<<angelError<<std::endl;
    double currentDistance = info[1];
    std::cout<<currentDistance<<"      ";
    //std::cout<<distance<<std::endl;
 
    
    double driveSpeed = (currentDistance - fullSpeedDistance) / (stopDistance - fullSpeedDistance);
    std::cout<<driveSpeed<<std::endl;

    //double PAngle = (angelError*0.0077-1.1538)*turnRate;
    double PAngle = angelError*turnRate;
    double IAngle = errorSum * angleI;
    //std::cout<<errorSum<<std::endl;
    double turning = PAngle /*+ IAngle*/ ;
    //driveSpeed = 0;

    turning = turning *0,13*0,37;

    double output[2] = {driveSpeed, turning};
    this->driveStation->move(-output[0],output[1]);
    return false;

}

#endif