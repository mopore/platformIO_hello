#include <Arduino.h>
#include "jni_wifi.h"


void setup() {
	Serial.begin(115200);
	auto returned_ip = connect_wifi().c_str();
	Serial.printf("Connected with IP address: %s\n", returned_ip);
}


void loop() {
	delay(100);
}