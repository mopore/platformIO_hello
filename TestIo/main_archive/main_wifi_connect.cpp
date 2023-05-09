#include <Arduino.h>
#include <string>
#include "jni_wifi.h"


void setup() {
	Serial.begin(115200);
	const char* ssid = "Loxodonta";
	const char* password = "Twitch7%Carton%Driller%Bluish";
	
	char out_ip[16];
	connect_wifi(out_ip, ssid, password);

	if (strcmp(out_ip, NO_IP)) {
		Serial.printf("Connected with IP address: %s\n", out_ip);
	}
	else {
		Serial.println("Failed to connect to WiFi");
	}
}


void loop() {
	delay(100);
}