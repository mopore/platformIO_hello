#include <Arduino.h>
#include "jni_functions.h"

void setup() {
	Serial.begin(115200);

	Person p("John", 30);
	Serial.println(p.toString());

	pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
	jniFunction();
	digitalWrite(LED_BUILTIN, HIGH);
	delay(1000);
	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
}