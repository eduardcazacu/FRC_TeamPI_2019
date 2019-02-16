
#pragma once

#include <iostream>
#include "ArduinoI2C.h"
#include "PI_Vector.h"
#include <vector>


#define PIXY_HEIGHT 51
#define PIXY_WIDTH 78

#define AMOUNTOFVECTORS 10

class C04_PI_Pixy{

    private:

    ArduinoI2C *i2cBus;
    void AddVector(PI_Vector vector);

    public:
    //This needs the port and address and creates a connection with the arduino
    //returns nothing
    C04_PI_Pixy(frc::I2C::Port port, int address);

    PI_Vector* latestVector;

    //This is a list with all the Vectors
    std::vector<PI_Vector> vectorList;
    
    //this updates the vector list by reading from the arduino
    //returns nothing
    void Update();
    PI_Vector LatestVector();
    PI_Vector BestVector();

    
};
