#include <Arduino.h>
#include "jni_wifi.h"
#include "jni_udp_receiver.h"

JniUdpReceiver receiver;

void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);	
	connect_wifi();
	digitalWrite(LED_BUILTIN, LOW);	
	receiver.setup();
}

void loop() {
	receiver.loop();
}