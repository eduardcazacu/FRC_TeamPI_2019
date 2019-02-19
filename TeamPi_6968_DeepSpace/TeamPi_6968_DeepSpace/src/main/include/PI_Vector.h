
#pragma once

#include <iostream>
#include <stdint.h>
#include <math.h>

class PI_Vector{

    private:

    //calculate the direction of the vector
    double Dir();
    double Height();

    

    public:
    uint8_t x0;
    uint8_t x1;
    uint8_t y0;
    uint8_t y1;

    uint8_t index;
    unsigned int lifeTime = 0;

    //creates the vectors from an array what it gets from the arduino
    PI_Vector(uint8_t info[5]);
    //PI_Vector(uint8_t _index, uint8_t _x0, uint8_t _y0, uint8_t _x1, uint8_t _y1);

   

    double CenterX(); //pixel x of the center
    double CenterY(); //pixel y of the center
    double Angle(); //angle in radians between -PI/2 and PI/2
    double Length(); //pixel length

    double NearestX();
    double NearestY();

    //parallel gives -1 back
    double IntersectX(PI_Vector vector2);
    double IntersectY(PI_Vector vector2);

    void Print();

};