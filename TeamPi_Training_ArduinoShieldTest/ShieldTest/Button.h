#pragma once
#include "Arduino.h"

class Button {
private:
	//fields:
	int btnPin;
	int lastBtnState;
	int btnState;
	unsigned long lastDebounceTime;
	unsigned long debounceDelay;


public:
	//constructor:
	Button(int btnPin);
	Button(int btnPin, unsigned long debounceDelay);
	//methods:
	//read button with debounce
	bool debounce();
	
};