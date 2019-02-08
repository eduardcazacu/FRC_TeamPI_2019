/*----------------------------------------------------------------------------      */
/*  Copyright (c) 2019 TEAM PI 6968                                                 */
/*  IR sensor class                                                                 */
/*  Created by Eduard Cazacu on 2019-02-04    
/*                                                                                  */
/*  This will handle the comunication with the current sensors that read the output */
/*  from the Elobau ultrasound distance sensors. It also handles the conversion to  */
/*  mm when the default range is set on the sensors themselves.                     */
/*                                                                                  */
/*  Ultrasound sensors used: ELOBAU UC18MIC090S                                     */
/*  Default range is 100mm - 900mm                                                  */

#pragma once

#define DEFAULT_PORT frc::I2C::Port::kOnboard

//ultrasound sensor reported current range
#define I_MIN 4             
#define I_MAX 20
//ultrasound sensor default distance range(in mm)
#define D_MIN 100
#define D_MAX 900

#include <cstdint>
#include <frc/I2C.h>
#include "Adafruit_INA219.h"    //current sensor library



class C05_PI_Ultrasoon
{
    private:
    Adafruit_INA219 *_currentSensor;
    double _rangeMin,_rangeMax;

    /*
        Description:    A map function similar to the arduino one
                        Probably only works for positive value. Too braindead to think 
                        about it right now.
        Input:          The value to map, range for the value to map, range for the mapped value
        Output:         Mapped value         
    */
    double map(double x, double xMin, double xMax, double yMin, double yMax);

    public:
    /*
        Description:    constructor
        Input:          char address - the hex value of the address of the current sensor
        Output:         void
    */
    C05_PI_Ultrasoon(frc::I2C::Port i2c_port,uint8_t address, double rangeMin = D_MIN, double rangeMax = D_MAX);
    C05_PI_Ultrasoon(uint8_t address, double rangeMin = D_MIN, double rangeMax = D_MAX);

    /*
        description:    returns the distance recorded by the distance sensor.
        Input:          none
        Output:         [double] distance in mm from the sensor.
    */
    double getDist();

    /*  description:    Get the raw values from the current sensor
        Input           void;
        Output          [char] raw current sensor value
    */
    uint16_t getRaw();

    /*
        description:    Get the current value reported by the current sensor
        Input:          void
        Output:         [double] current in mA
    */
   double getCurrent();
    
};