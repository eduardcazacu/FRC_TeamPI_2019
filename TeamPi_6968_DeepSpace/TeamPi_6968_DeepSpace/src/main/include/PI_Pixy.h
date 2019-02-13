
#pragma once

#include <iostream>
#include <frc/I2C.h>
#include <ArduinoI2C.h>
#include <PI_Vector.h>
#include <vector>

class PI_Pixy{

    private:

    ArduinoI2C *i2cBus;
    void AddVector(PI_Vector vector);

    public:

    //Constructor
    //This needs the port and address and creates a connection with the arduino
    //returns nothing
    PI_Pixy(frc::I2C::Port, uint8_t address);

    PI_Vector *latestVector;

    //This is a list with all the Vectors
    std::vector<PI_Vector> vectorList;


    
    //this updates the vector list by reading from the arduino
    void Update();


};
