#include <Wire.h>
#include <Pixy2.h>


Pixy2 pixy;

 uint8_t x;
 uint8_t width;

void setup() {
  pixy.init();
  pixy.setLamp(0, 0);
  pixy.setLED(0, 255, 0);

 
  //setup of the connection
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event 
  Serial.begin(9600);
}

void loop() {
  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks)
  {
    x = pixy.ccc.blocks[0].m_x; //between (0 to 319)
    width = pixy.ccc.blocks[0].m_width ; //between (1 to 320)
    //pixy.ccc.blocks[0].print();
  }
  double printX = x;
  Serial.println(x);

}

void requestEvent() {
  byte data[2] = {x,width};
  Wire.write(data, 2);
  //Serial.println(data[2]);
}
