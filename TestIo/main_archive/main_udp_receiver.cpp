#include <Arduino.h>
#include <SPI.h>
// #include <Adafruit_I2CDevice.h>
#include "jni_wifi.h"
#include "jni_udp_receiver.h"

JniUdpReceiver receiver;

void setup() {
	Serial.begin(115200);
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);	

	Serial.begin(115200);
	const char* ssid = "Loxodonta";
	const char* password = "Twitch7%Carton%Driller%Bluish";
	
	char out_ip[16];
	connect_wifi(out_ip, ssid, password);

	if (strcmp(out_ip, NO_IP) != 0) {
		Serial.printf("Connected with IP address: %s\n", out_ip);
        digitalWrite(LED_BUILTIN, LOW);	
	}
	receiver.setup();
}


void loop() {
	receiver.loop();
}