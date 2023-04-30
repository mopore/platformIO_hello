#include <Arduino.h>
#include "jni_distance.h"


JniDistance distance;


void setup() {
	Serial.begin(115200);
	distance.setup();	
}


void loop() {
	while (true) {
		auto measuremetn = distance.readInstance();
		Serial.printf("Distance: %d mm\n", measuremetn);
		delay(1000);
	}
}