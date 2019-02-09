
#pragma once

#include <iostream>

class PI_Vector{
    private:
    public:

    //creates the vectors from an array what it gets from the arduino
    PI_Vector(uint8_t info[5]);

    uint8_t index;
    uint8_t x0;
    uint8_t x1;
    uint8_t y0;
    uint8_t y1;

};