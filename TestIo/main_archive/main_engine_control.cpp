#include <Arduino.h>
#include "jni_engine_control.h"
#include "jni_shared_types.h"

JniEngineControl& engineControl = JniEngineControl::getInstance();


void setup() {
	Serial.begin(115200);
}


void loop() {
	for (int pos = 0; pos <= 100; pos++) {
		Serial.println(pos);
		carInput.x = pos;
		carInput.y = pos;
		delay(100);
		engineControl.loop10Hz();
	}
	for (int pos = 100; pos >= 0; pos--) {
		Serial.println(pos);
		carInput.x = pos;
		carInput.y = pos;
		delay(100);
		engineControl.loop10Hz();
	}
	for (int pos = 0; pos >= -100; pos--) {
		Serial.println(pos);
		carInput.x = pos;
		carInput.y = pos;
		delay(100);
		engineControl.loop10Hz();
	}
	for (int pos = -100; pos <= 0; pos++) {
		Serial.println(pos);
		carInput.x = pos;
		carInput.y = pos;
		delay(100);
		engineControl.loop10Hz();
	}
	Serial.println("Will wait 3 seconds before next loop...");
	delay(3000);
}