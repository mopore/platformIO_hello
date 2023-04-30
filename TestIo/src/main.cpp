#include <Arduino.h>
#include "jni_accelerometer.h"

JniAccelerometer accelerometer;

void setup(void) {
	Serial.begin(115200);
	while (!Serial)
		delay(10); // will pause Zero, Leonardo, etc until serial console opens
	accelerometer.setup();
}


void loop() {
	auto response = accelerometer.readAcceleration();
	auto x = response.accelX;
	Serial.printf("X: %.1f\n", x);
	delay(100);
}