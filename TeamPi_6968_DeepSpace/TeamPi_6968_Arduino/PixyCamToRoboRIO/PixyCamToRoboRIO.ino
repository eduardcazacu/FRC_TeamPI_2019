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

Pixy2 pixyUp;
Pixy2 pixyDown;

//this are the values of the vectors it sees
uint8_t pixyUp_id = 0;
uint8_t pixyUp_index;
uint8_t pixyUp_x0;
uint8_t pixyUp_y0;
uint8_t pixyUp_x1;
uint8_t pixyUp_y1;

uint8_t pixyDown_id = 1;
uint8_t pixyDown_index;
uint8_t pixyDown_x0;
uint8_t pixyDown_y0;
uint8_t pixyDown_x1;
uint8_t pixyDown_y1;

int ssUp = 10;
int ssDown = 9;
//inr ssDown = ...;

int selectedID = 0;

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");

  // change to the line_tracking program.  Note, changeProg can use partial strings, so for example,
  // you can change to the line_tracking program by calling changeProg("line") instead of the whole
  // string changeProg("line_tracking")

  // we need to initialize the pixy object
  pixyUp.init();
  pixyDown.init();
  pinMode(ssUp,OUTPUT);
  pinMode(ssDown,OUTPUT);
  digitalWrite(ssUp,HIGH);
  digitalWrite(ssDown,HIGH);
  // Change to line tracking program
  pixyDown.changeProg(LINE_MODE_WHITE_LINE);
  pixyUp.changeProg(LINE_MODE_WHITE_LINE);
  pixyDown.changeProg(LINE_MODE_WHITE_LINE);
  pixyUp.setLamp(1, 1);
  pixyDown.setLamp(1, 1);

  
  //setup of the connection
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
}

void loop()
{
  //scan camera's
  digitalWrite(ssUp,LOW);
  pixyUp.line.getMainFeatures();

  /*if (pixyUp.line.numVectors)
    Serial.println(pixyUp.line.vectors->m_x0);*/
    
  Serial.println(pixyUp.line.vectors->m_index);
  pixyUp_index = pixyUp.line.vectors->m_index;
  pixyUp_x0 = pixyUp.line.vectors->m_x0;
  pixyUp_y0 = pixyUp.line.vectors->m_y0;
  pixyUp_x1 = pixyUp.line.vectors->m_x1;
  pixyUp_y1 = pixyUp.line.vectors->m_y1;
  digitalWrite(ssUp,HIGH);

  digitalWrite(ssDown,LOW);
  pixyDown.line.getMainFeatures();

  /*if (pixyUp.line.numVectors)
    Serial.println(pixyUp.line.vectors->m_x0);*/
  pixyDown_index = pixyDown.line.vectors->m_index;
  pixyDown_x0 = pixyDown.line.vectors->m_x0;
  pixyDown_y0 = pixyDown.line.vectors->m_y0;
  pixyDown_x1 = pixyDown.line.vectors->m_x1;
  pixyDown_y1 = pixyDown.line.vectors->m_y1;
  digitalWrite(ssDown,HIGH);
  

}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  selectedID = Wire.read();    // receive byte as an integer
}

//this function is called everytime the roboRIO is asking for something from the I2C
void requestEvent() {
  if(selectedID == 0){
    //Send the data back;
    byte data[5] = {pixyUp_index, pixyUp_x0, pixyUp_y0, pixyUp_x1, pixyUp_y1};
    Wire.write(data, 5);
  }else{
    byte data[5] = {pixyDown_index, pixyDown_x0, pixyDown_y0, pixyDown_x1, pixyDown_y1};
    Wire.write(data, 5);
  }


  }
