//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//

#include <Wire.h>
#include <Pixy2.h>

Pixy2 pixy;

/this are the values of the vectors it sees
uint8_t index;
uint8_t x0;
uint8_t y0;
uint8_t x1;
uint8_t y1;

void setup()
{/*
  Serial.begin(115200);
  Serial.print("Starting...\n");
*/

  // change to the line_tracking program.  Note, changeProg can use partial strings, so for example,
  // you can change to the line_tracking program by calling changeProg("line") instead of the whole
  // string changeProg("line_tracking")

  // we need to initialize the pixy object
  pixy.init();
  // Change to line tracking program
  pixy.changeProg("line");

  //int8_t setLamp(uint8_t upper, uint8_t lower)


  //setup of the connection
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop()
{
  //scan camera's
  pixy.line.getMainFeatures();

  /*if (pixy.line.numVectors)
    Serial.println(pixy.line.vectors->m_x0);*/
  index = pixy.line.vectors->m_index;
  x0 = pixy.line.vectors->m_x0;
  y0 = pixy.line.vectors->m_y0;
  x1 = pixy.line.vectors->m_x1;
  y1 = pixy.line.vectors->m_y1;

}

//this function is called everytime the roboRIO is asking for something from the I2C
void requestEvent() {
  
  //Send the data back;
  byte data[5] = {index, x0, y0, x1, x1};
  Wire.write(data, 5);


  }
