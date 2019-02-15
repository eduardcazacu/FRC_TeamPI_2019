#include "S01_PI_Sensors.h"

S01_PI_Sensors::S01_PI_Sensors(){
    //allocate memory for all the sensors here:
    USRight =   new C05_PI_Ultrasoon(frc::I2C::Port::kOnboard,US_RIGHT,2,0,1,100,900);  //an ultrasound sensor on the default i2c port
    USLeft =    new C05_PI_Ultrasoon(frc::I2C::Port::kOnboard,US_LEFT,2,1,2,100,900);  //an ultrasound sensor on the default i2c port, sync 2 sensors priority 0 on pin 1
    

    IRFront =  new PI_IR(IR_FRONT,IR_DIST_THRESHOLD);
    IRBack =  new PI_IR(IR_BACK,IR_DIST_THRESHOLD);

    PixyDown = new C04_PI_Pixy(frc::I2C::Port::kOnboard, 8);

    camera = new C03_PI_Camera();
}   

void S01_PI_Sensors::refresh(){
    //encoder stuff here probably:

    PixyDown->Update();
}