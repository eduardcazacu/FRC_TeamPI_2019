#include "Button.h"

Button::Button(int btnPin) {
	//fields:
	this->btnPin= btnPin;
	lastBtnState=0;
	btnState=0;
	lastDebounceTime=0;
	debounceDelay = 50;
}

Button::Button(int btnPin, unsigned long debounceDelay) {
	//fields:
	this->btnPin = btnPin;
	lastBtnState = 0;
	btnState = 0;
	lastDebounceTime = 0;
	this->debounceDelay = debounceDelay;
}

bool Button::debounce() {
	// read the state of the switch into a local variable:
	int reading = digitalRead(btnPin);
	bool debouncedResult = false;
	// check to see if you just pressed the button
	// (i.e. the input went from LOW to HIGH), and you've waited long enough
	// since the last press to ignore any noise:

	// If the switch changed, due to noise or pressing:
	if (reading != lastBtnState) {
		// reset the debouncing timer
		lastDebounceTime = millis();
	}

	if ((millis() - lastDebounceTime) > debounceDelay) {
		// whatever the reading is at, it's been there for longer than the debounce
		// delay, so take it as the actual current state:

		// if the button state has changed:
		if (reading != btnState) {
			btnState = reading;

			if (btnState == HIGH) {
				debouncedResult = HIGH;
			}
		}
	}

	// save the reading. Next time through the loop, it'll be the lastButtonState:
	lastBtnState = reading;

	return debouncedResult;
}