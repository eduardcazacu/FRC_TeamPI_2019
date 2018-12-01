/*
 Name:		ShieldTest.ino
 Created:	11/27/2018 8:41:56 PM
 Author:	Eduard Cazacu


 DESCRIPTION:	This is a test code meant to verify the functionality of the
				Team pi's arduino training shield.
				It is meant for the Arduino Uno or Mega. (This code is for the MEGA)

SHIELD COMPONENTS:	The shield has 3 leds, one rgb led conected to pwm pins, 2 pushbuttons
					WITH NO PULLUP RESISTORS -internal pullups need to be used - one
					slide switch with 2 positions (HIGH, LOW) and one potentiometer

PINOUT:

LED[0,2]	: 6, 7, 8 
RGB			: 9, 10 , 11
SW			: 4
POT(10K)	: A0
Pushbuttons	: 2, 3


TEST FUNCTIONALITY:	When the board is soldered correctly, the leds should flash at an interval 
					given by the potentiometer. Depending on the position  of the slide switch,
					all leds flash at the same time, or one after the other.
					The buttons change the color of the rgb led, by cycling through Red, Green and
					Blue.

TODO:				-Better display of the pwm capabilities of the rgb led by fading on button press
					

PROBLEMS:			Switching between rgb colors on button press did not work reliably on testing,
					something might be wrong with the code or perhaps the board we used for testing.
					It is also possible that the shield has a design flaw.

*/

//this library includes a button class which has a debonce method. More details inside the class.
#include "Button.h"

//creating the button objects on the heap.
Button *btn1 = new Button(2);
Button *btn2 = new Button(3);

//pin initialization
const int led[] = { 6,7,8 };
const int rgb[] = { 9,10,11 };

const int sw = 4;
const int pot = A0;

//number of leds (RGB and 3 red)
const int nOfLeds = 3;	

//led flashing timing:
bool flashState;
bool ledState;
unsigned long minTime=50, maxTime=1000;
unsigned long delayTime = 500;
unsigned long lastBlinkTime;

//current red led which is on:
int currentLed = 0;

//current rgb color to display:
int rgbVal;

// the setup function runs once when you press reset or power the board
void setup() {
	//setup pins:
	for (int i = 0; i < nOfLeds; i++) {
		pinMode(led[i], OUTPUT);
		pinMode(rgb[i], OUTPUT);
	}

	pinMode(sw, INPUT);
	pinMode(pot, INPUT);

	//setup buttons:
	pinMode(2, INPUT_PULLUP);
	pinMode(3, INPUT_PULLUP);

	//TODO: more elegant solution for this in the buttons class.

}

// the loop function runs over and over again until power down or reset
void loop() {
	//readpot and map to a time range for flash interval
	delayTime = map(analogRead(pot), 0, 1024,minTime,maxTime);

	flashState = digitalRead(sw);

	if (!flashState) {
		//blink all leds with certain speed;
		if (millis() - lastBlinkTime > delayTime) {
			//switch between on/off
			ledState = !ledState;
			//write the state to all the leds
			for (int i = 0; i < nOfLeds; i++) {
				digitalWrite(led[i], ledState);
			}
			//store the time of the last blink
			lastBlinkTime = millis();
		}
	}
	else {
		//go through the leds one by one
		if (millis() - lastBlinkTime > delayTime) {
			//increment the current led that is to be lit up
			currentLed = (currentLed + 1) % nOfLeds;
			for (int i = 0; i < nOfLeds; i++) {
				//make all leds except for the "current one" LOW
				if (i == currentLed) {
					digitalWrite(led[i], HIGH);
				}
				else {
					digitalWrite(led[i], LOW);
				}
			}
			//store last blink time
			lastBlinkTime = millis();
		}
	}

	//read button 1 with debounce
	if (btn1->debounce()) {
		//go to the next rgb color:
		rgbVal = (rgbVal + 1) % 3;

		for (int i = 0; i < 3; i++) {
			//make the corresponding color HIGH, test PWM
			if (rgbVal == i) {
				analogWrite(rgb[i], 100);
			}
			else {
				analogWrite(rgb[i], 0);
			}
		}
	}
	//same as for btn1 but the other way:
	else if (btn2->debounce()) {
		rgbVal = (rgbVal - 1);
		if (rgbVal == -1)rgbVal = 2;

		for (int i = 0; i < 3; i++) {
			if (rgbVal == i) {
				analogWrite(rgb[i], 100);
			}
			else {
				analogWrite(rgb[i], 0);
			}
		}
	}

}
