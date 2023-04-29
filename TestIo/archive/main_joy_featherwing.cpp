#include <Arduino.h>
#include <map>
#include <SPI.h>
#include <Adafruit_seesaw.h>
#include "FeatherJoyWing.h"

#define Y_MAX 127
#define Y_MIN -128
#define X_MAX 127
#define X_MIN -128


Adafruit_seesaw ss;
FeatherJoyWing joy(ss);
std::map<uint8_t, String> buttonNames;


void joystickCallback(int8_t xIn, int8_t yIn){
	int xOut = 0;
	int yOut = 0;
	if (xIn > 0) {
		xOut = ((float)xIn / X_MAX) * 100;
	} else {
		xOut = ((float)xIn / X_MIN) * -100;
	}
	if (yIn > 0) {
		yOut = ((float)yIn / Y_MAX) * 100;
	} else {
		yOut = ((float)yIn / Y_MIN) * -100;
	}
	Serial.print(xOut); Serial.print(" : "); Serial.println(yOut);
}


void buttonCallback(FJBUTTON* buttons, uint8_t count){
	for(int i = 0; i < count; i++) {
		if (buttons[i].hasChanged) {
			Serial.print("Button ");
			String buttonName = buttonNames[buttons[i].pinId];
			Serial.print(buttonName);
			Serial.print(": ");
			Serial.println(buttons[i].pressed);
		}
	}
}


void setup() {
	Serial.begin(115200);
	while (!Serial);

	buttonNames[BUTTON_DOWN] = "DOWN";
	buttonNames[BUTTON_UP] = "UP";
	buttonNames[BUTTON_LEFT] = "LEFT";
	buttonNames[BUTTON_RIGHT] = "RIGHT";
	buttonNames[BUTTON_SEL] = "SELECT";

	Serial.println("FeatherJoyWing test");
	joy.begin();
	joy.registerJoystickCallback(joystickCallback);
	joy.registerButtonCallback(buttonCallback);
}


void loop() {
	joy.update();
	delay(10);
}