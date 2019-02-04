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

#include <cstdint>
#include <frc/I2C.h>

class C05_PI_Ultrasoon
{
    private:
    char *_address;


    public:
    /*
        Description:    constructor
        Input:          char address - the hex value of the address of the current sensor
        Output:         void
    */
    C05_PI_Ultrasoon(char address);

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
    uint8_t getRaw();

};