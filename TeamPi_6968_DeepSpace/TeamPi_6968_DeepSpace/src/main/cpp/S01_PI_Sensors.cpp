#include "S01_PI_Sensors.h"

S01_PI_Sensors::S01_PI_Sensors(){
    //allocate memory for all the sensors here:
    USLeft = new C05_PI_Ultrasoon(US_LEFT,100,900);  //an ultrasound sensor on the default i2c port
    USRight = new C05_PI_Ultrasoon(US_RIGHT,100,900);  //an ultrasound sensor on the default i2c port

    IRFront =  new PI_IR(IR_FRONT,IR_DIST_THRESHOLD);
    IRBack =  new PI_IR(IR_BACK,IR_DIST_THRESHOLD);
}   

void S01_PI_Sensors::refresh(){
    //encoder stuff here probably:
}