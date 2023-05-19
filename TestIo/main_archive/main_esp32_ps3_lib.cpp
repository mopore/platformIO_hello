#include <Arduino.h>
#include "jni_ps3_controller.h"
#include "jni_config.h"


// #define ESP32_HOST_MAC "e8:9f:6d:25:49:26"  // Get from jni_config...


JniPs3Controller& ps3Controller = JniPs3Controller::getInstance();


void setup() {
	Serial.println("Starting...");
	Serial.begin(115200);
	ps3Controller.setup(ESP32_HOST_MAC);	
}


void loop() {
	ps3Controller.loop();
}