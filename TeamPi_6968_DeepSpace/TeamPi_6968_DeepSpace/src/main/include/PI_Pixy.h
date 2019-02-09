
#pragma once

#include <iostream>
#include <frc/I2C.h>
#include <ArduinoI2C.h>
#include <PI_Vector.h>
#include <vector>

class PI_Pixy{

    private:

    ArduinoI2C *i2cBus;

    public:

    //This is a list with all the Vectors
    std::vector<PI_Vector> vectorList;

    //This needs the port and address and creates a connection with the arduino
    //returns nothing
    PI_Pixy(frc::I2C::Port, int address);
    
    //this updates the vector list by reading from the arduino
    void Update();


};
