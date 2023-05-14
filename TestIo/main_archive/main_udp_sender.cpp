#include <Arduino.h>
#include <SPI.h>
// #include <Adafruit_I2CDevice.h>
#include "jni_wifi.h"
#include "jni_udp_sender.h"

JniUdpSender sender;

void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);	
	connect_wifi();
	digitalWrite(LED_BUILTIN, LOW);	
	sender.setup();
}


void loop() {
	sender.loop();
}